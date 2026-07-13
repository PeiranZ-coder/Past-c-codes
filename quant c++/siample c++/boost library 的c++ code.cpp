// SimpleMonteCarloBoost.cpp
// 用 Boost 写的一个简单蒙特卡罗欧式看涨期权定价器。
//   - 随机数：boost::random (mt19937 + normal_distribution)
//   - 对照解：boost::math 的正态 CDF 算 Black-Scholes 闭式价
// 编译示例（Linux）: g++ -O2 -std=c++17 SimpleMonteCarloBoost.cpp -o mc
// boost::random 和 boost::math 都是 header-only，无需额外链接。

#include <boost/random.hpp>
#include <boost/math/distributions/normal.hpp>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>

// 生成一个标准正态随机数。generator 与 distribution 都 static：
// 整个程序只构造一次，保住 MT 状态推进和分布的内部缓存。
double GetOneGaussian() {
    static boost::random::mt19937 generator(
        static_cast<unsigned>(std::time(nullptr)));
    static boost::random::normal_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

// 欧式看涨的蒙特卡罗定价。
// 在 GBM 下直接抽终值 S_T，不用逐步模拟路径。
// 通过引用 stdErr 带出蒙特卡罗标准误。
double MonteCarloCall(double S0, double K, double r, double vol,
    double T, unsigned long NumberOfPaths, double& stdErr) {
    double drift = (r - 0.5 * vol * vol) * T;
    double diffusion = vol * std::sqrt(T);
    double disc = std::exp(-r * T);

    // Welford 在线算法：一遍循环里稳定地求均值和方差。
    double mean = 0.0, M2 = 0.0;
    for (unsigned long i = 1; i <= NumberOfPaths; ++i) {
        double z = GetOneGaussian();
        double ST = S0 * std::exp(drift + diffusion * z);
        double payoff = ST - K;
        payoff = payoff > 0.0 ? payoff : 0.0;
        double discPayoff = disc * payoff;

        double delta = discPayoff - mean;
        mean += delta / i;
        M2 += delta * (discPayoff - mean);
    }

    double variance = (NumberOfPaths > 1) ? M2 / (NumberOfPaths - 1) : 0.0;
    stdErr = std::sqrt(variance / NumberOfPaths);
    return mean;
}

// Black-Scholes 闭式看涨价，用 Boost 的正态 CDF 做对照基准。
double BlackScholesCall(double S0, double K, double r, double vol, double T) {
    boost::math::normal_distribution<double> N(0.0, 1.0);
    double sqrtT = std::sqrt(T);
    double d1 = (std::log(S0 / K) + (r + 0.5 * vol * vol) * T) / (vol * sqrtT);
    double d2 = d1 - vol * sqrtT;
    return S0 * cdf(N, d1) - K * std::exp(-r * T) * cdf(N, d2);
}

int main() {
    // ---- 从键盘读入期权与市场参数 ----
    double S0, K, r, vol, T;
    unsigned long NumberOfPaths;

    std::cout << "\nEnter expiry (T, in years): ";
    std::cin >> T;
    std::cout << "Enter strike (K): ";
    std::cin >> K;
    std::cout << "Enter spot (S0): ";
    std::cin >> S0;
    std::cout << "Enter vol (e.g. 0.20): ";
    std::cin >> vol;
    std::cout << "Enter r (e.g. 0.05): ";
    std::cin >> r;
    std::cout << "Enter number of paths: ";
    std::cin >> NumberOfPaths;

    double stdErr;
    double mc = MonteCarloCall(S0, K, r, vol, T, NumberOfPaths, stdErr);
    double bs = BlackScholesCall(S0, K, r, vol, T);

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "\n--- Result ---\n";
    std::cout << "Paths                  : " << NumberOfPaths << "\n";
    std::cout << "Monte Carlo call price : " << mc << "\n";
    std::cout << "Standard error         : " << stdErr << "\n";
    std::cout << "95% CI                 : [" << mc - 1.96 * stdErr
        << ", " << mc + 1.96 * stdErr << "]\n";
    std::cout << "Black-Scholes (exact)  : " << bs << "\n";
    std::cout << "MC - BS                : " << mc - bs << "\n";
    return 0;
}

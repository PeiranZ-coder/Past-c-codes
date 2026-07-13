#include <iostream>
#include <cmath>
#include <random> // 使用标准库的随机数
#include <ctime>

using namespace std;

// 将生成器留在全局或专门的命名空间中，保持 static
static mt19937 generator(static_cast<unsigned>(time(nullptr)));
static normal_distribution<double> distribution(0.0, 1.0);

double SimpleMonteCarlo1(double Expiry, double Strike, double Spot,
    double Vol, double r, unsigned long NumberOfPaths) {

    // 1. 确保这四行定义都在，没有被误删！
    double variance = Vol * Vol * Expiry;
    double rootVariance = sqrt(variance); // <-- 就是这一行定义了 rootVariance
    double itoCorrection = -0.5 * variance;
    double movedSpot = Spot * exp(r * Expiry + itoCorrection);
    double runningSum = 0;

    for (unsigned long i = 0; i < NumberOfPaths; i++) {
        // 如果你用的是标准库/Boost，这里直接调用
        double thisGaussian = distribution(generator);

        // 这一行需要用到上面定义的 rootVariance
        double thisSpot = movedSpot * exp(rootVariance * thisGaussian);
        double thisPayoff = thisSpot - Strike;
        thisPayoff = thisPayoff > 0 ? thisPayoff : 0;
        runningSum += thisPayoff;
    }

    double mean = runningSum / NumberOfPaths;
    mean *= exp(-r * Expiry);
    return mean;
}

int main() {
    double Expiry, Strike, Spot, Vol, r;
    unsigned long NumberofPaths;

    cout << "\nEnter expiry: \n";
    cin >> Expiry;
    cout << "\nEnter strike: \n";
    cin >> Strike;
    cout << "\nEnter spot: \n";
    cin >> Spot;
    cout << "\nEnter vol\n";
    cin >> Vol;
    cout << "\nr\n";
    cin >> r;
    cout << "\nNumber of paths\n";
    cin >> NumberofPaths;

    double result = SimpleMonteCarlo1(Expiry, Strike, Spot, Vol, r, NumberofPaths);
    cout << "the price is: " << result << "\n";

    return 0;
}
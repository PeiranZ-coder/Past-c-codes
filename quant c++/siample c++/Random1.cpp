#include "Random1.h"
#include <cmath>
#include <ctime>

// 使用Boost的随机数生成器
static boost::random::mt19937 generator(
    static_cast<unsigned>(std::time(nullptr))
);
static boost::random::normal_distribution<double> distribution(0.0, 1.0);

double GetOneGaussianByBoxMuller() {
    return distribution(generator);
}
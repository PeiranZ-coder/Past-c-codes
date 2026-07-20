#include "finance_utils.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// ================= Q1: 复利计算 =================

double futureValue(double principal, double rate, int years) {
    double amount = principal;
    for (int i = 0; i < years; i++) {
        amount *= (1 + rate);
    }
    return amount;
}

void printGrowthSchedule(double principal, double rate, int years) {
    double amount = principal;
    cout << fixed << setprecision(2);
    cout << "=== 投资增长明细 ===" << endl;
    cout << "初始本金: $" << principal << endl;
    cout << "年化利率: " << rate * 100 << "%" << endl;
    cout << "投资年限: " << years << " 年" << endl;
    cout << "-------------------" << endl;

    for (int year = 1; year <= years; year++) {
        amount *= (1 + rate);
        cout << "第 " << setw(2) << year << " 年: $";
        cout << setw(10) << amount << endl;
    }
    cout << "-------------------" << endl;
    cout << "最终终值: $" << amount << endl;
}

// ================= Q2: 波动率计算 =================

double calcMeanReturn(const double prices[], int size) {
    if (size < 2) {
        cout << "警告：价格数据不足，无法计算收益率" << endl;
        return 0.0;
    }

    double sum = 0.0;
    int count = size - 1;

    for (int i = 1; i < size; i++) {
        double ret = (prices[i] - prices[i - 1]) / prices[i - 1];
        sum += ret;
    }

    return sum / count;
}

double calcVolatility(const double prices[], int size) {
    if (size < 2) {
        cout << "警告：价格数据不足，无法计算波动率" << endl;
        return 0.0;
    }

    int count = size - 1;
    double mean = calcMeanReturn(prices, size);
    double sumSq = 0.0;

    for (int i = 1; i < size; i++) {
        double ret = (prices[i] - prices[i - 1]) / prices[i - 1];
        double diff = ret - mean;
        sumSq += diff * diff;
    }

    double dailyStd = sqrt(sumSq / (count - 1));
    double annualizedVol = dailyStd * sqrt(252.0);

    return annualizedVol;
}

// ================= Q3: 最大回撤计算 =================

double maxDrawdown(const double prices[], int size) {
    if (size < 2) {
        cout << "警告：数据不足，无法计算最大回撤" << endl;
        return 0.0;
    }

    double peak = prices[0];
    double maxDD = 0.0;

    for (int i = 1; i < size; i++) {
        if (prices[i] > peak) {
            peak = prices[i];
        }

        double currentDD = (peak - prices[i]) / peak;

        if (currentDD > maxDD) {
            maxDD = currentDD;
        }
    }

    return maxDD;
}

// ================= Q4: 夏普比率 =================

double calcSharpeRatio(const double prices[], int size, double riskFreeRate) {
    if (size < 2) return 0.0;

    double meanRet = calcMeanReturn(prices, size);
    double vol = calcVolatility(prices, size);

    // 年化收益率（假设252个交易日）
    double annualizedRet = meanRet * 252;
    double annualizedVol = vol;  // calcVolatility已经返回年化值

    if (annualizedVol == 0) return 0.0;

    return (annualizedRet - riskFreeRate) / annualizedVol;
}

// ================= Q5: SMA和交易信号 =================

double calcSMA(const double prices[], int size, int period) {
    if (size < period || period <= 0) return 0.0;

    double sum = 0.0;
    for (int i = size - period; i < size; i++) {
        sum += prices[i];
    }
    return sum / period;
}

int generateSMASignal(const double prices[], int size, int shortPeriod, int longPeriod) {
    if (size < longPeriod + 1) return 0;  // 数据不足

    // 计算当前和上一个周期的SMA
    double currentShortSMA = calcSMA(prices, size, shortPeriod);
    double currentLongSMA = calcSMA(prices, size, longPeriod);

    double prevShortSMA = calcSMA(prices, size - 1, shortPeriod);
    double prevLongSMA = calcSMA(prices, size - 1, longPeriod);

    // 判断交叉信号
    if (prevShortSMA <= prevLongSMA && currentShortSMA > currentLongSMA) {
        return 1;  // 金叉买入
    }
    else if (prevShortSMA >= prevLongSMA && currentShortSMA < currentLongSMA) {
        return -1; // 死叉卖出
    }

    return 0;  // 无信号
}

// ================= Q6: 蒙特卡洛模拟 =================

// 自定义PI常量（避免M_PI未定义问题）
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void monteCarloSimulation(double startPrice, double mu, double sigma,
    int days, int simulations, double* results) {
    // 将年化参数转换为日参数
    double dt = 1.0 / 252.0;
    double dailyMu = mu * dt;
    double dailySigma = sigma * sqrt(dt);

    // 使用当前时间作为随机种子（修复类型转换警告）
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int sim = 0; sim < simulations; sim++) {
        results[sim * days] = startPrice;
        for (int day = 1; day < days; day++) {
            // 生成标准正态随机数（Box-Muller变换）
            double u1 = rand() / (double)RAND_MAX;
            double u2 = rand() / (double)RAND_MAX;
            // 确保u1不为0，避免log(0)
            if (u1 < 0.0001) u1 = 0.0001;
            double z = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);

            // 几何布朗运动
            double ret = dailyMu + dailySigma * z;
            results[sim * days + day] = results[sim * days + day - 1] * (1 + ret);
        }
    }
}
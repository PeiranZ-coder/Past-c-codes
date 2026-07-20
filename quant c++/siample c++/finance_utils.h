#ifndef FINANCE_UTILS_H
#define FINANCE_UTILS_H

// ================= 量化金融工具函数声明 =================

/**
 * Q1: 计算复利终值
 */
double futureValue(double principal, double rate, int years);

/**
 * Q1: 打印逐年增长明细
 */
void printGrowthSchedule(double principal, double rate, int years);

/**
 * Q2: 计算日收益率均值
 */
double calcMeanReturn(const double prices[], int size);

/**
 * Q2: 计算年化波动率
 */
double calcVolatility(const double prices[], int size);

/**
 * Q3: 计算最大回撤
 */
double maxDrawdown(const double prices[], int size);

/**
 * Q4: 计算夏普比率
 */
double calcSharpeRatio(const double prices[], int size, double riskFreeRate = 0.02);

/**
 * Q5: 计算简单移动平均线
 */
double calcSMA(const double prices[], int size, int period);

/**
 * Q5: 生成SMA交叉信号
 */
int generateSMASignal(const double prices[], int size, int shortPeriod, int longPeriod);

/**
 * Q6: 蒙特卡洛模拟价格路径
 */
void monteCarloSimulation(double startPrice, double mu, double sigma,
    int days, int simulations, double* results);

#endif // FINANCE_UTILS_H

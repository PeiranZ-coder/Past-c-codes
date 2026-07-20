#include "finance_utils.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// 设置控制台编码为UTF-8
void setConsoleUTF8() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

// 辅助函数：打印数组
void printArray(const double arr[], int size, const string& name) {
    cout << name << " = [";
    for (int i = 0; i < size; i++) {
        cout << fixed << setprecision(4) << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    setConsoleUTF8();
    cout << "========================================" << endl;
    cout << "   量化金融工具包 - 测试程序" << endl;
    cout << "========================================" << endl << endl;

    // ================= 测试 Q1: 复利计算 =================
    cout << "【测试1】复利增长计算" << endl;
    cout << "----------------------------------------" << endl;

    double principal = 10000.0;
    double rate = 0.05;
    int years = 10;

    cout << fixed << setprecision(2);
    cout << "本金: $" << principal << endl;
    cout << "年利率: " << rate * 100 << "%" << endl;
    cout << "投资年限: " << years << " 年" << endl;
    cout << "终值: $" << futureValue(principal, rate, years) << endl << endl;

    printGrowthSchedule(principal, rate, years);
    cout << endl;

    // ================= 测试 Q2: 波动率计算 =================
    cout << "【测试2】波动率计算" << endl;
    cout << "----------------------------------------" << endl;

    double prices1[] = { 100.0, 102.0, 101.0, 105.0, 110.0 };
    int size1 = 5;

    printArray(prices1, size1, "价格序列");

    double meanRet = calcMeanReturn(prices1, size1);
    double vol = calcVolatility(prices1, size1);

    cout << fixed << setprecision(4);
    cout << "日收益率均值: " << meanRet * 100 << "%" << endl;
    cout << "年化波动率: " << vol * 100 << "%" << endl << endl;

    // ================= 测试 Q3: 最大回撤 =================
    cout << "【测试3】最大回撤计算" << endl;
    cout << "----------------------------------------" << endl;

    double prices2[] = { 100.0, 110.0, 105.0, 90.0, 95.0, 80.0 };
    int size2 = 6;

    printArray(prices2, size2, "价格序列");

    double mdd = maxDrawdown(prices2, size2);

    cout << fixed << setprecision(4);
    cout << "最大回撤: " << mdd * 100 << "%" << endl << endl;

    // ================= 测试 Q4: 夏普比率 =================
    cout << "【测试4】夏普比率计算" << endl;
    cout << "----------------------------------------" << endl;

    double prices3[] = { 100.0, 102.0, 104.0, 103.0, 105.0, 107.0, 106.0, 108.0 };
    int size3 = 8;
    double sharpe = calcSharpeRatio(prices3, size3, 0.02);
    cout << "夏普比率: " << fixed << setprecision(4) << sharpe << endl << endl;

    // ================= 测试 Q5: SMA信号 =================
    cout << "【测试5】SMA交易信号" << endl;
    cout << "----------------------------------------" << endl;

    double prices4[] = { 100, 101, 102, 103, 102, 101, 100, 99, 100, 101, 102, 103 };
    int size4 = 12;
    int signal = generateSMASignal(prices4, size4, 3, 5);
    cout << "SMA信号: ";
    if (signal == 1) cout << "买入（金叉）" << endl;
    else if (signal == -1) cout << "卖出（死叉）" << endl;
    else cout << "持有（无信号）" << endl << endl;

    // ================= 测试 Q6: 蒙特卡洛模拟 =================
    cout << "【测试6】蒙特卡洛模拟" << endl;
    cout << "----------------------------------------" << endl;

    const int DAYS_SIM = 252;
    const int SIMS = 5;
    double* simResults = new double[SIMS * DAYS_SIM];

    monteCarloSimulation(100.0, 0.08, 0.25, DAYS_SIM, SIMS, simResults);

    cout << "模拟 " << SIMS << " 条价格路径（前10天）:" << endl;
    for (int sim = 0; sim < SIMS; sim++) {
        cout << "路径 " << sim + 1 << ": ";
        for (int day = 0; day < 10; day++) {
            cout << fixed << setprecision(2) << simResults[sim * DAYS_SIM + day] << " ";
        }
        cout << "..." << endl;
    }

    delete[] simResults;

    cout << endl << "========================================" << endl;
    cout << "   测试完成！" << endl;
    cout << "========================================" << endl;

    return 0;
}



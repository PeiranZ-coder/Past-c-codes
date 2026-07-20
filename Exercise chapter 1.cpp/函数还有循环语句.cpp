#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

/*int main() {
    // some operationf
    return 0;
}*/


/*int main() {
	string msg{ "Hello c++" };
	cout << msg << endl;
	return 0;
}*/

/*int add (double a, double b, double c){
	return a + (c + b) + a;

}

int main() {
	double a, b, c;
	double result;
	cout << " thre number  is ";
	cin >> a;
	cin >> b;
	cin >> c;
	result = add(a, b, c);
	cout << " the result is " << result << endl;
	return 0;
}*/




/*int square3(int x)
{
	x = 3;
	return x * x;
}

int main()
{
	int x = 5;
	cout << square3(x) << endl; // 9
	cout << x << endl; // 5
}*/




/* ============================================
   题目1：累加器
   要求：编写函数 int sumUpTo(int n)，用 for 循环
         计算 1 + 2 + ... + n 的和并返回。
   知识点：for 循环、函数返回值、参数传递
   ============================================ */
int sumUpTo(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;  // 累加 i（不是 1）
    }
    return sum;
}

/* ============================================
   题目2：偶数打印器
   要求：编写函数 void printEvenNumbers(int n)，
         用 while 循环打印 2 到 n 的所有偶数。
   知识点：while 循环、void 函数、格式化输出
   ============================================ */
void printEvenNumbers(int n) {
    int i = 2;
    while (i <= n) {
        cout << i << endl;
        i += 2;
    }
}

/* ============================================
   题目3：素数判定器
   要求：编写函数 bool isPrime(int num)，判断
         是否为素数。只需检查到 sqrt(num)。
   知识点：for 循环、bool 返回、break、数学库
   ============================================ */
bool isPrime(int num) {
    if (num < 2) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;

    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

/* ============================================
   题目4：数字反转器
   要求：编写函数 int reverseNumber(int num)，
         用 do-while 将正整数反转。
   知识点：do-while 循环、整数分解与重组
   ============================================ */
int reverseNumber(int num) {
    int rev = 0;
    do {
        int digit = num % 10;
        rev = rev * 10 + digit;
        num /= 10;
    } while (num > 0);
    return rev;
}

/* ============================================
   题目5：数组最大值查找
   要求：编写函数 int findMax(const int arr[], int size)，
         遍历数组返回最大值。
   知识点：数组参数、const 保护、遍历循环
   ============================================ */
int findMax(const int arr[], int size) {
    int maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

/* ============================================
   题目6：乘法表生成器（嵌套循环）
   要求：编写函数 void printMultiplicationTable(int n)，
         用嵌套 for 打印 n×n 乘法表，setw(4) 对齐。
   知识点：嵌套 for 循环、格式化输出
   ============================================ */
void printMultiplicationTable(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << setw(4) << i * j;
        }
        cout << endl;
    }
}

/* ============================================
   题目7：猜数字游戏（循环控制 + 函数封装）
   要求：generateRandomNumber() 返回 1~100 随机数；
         guessGame() 用 while 循环让用户猜，统计次数。
   知识点：随机数、while 循环、函数封装
   ============================================ */
int generateRandomNumber() {
    return rand() % 100 + 1;
}

void guessGame() {
    int target = generateRandomNumber();
    int guess;
    int attempts = 0;

    cout << "猜一个 1~100 之间的数字: " << endl;

    while (true) {
        cin >> guess;
        attempts++;

        if (guess > target) {
            cout << "太大了！再试一次: ";
        }
        else if (guess < target) {
            cout << "太小了！再试一次: ";
        }
        else {
            cout << "恭喜！你猜对了！数字是 " << target
                << "，你总共猜了 " << attempts << " 次。" << endl;
            break;
        }
    }
}

/* ============================================
   main 函数：测试所有题目
   ============================================ */
int main() {
    // 设置随机种子（只需一次，放在 main 开头）
    srand(time(0));

    // ---------- 题目1 测试 ----------
    cout << "===== 题目1：累加器 =====" << endl;
    int n1;
    cout << "请输入 n: ";
    cin >> n1;
    cout << "1 到 " << n1 << " 的和是: " << sumUpTo(n1) << endl << endl;

    // ---------- 题目2 测试 ----------
    cout << "===== 题目2：偶数打印器 =====" << endl;
    int n2;
    cout << "请输入 n: ";
    cin >> n2;
    printEvenNumbers(n2);
    cout << endl;

    // ---------- 题目3 测试 ----------
    cout << "===== 题目3：素数判定器 =====" << endl;
    int num;
    cout << "请输入一个正整数: ";
    cin >> num;
    if (isPrime(num)) {
        cout << num << " 是素数" << endl;
    }
    else {
        cout << num << " 不是素数" << endl;
    }
    cout << endl;

    // ---------- 题目4 测试 ----------
    cout << "===== 题目4：数字反转器 =====" << endl;
    int revNum;
    cout << "请输入一个正整数: ";
    cin >> revNum;
    cout << "反转后: " << reverseNumber(revNum) << endl << endl;

    // ---------- 题目5 测试 ----------
    cout << "===== 题目5：数组最大值 =====" << endl;
    int arr[5] = { 3, 7, 1, 9, 4 };
    cout << "数组: [3, 7, 1, 9, 4]" << endl;
    cout << "最大值: " << findMax(arr, 5) << endl << endl;

    // ---------- 题目6 测试 ----------
    cout << "===== 题目6：乘法表 =====" << endl;
    int n6;
    cout << "请输入 n: ";
    cin >> n6;
    printMultiplicationTable(n6);
    cout << endl;

    // ---------- 题目7 测试 ----------
    cout << "===== 题目7：猜数字游戏 =====" << endl;
    guessGame();

    return 0;
}

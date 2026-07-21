/*题目1：学生信息结构体（基础）
要求：定义一个 Student 结构体，包含 name（姓名，string）、age（年龄，int）、score（成绩，double）。在 main 中创建一个学生，输入信息并打印。*/
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

struct Student {
	string name;
	int age;
	double score;
};

/*int main() {
    Student s;
    cout << "请输入姓名: ";
    cin >> s.name;
    cout << "请输入年龄: ";
    cin >> s.age;
    cout << "请输入成绩: ";
    cin >> s.score;

    cout << "姓名: " << s.name
        << ", 年龄: " << s.age
        << ", 成绩: " << s.score << endl;
    return 0;
}*/

/*题目2：学生数组 + 查找最高分（结构体数组）
要求：定义包含 3 个学生的数组，输入信息后，编写函数 Student findTopStudent(Student arr[], int n) 返回成绩最高的学生。*/
Student findTopStudent(Student arr[], int n) {
    Student top = arr[0];
    for (int i = 0; i < n; i++) {
        if (arr[i].score > top.score) {
            top = arr[i];
        }
    }
    return top;
}
/*int main() {
    Student arr[3];  // 3个学生的数组

    // 输入3个学生的信息
    for (int i = 0; i < 3; i++) {
        cout << "请输入第" << (i + 1) << "个学生姓名: ";
        cin >> arr[i].name;
        cout << "请输入第" << (i + 1) << "个学生成绩: ";
        cin >> arr[i].score;
        // 年龄如果需要也可以输入，题目主要关注成绩
    }

    // 调用函数找最高分
    Student top = findTopStudent(arr, 3);

    // 输出结果
    cout << "最高分学生: " << top.name
        << ", 成绩: " << top.score << endl;

    return 0;
}*/


/*题目3：点结构体 + 距离计算
要求
定义 Point 结构体，包含：
x（double）
y（double）*/


/*struct Point {
    double x;double y;
};

// 第二步：实现 distance 函数
double distance(Point a, Point b) {
    double dx = a.x - b.x;  // x方向差值
    double dy = a.y -b.y;  // 填空：y方向差值怎么写？

    return sqrt(dx * dx + dy * dy);  // 填空：sqrt里面填什么公式？
}

int main() {
    Point p1, p2;

    cout << "请输入点A的坐标(x y): ";
    cin >> p1.x >> p1.y;  // 可以同时输入两个数

    cout << "请输入点B的坐标(x y): ";
    cin >> p2.x >> p2.y;   // 填空

    double dist = distance(p1, p2);
    cout << "两点距离: " << dist << endl;

    return 0;
}*/


/*题目4：矩形类（class 基础）
要求：定义 Rectangle 类，私有成员 width、height。提供：
构造函数 Rectangle(double w, double h)
公有方法 double getArea()、double getPerimeter()
在 main 中创建对象并测试
知识点：类、私有成员、构造函数、成员函数*/

/*class Rectangle {
private: double width;
       double height;
public: 
    Rectangle(double w, double h) {
        width = w;
        height = h;

    }
    double getArea() {
        return width * height;
   }
    double getPerimeter() {
        return 2 * width + 2 * height;
   }
};

int main() {
    double w, h;
    cout << "请输入宽: ";
    cin >> w;
    cout << "请输入高: ";
    cin >> h;

    // 填空：创建 Rectangle 对象，传入 w 和 h
    Rectangle rect(w,h);

    cout << "面积: " << rect.getArea() << endl;
    cout << "周长: " << rect.getPerimeter() << endl;

    return 0;
} */


/*题目5：银行账户类（封装 + 方法）
要求：定义 BankAccount 类：
私有成员：accountNumber（账号）、balance（余额）
构造函数初始化账号和余额（默认 0）
公有方法：deposit(double amount) 存款、withdraw(double amount) 取款（余额不足提示失败）、getBalance() 查余额
知识点：封装、业务逻辑、条件判断*/


#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string accountNumber;   // ← 账号是 string
    double balance;

public:
    // 构造函数：账号 + 余额（默认0）
    BankAccount(string num, double bal = 0.0) {
        accountNumber = num;
        balance = bal;
    }

    // 存款
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "存款 " << amount << " 元，当前余额: "
                << balance << " 元" << endl;
        }
        else {
            cout << "存款金额必须大于0！" << endl;
        }
    }

    // 取款
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {   // ← 两个条件
            balance -= amount;
            cout << "取款 " << amount << " 元，当前余额: "
                << balance << " 元" << endl;
            return true;
        }
        else {
            cout << "余额不足！当前余额: " << balance << " 元" << endl;
            return false;
        }
    }

    // 查余额
    double getBalance() {
        return balance;
    }
};

int main() {
    string num;
    double initialBal;

    cout << "请输入账号: ";
    cin >> num;
    cout << "请输入初始余额: ";
    cin >> initialBal;

    BankAccount account(num, initialBal);   // 创建账户

    int choice;
    double amount;

    while (true) {
        cout << "\n请选择操作: 1-存款 2-取款 3-查余额 0-退出\n> ";
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
        case 1:
            cout << "请输入存款金额: ";
            cin >> amount;
            account.deposit(amount);
            break;
        case 2:
            cout << "请输入取款金额: ";
            cin >> amount;
            account.withdraw(amount);
            break;
        case 3:
            cout << "当前余额: " << account.getBalance() << " 元" << endl;
            break;
        default:
            cout << "无效选择！" << endl;
        }
    }

    cout << "感谢使用，再见！" << endl;
    return 0;
}

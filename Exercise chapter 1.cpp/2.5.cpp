//练习 1.3
//编写程序，在标准输出上打印 Hello, World。
  //Exercise 1.3: Write a program to print Hello, World on the standard output.

#include<iostream>  //

int main() {
	std::cout << "hello world" << std::endl;

		return 0;
}


// Exercise 1.4: Our program used the addition operator, +, to add two numbers. Write a program that uses the multiplication operator, *, to print the product instead.
//练习 1.4 我们的程序使用加法运算符 + 来将两个数相加。编写程序使用乘法运算符 *，来打印两个数的积。
#include<iostream>

int main() {

	double v1 = 0;
	double v2 = 0;
	
	
	
	std::cout << "Enter two numbers:" << std::endl;
	
	std::cin >> v1 >> v2; // 第一步：从输入流读取第一个整数，存入 v1
	
	std::cout << "The sum of " << v1 << " and " << v2
		<< " is " << v1 + v2 << std::endl;

	std::cout << "The product of " << v1 << " and " << v2
		<< " is " << v1 * v2 << std::endl;

	return 0;
}


//Exercise 1.5: We wrote the output in one large statement. Rewrite the program to us a separate statement to print each operand.
//我们将所有输出操作放在一条很长的语句中。重写程序，将每个运算对象的打印操作放在一条独立的语句中。
#include <iostream>

int main()
{
    int v1 = 0, v2 = 0;
    std::cout << "Enter two numbers:" << std::endl;
    std::cin >> v1 >> v2;
    std::cout << "The product of ";
    std::cout << v1;
    std::cout << " and ";
    std::cout << v2;
    std::cout << " is ";
    std::cout << v1 * v2;
    std::cout << std::endl;
    return 0;
}

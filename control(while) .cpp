// Exercise 1.9 Write a program that uses a while to sum the numbers from 50 to 100.

#include <iostream>

int main() {
    int sum = 0;
    int i = 50;
    
    while (i <= 100) {
        sum += i;  // equivalent to: sum = sum + i;
        ++i;       // increment i by 1
    }
    
    std::cout << "The sum of numbers from 50 to 100 is: " << sum << std::endl;
    
    return 0;
}


//Exercise 1.10 Use the decrement operator (--) to write a while that prints the numbers from ten down to zero.
#include <iostream>

int main() {
    int i = 10;
    
    while (i >= 0) {
        std::cout << i << " ";
        --i;  // decrement i by 1
    }
    std::cout << std::endl;
    
    return 0;
}

// Exercise 1.11Write a program that prompts the user for two integers. Print each number in the range specified by those two integers.
#include <iostream>

int main() {
    int v1 = 0, v2 = 0;
    
    std::cout << "Enter two integers: ";
    std::cin >> v1 >> v2;
    
    // 确定范围
    int lower = v1 < v2 ? v1 : v2;  // 三元运算符
    int upper = v1 > v2 ? v1 : v2;
    
    std::cout << "Numbers between " << lower << " and " << upper << ":" << std::endl;
    
    while (lower <= upper) {
        std::cout << lower << " ";
        ++lower;
    }
    std::cout << std::endl;
    
    return 0;
}

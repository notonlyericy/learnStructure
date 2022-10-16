#include <iostream>

int factorial(int n)
{
    if (n <= 1) return 1;
    int sum = 1;
    for (int i = n; i > 1; i--)
        sum *= i;
    return sum;
} // S(n) = 0, 参数、变量、代码都不依赖实例特征 n

int rFactorial(int n)
{
    if (n <= 1) return 1;
    return n * rFactorial(n-1);
} // S(n) = 8*max{n,1}

int main()
{
    bool ok = true;

    int i;
    for (i = 10; i >= 0 && factorial(i) == rFactorial(i); i--) {}
    if (i >= 0) ok = false;

    std::cout << "i = " << i <<", test " << (ok ? "succeed":"failed") << std::endl;
    return 0;
}

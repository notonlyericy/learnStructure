#include <iostream>

/**
 * 注：
 * 1. opd() 相比 d(), 少了 int i = 1 的 step
 * 2. 4) 略
 */
static int stepCount = 0;

void d(int x[], int n)
{
    for (int i = 0; i < n; i += 2)
    {
        stepCount++; // i < n(i<n)
        x[i] += 2;
        stepCount++; // x[i] += 2
    }
    stepCount++; // i < n(i==n)
    int i = 1;
    stepCount++; // i = 1
    while (i <= n / 2)
    {
        stepCount++; // i <= n/2
        x[i] += x[i + 1];
        stepCount++; // x[i] += x[i+1]
        i++;
        stepCount++; // i++
    }
    stepCount++; // i <= n/2(i>n/2)
}

void opd(int x[], int n)
{
    for (int i = 0; i < n; i += 2)
    {
        stepCount++;
        x[i] += 2;
        stepCount++;
        if (i > 0)
        {
            stepCount++;
            x[i/2] += x[i/2+1];
            stepCount++; // ==> x[i] += x[i+1]
        }
        stepCount++; // ==> i++
    }
    stepCount++;
}


int main()
{
    stepCount = 0;
    int a[]{1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(a) / sizeof(a[0]);
    d(a, n);
    std::cout << stepCount << "\n";
    for (auto v : a) std::cout << v << " ";
    std::cout << "\n";

    stepCount = 0;
    int b[]{1, 2, 3, 4, 5, 6, 7};
    opd(b, n);
    std::cout << stepCount << "\n"; // 相比 d(), 少了 int i = 1 的 step
    for (auto v : b) std::cout << v << " ";
    std::cout << "\n";
    return 0;
}

#include <iostream>

template<typename T>
void rank(T a[], int n, int r[])
{
    for (int i = 0; i < n; i++)
        r[i] = 0;

    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            if (a[j] < a[i]) r[i]++;
            else r[j]++;
}

int main()
{
    int a[]{3,2,6,5,9,4,7,1,8};
    int n = sizeof(a)/sizeof(a[0]);
    int *r = new int[n];
    rank(a, n, r);

    for (int i = 0; i < n; i++)
        std::cout << r[i] << " ";

    delete []r;
    return 0;
}

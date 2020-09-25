#include <stdio.h>

int factorial(int x)
{
    if (x < 1)
        return 1;
    return x * factorial(x - 1);
}

int main()
{
    int x;
    scanf("%d", &x);
    int res = 1;
    for (int i = 2; i <= x; ++i) {
        res *= i;
    }
    printf("%d \n%d", res, factorial(x));
    return 0;
}
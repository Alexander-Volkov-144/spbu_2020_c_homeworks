#include <stdio.h>

int factorialRecursive(int x)
{
    if (x <= 1)
        return 1;
    return x * factorialRecursive(x - 1);
}

int factorialIterative(int x)
{
    int res = 1;
    for (int i = 2; i <= x; ++i) {
        res *= i;
    }
    return res;
}

int main()
{
    int x = 0;
    printf("enter a natural number\n");
    scanf("%d", &x);
    printf("factorial of number %d, calculated iteratively = %d\n", x, factorialIterative(x));
    printf("factorial of number %d, calculated recursively = %d", x, factorialRecursive(x));
    return 0;
}
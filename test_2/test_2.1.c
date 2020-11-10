#include <stdio.h>

unsigned long long getFibonacciNumber(int ordinalNumber)
{
    unsigned long long a = 0, b = 1, temporary = 0;
    for (int i = 0; i < ordinalNumber; ++i) {
        temporary = b;
        b += a;
        a = temporary;
    }
    return a;
}

int main()
{
    int ordinalNumber = 0;
    printf("enter the ordinal ordinalNumber of the Fibonacci ordinalNumber\n");
    scanf("%d", &ordinalNumber);
    printf("%d Fibonacci ordinalNumber: %llu", ordinalNumber, getFibonacciNumber(ordinalNumber));
    return 0;
}


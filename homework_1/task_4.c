#include <stdbool.h>
#include <stdio.h>

int main()
{
    int n = 0;
    printf("enter a natural number\n");
    scanf("%d", &n);
    printf("all primes less than n:\n");
    for (int i = 2; i < n; ++i) {
        bool check = true;
        for (int j = 2; j * j <= i; ++j) {
            if (i % j == 0) {
                check = false;
                break;
            }
        }
        if (check) {
            printf("%d ", i);
        }
    }
    return 0;
}

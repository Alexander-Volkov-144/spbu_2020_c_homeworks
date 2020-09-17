#include <stdio.h>
#include <math.h>

int main()
{
    int n = 0;
    scanf("%d", &n);
    for (int i = 2; i < n; ++i) {
        int check = 1, squareRoot = sqrt(i);
        for (int j = 2; j <= squareRoot; ++j) {
            if (i % j == 0) {
                check = 0;
                break;
            }
        }
        if (check)
            printf("%d ", i);
    }
    return 0;
}
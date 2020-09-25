#include <math.h>
#include <stdbool.h>
#include <stdio.h>

int main()
{
    int n = 0;
    scanf("%d", &n);
    for (int i = 2; i < n; ++i) {
        bool check = true;
        int squareRoot = sqrt(i);
        for (int j = 2; j <= squareRoot; ++j) {
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

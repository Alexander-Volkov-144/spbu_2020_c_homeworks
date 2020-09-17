#include <stdio.h>

int main()
{
    int n = 0;
    scanf("%d", &n);
    int array[n][n];
    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != n; ++j) {
            scanf("%d", &array[i][j]);
        }
    }
    int row = n / 2, column = n / 2, l = 1;
    printf("%d ", array[row][column]);
    if (n == 1)
        return 0;
    while (1) {
        for (int i = 0; i < l; ++i) {
            column--;
            printf("%d ", array[row][column]);
        }
        for (int i = 0; i < l; ++i) {
            row++;
            printf("%d ", array[row][column]);
        }
        l++;
        for (int i = 0; i < l; ++i) {
            column++;
            printf("%d ", array[row][column]);
        }
        for (int i = 0; i < l; ++i) {
            row--;
            printf("%d ", array[row][column]);
        }
        l++;
        if (l == n) {
            while (column != 0) {
                column--;
                printf("%d ", array[row][column]);
            }
            break;
        }
    }
    return 0;
}
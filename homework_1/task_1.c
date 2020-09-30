#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 0;
    printf("enter the number of rows and columns (n)\n");
    scanf("%d", &n);
    int** array = malloc(n * sizeof(int*));
    for (int i = 0; i != n; ++i) {
        array[i] = malloc(n * sizeof(int));
    }
    printf("enter the array (%d character(s) per line)\n", n);
    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != n; ++j) {
            scanf("%d", &array[i][j]);
        }
    }
    int row = n / 2, column = n / 2, l = 1;
    printf("%d ", array[row][column]);
    if (n == 1) {
        for (int i = 0; i != n; ++i) {
            free(array[i]);
        }
        free(array);
        return 0;
    }
    while (l < n) {
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
    for (int i = 0; i != n; ++i) {
        free(array[i]);
    }
    free(array);
    return 0;
}

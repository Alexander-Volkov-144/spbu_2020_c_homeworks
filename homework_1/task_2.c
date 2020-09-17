#include <stdio.h>

int main()
{
    int n = 0, m = 0;
    scanf("%d%d", &m, &n);
    int array[n];
    for (int i = 0; i != n; ++i) {
        scanf("%d", &array[i]);
    }
    for (int i = 0; i != n / 2; ++i) {
        int temporary = array[i];
        array[i] = array[n - i - 1];
        array[n - i - 1] = temporary;
    }
    for (int i = 0; i != (n - m) / 2; ++i) {
        int temporary = array[i];
        array[i] = array[n - m - i - 1];
        array[n - m - i - 1] = temporary;
    }
    for (int i = 0; i != m / 2; ++i) {
        int temporary = array[n - m + i];
        array[n - m + i] = array[n - 1 - i];
        array[n - 1 - i] = temporary;
    }
    for (int i = 0; i != n; ++i) {
        printf("%d ", array[i]);
    }
    return 0;
}
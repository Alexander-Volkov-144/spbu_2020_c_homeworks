#include <stdio.h>

int main()
{
    int n = 0;
    scanf("%d", &n);
    int array[n];
    for (int i = 0; i != n; ++i) {
        scanf("%d", &array[i]);
    }
    for (int i = 0; i != n - 1; ++i) {
        for (int j = 0; j != n - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                int temporary = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temporary;
            }
        }
    }
    int maximum = -2147483648, last = array[n - 1];
    for (int i = n - 2; i != -1; --i) {
        if (array[i] == last) {
            if (array[i] > maximum) {
                maximum = array[i];
                break;
            }
        } else {
            last = array[i];
        }
    }
    if (maximum == -2147483648) {
        printf("there are no such elements");
        return 0;
    }
    printf("%d", maximum);
    return 0;
}
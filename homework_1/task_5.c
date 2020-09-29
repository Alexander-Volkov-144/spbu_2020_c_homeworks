#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 0;
    printf("enter the number of elements in the array\n");
    scanf("%d", &n);
    int* array = malloc(n * sizeof(int));
    printf("enter array elements\n");
    for (int i = 0; i != n; ++i) {
        scanf("%d", &array[i]);
    }
    bool isFind = false; // переменная, указываюшая, найден ли максимум
    int maximum = 0, count = 0, j = 0, current = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (array[i] == array[j]) {
                if (!isFind) {
                    maximum = array[i];
                    isFind = true;
                } else {
                    if (array[i] > maximum)
                        maximum = array[i];
                }
            }
        }
    }
    if (!isFind)
        printf("there are no such elements");
    else
        printf("%d", maximum);
    free(array);
    return 0;
}

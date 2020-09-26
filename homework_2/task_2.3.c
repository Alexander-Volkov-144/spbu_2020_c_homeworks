#include <malloc.h>
#include <stdio.h>

void swap(int* x, int* y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
    return;
}

int main()
{
    int n = 0;
    printf("enter the number of elements in the array\n");
    scanf("%d", &n);
    int* array = malloc(n * sizeof(int));
    printf("enter elements separated by space\n");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &array[i]);
    }
    for (int i = 0; i < n - 1; ++i) {
        if (array[i] == 0) {
            for (int j = i + 1; j < n; ++j) {
                if (array[j] != 0) {
                    swap(&array[i], &array[j]); // если элемент равен нулю, то он заменяется на ближайший ненулевой
                    break;
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        printf("%d ", array[i]);
    }
    free(array);
    return 0;
}

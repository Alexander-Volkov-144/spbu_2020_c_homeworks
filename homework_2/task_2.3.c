#include <stdio.h>
#include <stdlib.h>

void swap(int* x, int* y) // функция, меняющая местами элементы
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void zeroShift(int* array, int n)
{ // функция, двигающая нули в конец
    for (int i = 0, j = 0; i < n; ++i) {
        if (array[i] != 0) {
            if (j < i) {
                swap(&array[j], &array[i]);
            }
            ++j;
        }
    }
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
    zeroShift(array, n);
    for (int i = 0; i < n; ++i) {
        printf("%d ", array[i]);
    }
    free(array);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int maxSize = 20;  // 20 - максимальное количество цифр в числе, которое может быть записано в  unsigned long long

int fillArray(int* array, unsigned long long x)
{
    int n = 0;
    while (x > 0) {
        array[n] = x % 10; // в массив записываются цифры числа
        n += 1;
        x /= 10;
    }
    return n; // возвращается количество элементов в массиве
}

void swap(int* x, int* y) // функция, меняющая местами два элемента массива
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int compare(const void* x, const void* y) // функция, сравнивающая два элемента массива для qsort
{
    return *(int*)x - *(int*)y;
}

void zeroMove(int* array)
{
    int i = 1;
    while (array[i] == 0) {
        ++i;
    }
    swap(&array[0], &array[i]);
}

int main()
{
    int numbers[maxSize];
    for (int i = 0; i < maxSize; ++i) {
        numbers[i] = 0;
    }
    unsigned long long x = 0;
    printf("enter a natural number\n");
    scanf("%d", &x);
    int n = fillArray(numbers, x);
    qsort(numbers, n, sizeof(int), compare);
    if (numbers[0] == 0)
        zeroMove(numbers);
    for (int i = 0; i < n; ++i) {
        printf("%d", numbers[i]);
    }
    return 0;
}

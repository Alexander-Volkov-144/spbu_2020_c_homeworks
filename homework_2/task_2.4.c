#include <stdio.h>

void swap(int* x, int* y) // функция, меняющая местами два элемента массива
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
    return;
}

int main()
{
    int numbers[10]; // 10 - максимальное количество цифр в числе, которое может быть записано в  int
    int x = 0;
    printf("enter a natural number\n");
    scanf("%d", &x);
    int n = 0;
    while (x > 0) {
        numbers[n] = x % 10; // в массив записываются цифры числа
        n += 1;
        x /= 10;
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < n - i; ++j) {
            if (numbers[j] > numbers[j + 1]) {
                swap(&numbers[j], &numbers[j + 1]); // массив сортируется по неубыванию
            }
        }
    }
    if (numbers[0] == 0) { // если на первом месте оказался 0, то нужно заменить его на цифру > 0
        for (int i = 1;; ++i) {
            if (numbers[i] != 0) {
                swap(&numbers[0], &numbers[i]);
                break;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        printf("%d", numbers[i]);
    }
    return 0;
}
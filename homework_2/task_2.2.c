#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void randomArray(int* array, int n)
{
    bool digits[10]; // создается массив для цифр
    for (int i = 0; i < 10; ++i) {
        digits[i] = true; // в каждую ячейку записывается true, что означает, что цифра еще не использовалась
    }
    int r = 0;
    while (r == 0) { // необходимо, чтобы первая цифра была ненулевой
        r = rand() % 10;
    }
    array[0] = r;
    digits[r] = false;
    for (int i = 1; i < n; ++i) {
        while (!digits[r]) { // находится цифра, которая еще не использовалась
            r = rand() % 10;
        }
        digits[r] = false; // эту цифру больше нельзя использовать
        array[i] = r;
    }
}

void generate(int* array, int x, int n) // функция превращает число в массив с цифрами этого числа
{
    for (int i = n - 1; i > -1; --i) {
        array[i] = x % 10;
        x /= 10;
    }
}

bool check(int x, int n) // функция проверяет, что пользователь ввел число с необходимым количеством цифр
{
    while (x > 0) {
        x /= 10;
        --n;
    }
    return n != 0;
}

int main()
{
    srand(time(NULL));
    int n = 0;
    printf("enter the quantity of digits in the number that you will guess (from 4 to 9)\n");
    scanf("%d", &n);
    while (n < 4 || n > 9) {
        printf("please enter the number between four and nine\n");
        scanf("%d", &n);
    }
    int* hidden = malloc(n * sizeof(int)); // создается массив для числа, которое нужно угадать
    int* assumption = malloc(n * sizeof(int)); // создается массив для числа, которое будет предлагать игрок
    randomArray(hidden, n); // вызывается функция для генерации случайного числа
    printf("A - number of full matches, B - number of partial matches (wrong position)\n");
    printf("enter the number\n");
    int a = 0, b = 0, x = 0;
    while (a != n) {
        a = 0; // обнуляются счетчики
        b = 0;
        scanf("%d", &x);
        while (check(x, n)) { // проверяется, что пользователь ввел число с необходимым количеством цифр
            printf("please enter a %d-digit number\n", n);
            scanf("%d", &x);
        }
        generate(assumption, x, n); // число записывается в массив
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (hidden[i] == assumption[j]) { // проверяется совпадение элементов двух массивов
                    b += 1;
                    if (i == j) {
                        b -= 1;
                        a += 1;
                    }
                }
            }
        }
        printf("A%dB%d\n", a, b);
    }
    printf("you win");
    free(hidden);
    free(assumption);
    return 0;
}
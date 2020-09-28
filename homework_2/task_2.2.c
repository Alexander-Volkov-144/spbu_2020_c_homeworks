#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int N = 10; // количество цифр

void generateRandomArray(int* array, int n)
{
    bool* digits = malloc(N * sizeof(bool)); // создается массив для цифр
    memset(digits, 0, N * sizeof(bool));
    int currentFigure = 0;
    do { // необходимо, чтобы первая цифра была ненулевой
        currentFigure = rand() % 10;
    } while (currentFigure == 0);
    for (int i = 0; i < n; ++i) {
        while (digits[currentFigure]) { // находится цифра, которая еще не использовалась
            currentFigure = rand() % 10;
        }
        digits[currentFigure] = true; // эту цифру больше нельзя использовать
        array[i] = currentFigure;
    }
    free(digits);
}

void makeArrayFromNumber(int* numbers, int x, int n) // функция превращает число в массив с цифрами этого числа
{
    for (int i = n - 1; i > -1; --i) {
        numbers[i] = x % 10;
        x /= 10;
    }
}

bool isCorrectNumberOfDigits(int x, int n) // функция проверяет, что пользователь ввел число с необходимым количеством цифр
{
    return x / pow(10, n - 1) >= 1 && x / pow(10, n - 1) <= 9;
}

void checkNumberOfMatches(int* hiddenNumbers, int* assumptiveNumbers, int* a, int* b, int n)
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (hiddenNumbers[i] == assumptiveNumbers[j]) { // проверяется совпадение элементов двух массивов
                i == j ? ++*a : ++*b;
            }
        }
    }
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
    int* hiddenNumbers = malloc(n * sizeof(int)); // создается массив для числа, которое нужно угадать
    int* assumptiveNumbers = malloc(n * sizeof(int)); // создается массив для числа, которое будет предлагать игрок
    generateRandomArray(hiddenNumbers, n); // вызывается функция для генерации случайного числа
    printf("A - number of full matches, B - number of partial matches (wrong position)\n");
    printf("enter the number\n");
    int a = 0, b = 0, x = 0;
    while (a != n) {
        a = 0; // обнуляются счетчики
        b = 0;
        scanf("%d", &x);
        while (!isCorrectNumberOfDigits(x, n)) { // проверяется, что пользователь ввел число с необходимым количеством цифр
            printf("please enter a %d-digit number\n", n);
            scanf("%d", &x);
        }
        makeArrayFromNumber(assumptiveNumbers, x, n); // число записывается в массив
        checkNumberOfMatches(hiddenNumbers, assumptiveNumbers, &a, &b, n); // проверяет количество совпадающих значений
        printf("A%dB%d\n", a, b);
    }
    printf("you win");
    free(hiddenNumbers);
    free(assumptiveNumbers);
    return 0;
}
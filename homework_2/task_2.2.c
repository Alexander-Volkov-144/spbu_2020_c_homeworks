#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    int sec[4];
    sec[0] = rand() % 10; // генерируется первый элемент
    while (sec[0] == 0) {
        sec[0] = rand() % 10;
    }
    sec[1] = rand() % 10; // генерируется второй элемент
    while (sec[1] == sec[0]) {
        sec[1] = rand() % 10;
    }
    sec[2] = rand() % 10; // генерируется третий элемент
    while (sec[2] == sec[1] || sec[2] == sec[0]) {
        sec[2] = rand() % 10;
    }
    sec[3] = rand() % 10; // генерируется четвертый элемент
    while (sec[3] == sec[2] || sec[3] == sec[1] || sec[3] == sec[0]) {
        sec[3] = rand() % 10;
    }
    int A = 0, B = 0;
    printf("A - number of full matches, B - number of partial matches (wrong position)\n");
    while (A != 4) {
        int x = 0;
        printf("enter a four-digit number\n");
        scanf("%d", &x);
        int guess[4];
        for (int i = 3; i != -1; i--) {
            guess[i] = x % 10;
            x /= 10;
        }
        A = 0;
        B = 0;
        for (int i = 0; i != 4; ++i) {
            for (int j = 0; j != 4; ++j) {
                if (sec[i] == guess[j]) {
                    if (i == j) {
                        A += 1;
                    } else {
                        B += 1;
                    }
                }
            }
        }
        printf("%dA%dB\n", A, B);
    }
    printf("you win");
    return 0;
}
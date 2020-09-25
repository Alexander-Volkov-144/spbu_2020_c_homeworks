#include <stdio.h>

int next(int* sol, int num, int sum)
{
    if (sum <= 0) {
        for (int j = num; sol[j] != 0; j++) {
            sol[num] = 0;
        }
        int i = 0;
        for (; sol[i + 1] != 0; i++) {
            printf("%d + ", sol[i]);
        }
        printf("%d\n", sol[i]);
    } else {
        for (int i = sol[num - 1]; i > 0; i--) {
            if (sum - i >= 0) {
                sol[num] = i;
                next(sol, num + 1, sum - i);
            }
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int sol[n + 1];
    for (int i = 0; i != n + 1; ++i) {
        sol[i] = 0;
    }
    for (int i = n - 1; i != 0; i--) {
        sol[0] = i;
        next(sol, 1, n - i);
    }

    return 0;
}

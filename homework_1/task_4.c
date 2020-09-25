#include <stdbool.h>
#include <stdio.h>

int main()
{
    int n = 0;
    scanf("%d", &n);
    for (int i = 2; i < n; ++i) {
        bool check = true;
        for (int j = 2; j * j <= i; ++j) {
            if (i % j == 0) {
                check = false;
                break;
            }
        }
        if (check) {
            printf("%d ", i);
        }
    }
    return 0;
}

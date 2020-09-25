#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>

int main()
{
    int n = 0;
    scanf("%d", &n);
    int* array = malloc(n * sizeof(int));
    for (int i = 0; i != n; ++i) {
        scanf("%d", &array[i]);
    }
    int maximum = -2147483648, count = 0, j = 0, current = 0;
    for (int i = 0; i < n - 1; ++i) {
        j = i + 1;
        bool notFind = true;
        current = array[i];
        while (j < n) {
            if (array[i] == array[j]) {
                notFind = false;
                break;
            }
            j++;
        }
        if (!notFind && current > maximum)
            maximum = current;
    }
    if (maximum == -2147483648) {
        printf("there are no such elements");
        return 0;
    }
    printf("%d", maximum);
    free(array);
    return 0;
}

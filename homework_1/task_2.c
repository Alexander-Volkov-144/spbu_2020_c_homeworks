#include "../library/commonUtils/reverseArray.h"
#include <malloc.h>
#include <stdio.h>

int main()
{
    int n = 0, m = 0;
    scanf("%d%d", &m, &n);
    int* array = malloc(n * sizeof(int));
    for (int i = 0; i != n; ++i) {
        scanf("%d", &array[i]);
    }
    reverseArray(array, array + n - 1);
    reverseArray(array, array + n - m - 1);
    reverseArray(array + n - m, array + n - 1);
    for (int i = 0; i != n; ++i) {
        printf("%d ", array[i]);
    }
    free(array);
    return 0;
}

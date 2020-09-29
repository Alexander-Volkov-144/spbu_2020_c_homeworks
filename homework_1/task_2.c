#include "../library/commonUtils/reverseArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int n = 0, m = 0;
    printf("enter enter the length of the first part of the array (m)\n");
    scanf("%d", &m);
    printf("enter the length of the second part of the array (n)\n");
    scanf("%d", &n);
    int* array = malloc((n + m) * sizeof(int));
    memset(array, 0, (n + m) * sizeof(int));
    printf("enter array elements\n");
    for (int i = 0; i != n + m; ++i) {
        scanf("%d", &array[i]);
    }
    reverseArray(array, n + m);
    reverseArray(array, n);
    reverseArray(array + n, m);
    for (int i = 0; i != n + m; ++i) {
        printf("%d ", array[i]);
    }
    free(array);
    return 0;
}

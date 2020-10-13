#include <stdio.h>
#include <stdlib.h>

int* mergeArrays(int* array1, int size1, int* array2, int size2)
{
    int* newArray = (int*)malloc((size1 + size2) * sizeof(int));
    int i = 0, j = 0; // для исходных массивов
    int z = 0; // для нового массива
    while (i < size1 && j < size2) {
        if (array1[i] > array2[j]) {
            newArray[z] = array1[i];
            ++z;
            ++i;
        } else {
            newArray[z] = array2[j];
            ++z;
            ++j;
        }
    }
    while (i < size1) {
        newArray[z] = array1[i];
        ++z;
        ++i;
    }
    while (j < size2) {
        newArray[z] = array2[j];
        ++z;
        ++j;
    }
    return newArray;
}

int* createArray(int size)
{
    int* temporaryArray = (int*)malloc(size * sizeof(int));
    printf("enter the elements\n");
    for (int i = 0; i < size; ++i) {
        scanf("%d", &(temporaryArray[i]));
    }
    return temporaryArray;
}

void printArray(int* array, int size)
{
    for (int i = 0; i < size; ++i) {
        printf("%d ", array[i]);
    }
}

int main()
{
    int n1 = 0;
    printf("enter the number of elements in the first array\n");
    scanf("%d", &n1);
    int n2 = 0;
    int* array1 = createArray(n1);
    printf("enter the number of elements in the second array\n");
    scanf("%d", &n2);
    int* array2 = createArray(n2);
    int* array3 = mergeArrays(array1, n1, array2, n2);
    printArray(array3, n1 + n2);
    free(array1);
    free(array2);
    free(array3);
    return 0;
}

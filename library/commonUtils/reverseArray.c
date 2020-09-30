#include "reverseArray.h"

void reverseArray(int* array, int length)
{
    for (int i = 0; i != length / 2; ++i) {
        int tmp = array[i];
        array[i] = array[length - 1 - i];
        array[length - 1 - i] = tmp;
    }
};
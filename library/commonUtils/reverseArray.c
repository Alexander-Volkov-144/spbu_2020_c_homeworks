#include "reverseArray.h"
#include <malloc.h>

void reverseArray(int* begin, int* end)
{
    int n = end - begin + 1;
    for (int i = 0; i != n / 2; ++i) {
        int tmp = begin[i];
        begin[i] = begin[n - 1 - i];
        begin[n - 1 - i] = tmp;
    }
    return;
};
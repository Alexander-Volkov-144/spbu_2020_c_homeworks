#include "hashComputation.h"
#include <string.h>

int getHash(char* key, int module)
{
    int size = (int)strlen(key);
    int currentHash = 0;
    for (int i = 0; i < size; ++i) {
        currentHash = ((currentHash * 2) + (key[i] - 'a')) % module;
    }
    return currentHash;
}
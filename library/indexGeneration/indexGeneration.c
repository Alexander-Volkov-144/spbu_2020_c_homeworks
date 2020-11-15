#include "indexGeneration.h"

int getIndex(int hash, int module, int numberOfProbes)
{
    return (hash + ((numberOfProbes - 1) * numberOfProbes) / 2) % module;
}

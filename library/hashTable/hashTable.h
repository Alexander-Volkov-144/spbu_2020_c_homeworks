#ifndef SPBU_2020_C_HOMEWORKS_HASHTABLE_H
#define SPBU_2020_C_HOMEWORKS_HASHTABLE_H

#include <stdbool.h>

typedef struct HashTable HashTable;

bool addElement(HashTable* table, char* key, int value);

HashTable* createHashTable(int polynomFactor);

void destroyHashTable(HashTable* table);

bool getValue(HashTable* table, char* key, int* result);

double getLoadFactor(HashTable* hashTable);

double getAverageNumberOfProbes(HashTable* table);

int getMaximumNumberOfProbes(HashTable* table);

void printAllElementsWithCertainNumberOfProbes(HashTable* table, int numberOfProbes);

int getElementCount(HashTable* table);

int getBucketCount(HashTable* table);

void printElementsWithBiggestValues(HashTable* table, int numberOfElements);

#endif //SPBU_2020_C_HOMEWORKS_HASHTABLE_H

#include "hashTable.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const double maxLoadFactor = 0.7;

enum CellType {
    empty,
    used,
    deleted
};

typedef struct HashElement {
    char* key;
    int value;
    int numberOfProbes;
} HashElement;

struct HashTable {
    HashElement** hashTable;
    enum CellType* types;
    int bucketCount;
    int elementCount;
    int polynomFactor;
};

bool addElementWithProbes(HashTable* table, char* key, int value, int numberOfProbes);

double getLoadFactor(HashTable* hashTable)
{
    return (double)hashTable->elementCount / (float)hashTable->bucketCount;
}

HashElement* createHashElement(char* key, int value, int numberOfProbes)
{
    HashElement* newElement = (HashElement*)malloc(sizeof(HashElement));
    int keySize = (int)strlen(key);
    newElement->key = (char*)malloc(sizeof(char) * (keySize + 1));
    strcpy(newElement->key, key);
    newElement->value = value;
    newElement->numberOfProbes = numberOfProbes;
    return newElement;
}

HashTable* createHashTableWithSize(int polynomFactor, int size)
{
    HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));
    newTable->hashTable = (HashElement**)malloc(sizeof(HashElement*) * size);
    newTable->types = (enum CellType*)malloc(sizeof(enum CellType) * size);
    memset(newTable->types, (int)empty, size * sizeof(enum CellType));
    newTable->bucketCount = size;
    memset(newTable->hashTable, 0, size * sizeof(HashElement*));
    newTable->elementCount = 0;
    newTable->polynomFactor = polynomFactor;
    return newTable;
}

HashTable* createHashTable(int polynomFactor)
{
    return createHashTableWithSize(polynomFactor, 1);
}

int getHash(char* key, int polynomFactor, int module)
{
    int size = (int)strlen(key);
    int currentHash = 0;
    for (int i = 0; i < size; ++i) {
        currentHash = ((currentHash * polynomFactor) + (key[i] - 'a')) % module;
    }
    return currentHash;
}

void destroyHashTable(HashTable* table)
{
    for (int i = 0; i < table->bucketCount; ++i) {
        if (used == table->types[i])
            free(table->hashTable[i]->key);
        free(table->hashTable[i]);
    }
    free(table->hashTable);
    free(table->types);
    free(table);
}

void expandTable(HashTable* table)
{
    HashElement** oldElements = table->hashTable;
    enum CellType* oldTypes = table->types;

    int oldSize = table->bucketCount;
    int size = table->bucketCount * 2;

    table->hashTable = (HashElement**)malloc(sizeof(HashElement*) * size);
    table->types = (enum CellType*)malloc(sizeof(enum CellType) * size);
    memset(table->hashTable, 0, size * sizeof(HashElement*));
    memset(table->types, (int)empty, size * sizeof(enum CellType));
    table->bucketCount = size;
    table->elementCount = 0;

    for (int i = 0; i < oldSize; ++i) {
        if (oldTypes[i] == used) {
            HashElement* element = oldElements[i];
            addElementWithProbes(table, element->key, element->value, element->numberOfProbes);
            free(element->key);
            free(element);
        }
    }
    free(oldElements);
    free(oldTypes);
}

bool addElement(HashTable* table, char* key, int value)
{
    addElementWithProbes(table, key, value, 1);
    return true;
}

bool addElementWithProbes(HashTable* table, char* key, int value, int numberOfProbes)
{
    int startIndex = getHash(key, table->polynomFactor, table->bucketCount);
    int currentIndex = startIndex;
    int currentNumberOfProbes = 1;
    while (table->types[currentIndex] == used) {
        if (0 == strcmp(key, table->hashTable[currentIndex]->key)) {
            table->hashTable[currentIndex]->value += value;
            if (currentNumberOfProbes > table->hashTable[currentIndex]->numberOfProbes) {
                table->hashTable[currentIndex]->numberOfProbes = currentNumberOfProbes;
            }
            return true;
        }
        currentIndex = (currentIndex + (currentNumberOfProbes + currentNumberOfProbes * currentNumberOfProbes) / 2) % table->bucketCount;
        ++currentNumberOfProbes;
        if (currentIndex == startIndex)
            return false;
    }
    HashElement* newElement = createHashElement(key, value, numberOfProbes);
    newElement->numberOfProbes = currentNumberOfProbes;
    table->hashTable[currentIndex] = newElement;
    table->types[currentIndex] = used;
    table->elementCount++;

    if (getLoadFactor(table) > maxLoadFactor)
        expandTable(table);

    return true;
}

double getAverageNumberOfProbes(HashTable* table)
{
    int totalNumberOfProbes = 0;
    for (int i = 0; i < table->bucketCount; ++i) {
        if (used == table->types[i])
            totalNumberOfProbes += table->hashTable[i]->numberOfProbes;
    }
    return (double)totalNumberOfProbes / table->elementCount;
}

int getMaximumNumberOfProbes(HashTable* table)
{
    int maximumNumberOfProbes = 0;
    for (int i = 0; i < table->bucketCount; ++i) {
        if (used == table->types[i])
            if (table->hashTable[i]->numberOfProbes > maximumNumberOfProbes)
                maximumNumberOfProbes = table->hashTable[i]->numberOfProbes;
    }
    return maximumNumberOfProbes;
}

void printAllElementsWithCertainNumberOfProbes(HashTable* table, int numberOfProbes)
{
    for (int i = 0; i < table->bucketCount; ++i) {
        if (used == table->types[i]) {
            if (table->hashTable[i]->numberOfProbes == numberOfProbes) {
                for (int j = 0; table->hashTable[i]->key[j] != '\0'; ++j) {
                    printf("%c", table->hashTable[i]->key[j]);
                }
                printf(" ");
            }
        }
    }
}

int getElementCount(HashTable* table)
{
    return table->elementCount;
}

int getBucketCount(HashTable* table)
{
    return table->bucketCount;
}

bool notInArray(const int* array, int size, int value)
{
    for (int i = 0; i < size; ++i) {
        if (array[i] == value)
            return false;
    }
    return true;
}

void printElementsWithBiggestValues(HashTable* table, int numberOfElements)
{
    printf("elements with biggest values:\n");
    if (numberOfElements > table->elementCount)
        numberOfElements = table->elementCount;
    int* alreadyCounted = (int*)malloc(numberOfElements * sizeof(int));
    memset(alreadyCounted, -1, numberOfElements * sizeof(int));
    int maximumValue = 0;
    int notFound = true;
    char* foundKey = NULL;
    for (int i = 0; i < numberOfElements; ++i) {
        maximumValue = 0;
        notFound = true;
        for (int j = 0; j < table->bucketCount; ++j) {
            if (notInArray(alreadyCounted, numberOfElements, j)) {
                if (used == table->types[j]) {
                    if (table->hashTable[j]->value > maximumValue || notFound) {
                        notFound = false;
                        foundKey = table->hashTable[j]->key;
                        maximumValue = table->hashTable[j]->value;
                        alreadyCounted[i] = j;
                    }
                }
            }
        }
        for (int j = 0; foundKey[j] != '\0'; ++j) {
            printf("%c", foundKey[j]);
        }
        printf(" %d\n", maximumValue);
    }
    free(alreadyCounted);
}

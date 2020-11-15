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

    int (* getHash)(char*, int);

    int (* getIndex)(int, int, int);
};

void addElementWithProbes(HashTable* table, char* key, int value, int numberOfProbes);

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

HashTable* createHashTableWithSize(int size, int (* getHash)(char*, int), int (* getIndex)(int, int, int))
{
    HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));
    newTable->hashTable = (HashElement**)malloc(sizeof(HashElement*) * size);
    newTable->types = (enum CellType*)malloc(sizeof(enum CellType) * size);
    memset(newTable->types, (int)empty, size * sizeof(enum CellType));
    newTable->bucketCount = size;
    memset(newTable->hashTable, 0, size * sizeof(HashElement*));
    newTable->elementCount = 0;
    newTable->getHash = getHash;
    newTable->getIndex = getIndex;
    return newTable;
}

HashTable* createHashTable(int (* getHash)(char*, int), int (* getIndex)(int, int, int))
{
    return createHashTableWithSize(1, getHash, getIndex);
}

void destroyHashTable(HashTable* table)
{
    for (int i = 0; i < table->bucketCount; ++i) {
        if (table->types[i] == used)
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

void addElement(HashTable* table, char* key, int value)
{
    addElementWithProbes(table, key, value, 1);
}

void addElementWithProbes(HashTable* table, char* key, int value, int numberOfProbes)
{
    int hash = table->getHash(key, table->bucketCount);
    int currentNumberOfProbes = 1;
    int currentIndex = table->getIndex(hash, table->bucketCount, currentNumberOfProbes);
    while (table->types[currentIndex] == used) {
        if (strcmp(key, table->hashTable[currentIndex]->key) == 0) {
            table->hashTable[currentIndex]->value += value;
            if (currentNumberOfProbes > table->hashTable[currentIndex]->numberOfProbes) {
                table->hashTable[currentIndex]->numberOfProbes = currentNumberOfProbes;
            }
            return;
        }
        ++currentNumberOfProbes;
        currentIndex = table->getIndex(hash, table->bucketCount, currentNumberOfProbes);
    }
    HashElement* newElement = createHashElement(key, value, numberOfProbes);
    newElement->numberOfProbes = currentNumberOfProbes;
    table->hashTable[currentIndex] = newElement;
    table->types[currentIndex] = used;
    table->elementCount++;
    if (getLoadFactor(table) > maxLoadFactor)
        expandTable(table);
}

bool removeElement(HashTable* table, char* key)
{
    int hash = table->getHash(key, table->bucketCount);
    int currentNumberOfProbes = 1;
    int startIndex = table->getIndex(hash, table->bucketCount, currentNumberOfProbes);
    int currentIndex = startIndex;
    do {
        if (table->types[currentIndex] == used && (strcmp(key, table->hashTable[currentIndex]->key) == 0)) {
            table->types[currentIndex] = deleted;
            free(table->hashTable[currentIndex]->key);
            free(table->hashTable[currentIndex]);
            table->hashTable[currentIndex] = NULL;
            table->elementCount--;
            return true;
        }
        ++currentNumberOfProbes;
        currentIndex = table->getIndex(hash, table->bucketCount, currentNumberOfProbes);
    } while (currentIndex != startIndex);
    return false;
}

double getAverageNumberOfProbes(HashTable* table)
{
    if (table->elementCount == 0)
        return 0;
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
        if (table->types[i] == used && table->hashTable[i]->numberOfProbes > maximumNumberOfProbes)
            maximumNumberOfProbes = table->hashTable[i]->numberOfProbes;
    }
    return maximumNumberOfProbes;
}

void printAllElementsWithCertainNumberOfProbes(HashTable* table, int numberOfProbes)
{
    for (int i = 0; i < table->bucketCount; ++i) {
        if (used == table->types[i] && table->hashTable[i]->numberOfProbes == numberOfProbes) {
            for (int j = 0; table->hashTable[i]->key[j] != '\0'; ++j) {
                printf("%c", table->hashTable[i]->key[j]);
            }
            printf(" ");
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

bool inArray(const int* array, int size, int value)
{
    for (int i = 0; i < size; ++i) {
        if (array[i] == value)
            return true;
    }
    return false;
}

bool isLarger(HashTable* table, int* alreadyCounted, int numberOfElements, int index, int maximumValue, bool notFound)
{
    return (!inArray(alreadyCounted, numberOfElements, index)) && (table->types[index] == used) && (table->hashTable[index]->value > maximumValue || notFound);
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
            if (isLarger(table, alreadyCounted, numberOfElements, j, maximumValue, notFound)) {
                notFound = false;
                foundKey = table->hashTable[j]->key;
                maximumValue = table->hashTable[j]->value;
                alreadyCounted[i] = j;
            }
        }
        for (int j = 0; foundKey[j] != '\0'; ++j) {
            printf("%c", foundKey[j]);
        }
        printf(" %d\n", maximumValue);
    }
    free(alreadyCounted);
}

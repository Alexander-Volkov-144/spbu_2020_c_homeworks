#include "hashTable.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

const double maxLoadFactor = 0.7;

enum CellType {
    empty, used, deleted
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

double getLoadFactor(HashTable* hashTable)
{
    return (double)hashTable->elementCount / (float)hashTable->bucketCount;
}

HashElement* createHashElement(char* key, int value)
{
    HashElement* newElement = (HashElement*)malloc(sizeof(HashElement));
    int keySize = (int)strlen(key);
    newElement->key = (char*)malloc(sizeof(char) * keySize);
    strcpy(newElement->key, key);
    newElement->value = value;
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
        if (oldTypes[i] != used)
            continue;
        HashElement* element = oldElements[i];
        addElement(table, element->key, element->value);
    }

    free(oldElements);
    free(oldTypes);
}

bool addElement(HashTable* table, char* key, int value)
{
    int startIndex = getHash(key, table->polynomFactor, table->bucketCount);
    HashElement* newElement = createHashElement(key, value);
    int currentIndex = startIndex;
    while (table->types[currentIndex] == used) {
        currentIndex = (currentIndex + 1) % table->bucketCount;
        if (currentIndex == startIndex) {
            return false;
        }
    }
    table->hashTable[currentIndex] = newElement;
    table->types[currentIndex] = used;
    table->elementCount++;

    if (getLoadFactor(table) > maxLoadFactor)
        expandTable(table);

    return true;
}

bool getValue(HashTable* table, char* key, int* result)
{
    int startIndex = getHash(key, table->polynomFactor, table->bucketCount);
    int currentIndex = startIndex;
    printf("%d", table->types[0]);
    while (table->types[currentIndex] != empty) {
        if (strcmp(table->hashTable[currentIndex]->key, key) == 0) {
            *result = table->hashTable[currentIndex]->value;
            return true;
        }
        currentIndex = (currentIndex + 1) % table->bucketCount;
        if (currentIndex == startIndex) {
            return false;
        }
    }
    return false;
}

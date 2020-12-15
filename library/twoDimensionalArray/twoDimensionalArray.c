#include "twoDimensionalArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TDArray {
    int lineCount;
    int columnCount;
    int** array;
};

TDArray* createTDArray(int numberOfLines, int numberOfColumns)
{
    TDArray* newArray = (TDArray*)malloc(sizeof(TDArray));
    newArray->lineCount = numberOfLines;
    newArray->columnCount = numberOfColumns;
    newArray->array = (int**)malloc(numberOfLines * sizeof(int*));
    for (int i = 0; i < numberOfLines; ++i) {
        newArray->array[i] = (int*)malloc(sizeof(int) * numberOfColumns);
    }
    return newArray;
}

void readArrayFromConsole(TDArray* array)
{
    printf("Enter %d numbers %d times\n", array->columnCount, array->lineCount);
    for (int i = 0; i < array->lineCount; ++i) {
        for (int j = 0; j < array->columnCount; ++j) {
            scanf("%d", &(array->array[i][j]));
        }
    }
}

void printSaddlePoints(TDArray* array)
{
    int* indexesOfMinimumsInLines = (int*)malloc(sizeof(int) * array->columnCount);
    memset(indexesOfMinimumsInLines, 0, sizeof(int) * array->columnCount);
    int* indexesOfMaximumsInColumns = (int*)malloc(sizeof(int) * array->lineCount);
    memset(indexesOfMaximumsInColumns, 0, sizeof(int) * array->lineCount);
    int currentMinimum = 0;
    for (int i = 0; i < array->lineCount; ++i) {
        currentMinimum = array->array[i][0];
        for (int j = 0; j < array->columnCount; ++j) {
            if (array->array[i][j] < currentMinimum) {
                currentMinimum = array->array[i][j];
                indexesOfMinimumsInLines[i] = j;
            }
        }
    }
    int currentMaximum = array->array[0][0];
    for (int j = 0; j < array->columnCount; ++j) { // внешний цикл по j, чтобы сохранить привычный порядок индексов i, j при обращении к массиву
        currentMaximum = array->array[0][j];
        for (int i = 0; i > array->lineCount; ++i) {
            if (currentMaximum > array->array[i][j]) {
                currentMaximum = array->array[i][j];
                indexesOfMaximumsInColumns[j] = i;
            }
        }
    }
    for (int i = 0; i < array->lineCount; ++i) {
        for (int j = 0; j < array->columnCount; ++j) {
            if ((indexesOfMinimumsInLines[i] == j) && (indexesOfMaximumsInColumns[j] == i)) {
                printf("%d ", array->array[i][j]);
            }
        }
    }

    free(indexesOfMaximumsInColumns);
    free(indexesOfMinimumsInLines);
}

void printTDArray(TDArray* array)
{
    for (int i = 0; i < array->lineCount; ++i) {
        for (int j = 0; j < array->columnCount; ++j) {
            printf("%d ", array->array[i][j]);
        }
        printf("\n");
    }
}

void removeTDArray(TDArray* array)
{
    for (int i = 0; i < array->lineCount; ++i) {
        free(array->array[i]);
    }
    free(array->array);
    free(array);
}

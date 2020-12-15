#ifndef SPBU_2020_C_HOMEWORKS_TWODIMENSIONALARRAY_H
#define SPBU_2020_C_HOMEWORKS_TWODIMENSIONALARRAY_H

typedef struct TDArray TDArray;

TDArray* createTDArray(int numberOfLines, int numberOfColumns);

void readArrayFromConsole(TDArray* array);

void printTDArray(TDArray* array);

void printSaddlePoints(TDArray* array);

void removeTDArray(TDArray* array);

#endif //SPBU_2020_C_HOMEWORKS_TWODIMENSIONALARRAY_H

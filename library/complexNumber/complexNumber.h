#ifndef SPBU_2020_C_HOMEWORKS_COMPLEXNUMBER_H
#define SPBU_2020_C_HOMEWORKS_COMPLEXNUMBER_H

typedef struct complexNumber complexNumber;

complexNumber* createComplexNumber(double realPart, double imaginaryPart);

complexNumber* addComplexNumber(complexNumber* x, complexNumber* y);

complexNumber* subtractComplexNumber(complexNumber* x, complexNumber* y);

complexNumber* multiplyComplexNumbers(complexNumber* x, complexNumber* y);

complexNumber* divideComplexNumbers(complexNumber* x, complexNumber* y);

void deleteComplexNumber(complexNumber* x);

void printComplexNumber(complexNumber* x);

#endif //SPBU_2020_C_HOMEWORKS_COMPLEXNUMBER_H

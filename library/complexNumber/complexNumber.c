#include "complexNumber.h"
#include <stdio.h>
#include <stdlib.h>

struct complexNumber {
    double realPart;
    double imaginaryPart;
};

complexNumber* createComplexNumber(double realPart, double imaginaryPart)
{
    complexNumber* newNumber = (complexNumber*)malloc(sizeof(complexNumber));
    newNumber->realPart = realPart;
    newNumber->imaginaryPart = imaginaryPart;
    return newNumber;
}

complexNumber* addComplexNumber(complexNumber* x, complexNumber* y)
{
    complexNumber* newNumber = createComplexNumber(x->realPart + y->realPart, x->imaginaryPart + y->imaginaryPart);
    return newNumber;
}

complexNumber* subtractComplexNumber(complexNumber* x, complexNumber* y)
{
    complexNumber* newNumber = createComplexNumber(x->realPart - y->realPart, x->imaginaryPart - y->imaginaryPart);
    return newNumber;
}

complexNumber* multiplyComplexNumbers(complexNumber* x, complexNumber* y)
{
    complexNumber* newNumber = createComplexNumber(x->realPart * y->realPart - x->imaginaryPart * y->imaginaryPart, x->realPart * y->imaginaryPart + y->realPart * x->imaginaryPart);
    return newNumber;
}

complexNumber* divideComplexNumbers(complexNumber* x, complexNumber* y)
{
    if (y->realPart == 0 && y->imaginaryPart == 0) {
        printf("error, division by zero\n");
        return NULL;
    }
    complexNumber* newNumber = createComplexNumber((x->realPart * y->realPart + x->imaginaryPart * y->imaginaryPart) / (y->realPart * y->realPart + y->imaginaryPart * y->imaginaryPart), (y->realPart * x->imaginaryPart - x->realPart * y->imaginaryPart) / (y->realPart * y->realPart + y->imaginaryPart * y->imaginaryPart));
    return newNumber;
}

void deleteComplexNumber(complexNumber* x)
{
    x->realPart = 0;
    x->imaginaryPart = 0;
    free(x);
}

void printComplexNumber(complexNumber* x)
{
    if (x->realPart == 0) {
        printf("%lfi\n", x->imaginaryPart);
    } else {
        if (x->imaginaryPart == 0) {
            printf("%lf\n", x->realPart);
        } else {
            printf("%lf + (%lf)i\n", x->realPart, x->imaginaryPart);
        }
    }
}

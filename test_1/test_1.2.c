#include "../library/complexNumber/complexNumber.h"

int main()
{
    complexNumber* a = createComplexNumber(1, 1);
    complexNumber* b = createComplexNumber(2, 2);

    printComplexNumber(a);
    printComplexNumber(b);

    complexNumber* c = addComplexNumber(a, b);
    printComplexNumber(c);

    complexNumber* d = subtractComplexNumber(a, b);
    printComplexNumber(d);

    complexNumber* e = multiplyComplexNumbers(a, b);
    printComplexNumber(e);

    complexNumber* f = divideComplexNumbers(a, b);
    printComplexNumber(f);

    deleteComplexNumber(a);
    deleteComplexNumber(b);
    deleteComplexNumber(c);
    deleteComplexNumber(d);
    deleteComplexNumber(e);
    deleteComplexNumber(f);
}

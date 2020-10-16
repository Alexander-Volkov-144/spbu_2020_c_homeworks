#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define SD sizeof(double)

bool convertToBytes(double number, unsigned char* numberInBytes)
{
    unsigned char* reversedNumberInBytes = (unsigned char*) &number;
    for (int i = 0; i < SD; ++i) {
        numberInBytes[i] = reversedNumberInBytes[SD - (1 + i)];
    }
    return true;
}

char getSignOfNumber(unsigned char* numberInBytes)
{
    return ((numberInBytes[0] >> 7 == 1) ? '-' : '+');
}

int getExponentOfNumber(unsigned char* numberInBytes)
{
    int exponentOfNumber = (int) (numberInBytes[0] & 0b01111111);
    exponentOfNumber <<= 4;
    exponentOfNumber += (int) (numberInBytes[1] >> 4);
    exponentOfNumber -= 1023;
    return exponentOfNumber;
}

double getSignificandOfNumber(unsigned char* numberInBytes)
{
    unsigned long long fractionalPart = (numberInBytes[1] & 0b00001111);
    fractionalPart <<= 8;
    for (int i = 2; i < SD; i++) {
        fractionalPart += (numberInBytes[i] & 0b11111111);
        fractionalPart <<= 8;
    }
    fractionalPart >>= 8;
    unsigned long long div = 1;
    div <<= 52;
    return ((double) fractionalPart) / div + 1;
}

bool printInExponentialForm(char signOfNumber, int exponentOfNumber, double significandOfNumber)
{
    printf("Result: ");
    if (significandOfNumber == 1 && exponentOfNumber == -1023)
        printf("0");
    else
        printf("%c%lf*2^{%d}", signOfNumber, significandOfNumber, exponentOfNumber);
    return true;
}

int main()
{
    double number = 0;
    printf("enter the number:");
    scanf("%lf", &number);
    unsigned char numberInBytes[(SD * sizeof(unsigned char))];
    memset(numberInBytes, 0, (SD * sizeof(unsigned char)));
    convertToBytes(number, numberInBytes);
    char signOfNumber = getSignOfNumber(numberInBytes);
    int exponentOfNumber = getExponentOfNumber(numberInBytes);
    double significandOfNumber = getSignificandOfNumber(numberInBytes);
    printInExponentialForm(signOfNumber, exponentOfNumber, significandOfNumber);
    return 0;
}
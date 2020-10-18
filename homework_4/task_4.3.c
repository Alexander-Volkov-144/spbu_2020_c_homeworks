#include <stdbool.h>
#include <stdio.h>

bool sumBinary(const bool* binaryRepresentation1, const bool* binaryRepresentation2, bool* sumInBinary, int size)
{
    int previousRemainder = 0;
    for (int i = 0; i < size; ++i) {
        sumInBinary[i] = (previousRemainder + binaryRepresentation1[i] + binaryRepresentation2[i]) % 2;
        previousRemainder = (previousRemainder + binaryRepresentation1[i] + binaryRepresentation2[i]) / 2;
    }
    return true;
}

int getDecimal(const bool* binaryRepresentation, int size)
{
    int decimalNumber = 0;
    int powerOfTwo = 1;
    for (int i = 0; i < size; ++i) {
        decimalNumber += (binaryRepresentation[i] ? powerOfTwo : 0);
        powerOfTwo *= 2;
    }
    return decimalNumber;
}

void printBinaryRepresentation(const bool* binaryRepresentation, int size)
{
    for (int i = 0; i < size; ++i) {
        printf("%d", (binaryRepresentation[i] ? 1 : 0));
    }
}

bool createBinaryRepresentation(bool* binaryRepresentation, int size, int number)
{
    for (int i = 0; i < size; ++i) {
        binaryRepresentation[i] = (number & 1) == 1;
        number >>= 1;
    }
    return true;
}

int main()
{
    int number1 = 0;
    int size = sizeof(int) * sizeof(bool) * 8;
    printf("enter the first number\n");
    scanf("%d", &number1);
    bool binaryRepresentation1[size];
    createBinaryRepresentation(binaryRepresentation1, size, number1);
    int number2 = 0;
    printf("enter the second number\n");
    scanf("%d", &number2);
    bool binaryRepresentation2[size];
    createBinaryRepresentation(binaryRepresentation2, size, number2);
    printf("%d = ", number1);
    printBinaryRepresentation(binaryRepresentation1, size);
    printf("\n");
    printf("%d = ", number2);
    printBinaryRepresentation(binaryRepresentation2, size);
    printf("\n");
    bool sumInBinary[size];
    sumBinary(binaryRepresentation1, binaryRepresentation2, sumInBinary, size);
    int sum = getDecimal(sumInBinary, size);
    printf("%d + %d = %d (calculated in binary notation)\n", number1, number2, sum);
    printf("%d + %d = %d (calculated in decimal notation)", number1, number2, number1 + number2);
}

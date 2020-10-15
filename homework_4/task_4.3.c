#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INT_SIZE 32

bool* sumBinary(const bool* binaryRepresentation1, const bool* binaryRepresentation2)
{
    bool* newBinaryRepresentation = (bool*)malloc(INT_SIZE * sizeof(bool));
    int previousRemainder = 0;
    for (int i = 0; i < INT_SIZE; ++i) {
        newBinaryRepresentation[i] = (previousRemainder + binaryRepresentation1[i] + binaryRepresentation2[i]) % 2;
        previousRemainder = (previousRemainder + binaryRepresentation1[i] + binaryRepresentation2[i]) / 2;
    }
    return newBinaryRepresentation;
}

int getDecimal(const bool* binaryRepresentation)
{
    int decimalNumber = 0;
    int twoInPower = 1;
    for (int i = 0; i < INT_SIZE; ++i) {
        decimalNumber += (binaryRepresentation[i] ? twoInPower : 0);
        twoInPower *= 2;
    }
    return decimalNumber;
}

void printBinaryRepresentation(const bool* binaryRepresentation)
{
    for (int i = 0; i < INT_SIZE; ++i) {
        printf("%d", (binaryRepresentation[i] ? 1 : 0));
    }
}

bool* createBinaryRepresentation(int number)
{
    bool* binaryRepresentation = (bool*)malloc(INT_SIZE * sizeof(bool));
    for (int i = 0; i < INT_SIZE; ++i) {
        binaryRepresentation[i] = (number & 1) == 1;
        number >>= 1;
    }
    return binaryRepresentation;
}


int main()
{
    int number1 = 0;
    printf("enter the first number\n");
    scanf("%d", &number1);
    bool* binaryRepresentation1 = createBinaryRepresentation(number1);
    int number2 = 0;
    printf("enter the second number\n");
    scanf("%d", &number2);
    bool* binaryRepresentation2 = createBinaryRepresentation(number2);
    printf("%d = ", number1);
    printBinaryRepresentation(binaryRepresentation1);
    printf("\n");
    printf("%d = ", number2);
    printBinaryRepresentation(binaryRepresentation2);
    printf("\n");
    bool* sumInBinary = sumBinary(binaryRepresentation1, binaryRepresentation2);
    int sum = getDecimal(sumInBinary);
    printf("%d + %d = %d (calculated in binary notation)\n", number1, number2, sum);
    printf("%d + %d = %d (calculated in decimal notation)", number1, number2, number1 + number2);
    free(binaryRepresentation1);
    free(binaryRepresentation2);
    free(sumInBinary);
}

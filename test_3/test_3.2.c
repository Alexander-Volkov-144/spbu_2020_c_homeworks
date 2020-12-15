#include "../library/twoDimensionalArray/twoDimensionalArray.h"
#include <stdio.h>

int main()
{
    int numberOfLines = 0, numberOfColumns = 0;
    printf("Enter the number of lines\n");
    scanf("%d", &numberOfLines);
    printf("Enter the number of columns\n");
    scanf("%d", &numberOfColumns);
    TDArray* array = createTDArray(numberOfLines, numberOfColumns);
    readArrayFromConsole(array);
    printSaddlePoints(array);
    removeTDArray(array);
    return 0;
}

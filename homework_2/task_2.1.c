#include <malloc.h>
#include <stdio.h>

void printRepresentation(int* representation)
{
    int i = 0;//переменная объявлена вне цикла, чтобы было проще печатать последее слагаемое
    for (; representation[i + 1] != 0; i++) {
        printf("%d + ", representation[i]);
    }
    printf("%d\n", representation[i]);
    return;
}

void generateNextTerm(int* representation, int num, int sum)
{
    if (sum <= 0) {
        for (int i = num; representation[i] != 0; ++i) {
            representation[i] = 0;//обнуляются ячейки, идущие далее, чтобы не печатались лишние слагаемые
        }
        printRepresentation(representation);//печать
    } else {
        for (int i = representation[num - 1]; i > 0; --i) {
            if (sum - i >= 0) {
                representation[num] = i;//добавление в массив следующего слагаемого
                generateNextTerm(representation, num + 1, sum - i);
            }
        }
    }
    return;
}

int main()
{
    int n = 0;
    printf("enter a natural number greater than 1\n");
    scanf("%d", &n);
    int* representation = malloc(n * sizeof(int));
    for (int i = 0; i < n + 1; ++i) {
        representation[i] = 0;
    }
    for (int i = n - 1; i > 0; --i) {
        representation[0] = i;
        generateNextTerm(representation, 1, n - i);
    }
    free(representation);
    return 0;
}

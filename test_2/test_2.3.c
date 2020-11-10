#include "../library/list/list.h"
#include <stdio.h>

int isNumber(char character)
{
    return character >= '0' && character <= '9';
}

int main()
{
    FILE* input = fopen("D://AB.txt", "r");
    printf("enter first number\n");
    int a = 0;
    scanf("%d", &a);
    printf("enter second number\n");
    int b = 0;
    scanf("%d", &b);
    List* lessThanA = createList();
    int position1 = 0;
    List* belongsToSegment = createList();
    int position2 = 0;
    List* aboveB = createList();
    int position3 = 0;
    char currentCharacter = getc(input);
    int currentNumber = 0;
    while (currentCharacter != EOF && currentCharacter != '\0') {
        if (isNumber(currentCharacter)) {
            currentNumber *= 10;
            currentNumber += (currentCharacter - '0');
        } else {
            if (currentNumber < a) {
                ListElement* temporaryElement = createListElement(currentNumber);
                insert(temporaryElement, position1, lessThanA);
                position1++;
                currentNumber = 0;
            } else {
                if (currentNumber > b) {
                    ListElement* temporaryElement = createListElement(currentNumber);
                    insert(temporaryElement, position2, aboveB);
                    position2++;
                    currentNumber = 0;
                } else {
                    ListElement* temporaryElement = createListElement(currentNumber);
                    insert(temporaryElement, position3, belongsToSegment);
                    position3++;
                    currentNumber = 0;
                }
            }
        }
        currentCharacter = fgetc(input);
    }
    printf("less than A: ");
    printList(lessThanA);
    printf("belongsToSegment:");
    printList(belongsToSegment);
    printf("greater than B: ");
    printList(aboveB);
    deleteList(lessThanA);
    deleteList(belongsToSegment);
    deleteList(aboveB);
    fclose(input);
}

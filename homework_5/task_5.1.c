#include "../library/bst/bst.h"
#include <stdio.h>

void printInstructions()
{
    printf("enter one of the numbers:\n");
    printf("1 - add number to set\n");
    printf("2 - remove number from set\n");
    printf("3 - check if element belongs to set\n");
    printf("4 - print all elements in a set\n");
    printf("5 - exit\n");
}

int readNumber()
{
    int number = 0;
    printf("enter an integer\n");
    scanf("%d", &number);
    return number;
}

bool isInRange(char enteredCharacter)
{
    return '1' <= enteredCharacter && enteredCharacter <= '5';
}

int readFunctionNumber()
{
    char enteredCharacter = '0';
    enteredCharacter = getchar();
    if (enteredCharacter == '\n')
        enteredCharacter = getchar();
    while (!isInRange(enteredCharacter)) {
        printf("please, enter a number between 1 and 5\n");
        enteredCharacter = getchar();
        if (enteredCharacter == '\n')
            enteredCharacter = getchar();
    }
    return enteredCharacter - '0';
}

bool addNumberToSet(BinarySearchTree* tree, int number)
{
    addValue(tree, number);
    return true;
}

bool removeNumberFromSet(BinarySearchTree* tree, int number)
{
    removeValue(tree, number);
    return true;
}

bool isElementInSet(BinarySearchTree* tree, int number)
{
    if (exists(tree, number))
        printf("number %d is in set\n", number);
    else
        printf("number %d isn't in set\n", number);
    return true;
}

bool printAllElements(BinarySearchTree* tree)
{
    printTree(tree);
    return true;
}

void callFunction(BinarySearchTree* tree, int functionNumber)
{
    switch (functionNumber) {
    case 1:
        addNumberToSet(tree, readNumber());
        break;
    case 2:
        removeNumberFromSet(tree, readNumber());
        break;
    case 3:
        isElementInSet(tree, readNumber());
        break;
    case 4:
        printAllElements(tree);
        break;
    }
}

int main()
{
    BinarySearchTree* tree = createTree();
    while (1) {
        printInstructions();
        int functionNumber = readFunctionNumber();
        if (functionNumber == 5) {
            printf("the program is finished");
            break;
        }
        callFunction(tree, functionNumber);
    }
    removeTree(tree);
    return 0;
}

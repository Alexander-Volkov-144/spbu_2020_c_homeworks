#include "../library/stackd/stackd.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char* readString()
{
    char* newString = (char*)malloc(sizeof(char));
    int i = 0, size = 1;
    char currentCharacter = getchar();
    while (currentCharacter != '\n') {
        if (i == size) {
            newString = (char*)realloc(newString, size * 2);
            size *= 2;
        }
        newString[i] = currentCharacter;
        ++i;
        currentCharacter = getchar();
    }
    return newString;
}

bool isOperation(char x)
{
    return '*' <= x && x <= '/';
}

double parseNumber(const char* string, int i)
{
    double value = 0;
    for (; isdigit(string[i]); ++i) {
        value *= 10;
        value += (string[i] - '0');
    }
    return value;
}

double getFirstElementValue(Stack* stack)
{
    StackElement* temporaryElement = pop(stack);
    double x = getStoreElement(temporaryElement);
    deleteStackElement(temporaryElement);
    return x;
}

double calculatePartialResult(Stack* numbers, char operation)
{
    double b = getFirstElementValue(numbers);
    double a = getFirstElementValue(numbers);
    switch (operation) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    }
    printf("error in function calculatePartialResult\n");
    return 0;
}

double calculateResult(char* expression)
{
    Stack* numbers = createStack();
    for (int i = 0; expression[i] != '\0'; ++i) {
        if (isdigit(expression[i])) {
            push(numbers, createStackElement(parseNumber(expression, i)));
            while (isdigit(expression[i])) {
                ++i;
            }
        } else if (isOperation(expression[i])) {
            push(numbers, createStackElement(calculatePartialResult(numbers, expression[i])));
        }
    }
    double result = getFirstElementValue(numbers);
    removeStack(numbers);
    return result;
}

int main()
{
    printf("enter expression in postfix form\n");
    char* expression = readString();
    printf("= %f", calculateResult(expression));
    return 0;
}
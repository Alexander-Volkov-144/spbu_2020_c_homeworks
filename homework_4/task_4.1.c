#include "../library/stackd/stackd.h"
#include <stdio.h>

#define MAX_LENGTH 2048

double calculateNumber(char* string, int i)
{
    double value = 0;
    for (; string[i] != ' '; ++i) {
        value *= 10;
        value += (string[i] - '0');
    }
    return value;
}

double getFirstElementValue(Stack* stack)
{
    StackElement* temporaryElement = pop(stack);
    double x = temporaryElement->storeElement;
    deleteStackElement(temporaryElement);
    return x;
}

double calculatePartialResult(Stack* numbers, char operation)
{
    double b = getFirstElementValue(numbers);
    double a = getFirstElementValue(numbers);
    switch (operation) {
        case '+' :
            return a + b;
        case '-' :
            return a - b;
        case '*' :
            return a * b;
        case '/' :
            return a / b;
    }
};

double calculateResult(char* expression)
{
    Stack* numbers = createStack();
    for (int i = 0; expression[i] != '\0'; ++i) {
        if ('1' <= expression[i] && expression[i] <= '9') {
            push(numbers, createStackElement(calculateNumber(expression, i)));
        } else {
            if ('*' <= expression[i] && expression[i] <= '/') {
                push(numbers, createStackElement(calculatePartialResult(numbers, expression[i])));
            }
        }
    }
    double result = getFirstElementValue(numbers);
    removeStack(numbers);
    return result;
}

int main()
{
    char expression[MAX_LENGTH];
    fgets(expression, 2048, stdin);
    printf("%f", calculateResult(expression));
    return 0;
}
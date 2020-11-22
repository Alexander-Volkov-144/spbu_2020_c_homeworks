#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool isNumeral(char character)
{
    return character >= '0' && character <= '9';
}

int getNumericalEquivalent(const char* string, int size)
{
    int result = 0;
    for (int i = 0; i < size; ++i) {
        result *= 10;
        result += string[i];
    }
    return result;
}

bool isDate(char* string)
{
    for (int i = 0; i < 2; ++i) {
        if (!isNumeral(string[i])) {
            return false;
        }
    }
    if (string[2] != '.')
        return false;
    for (int i = 3; i < 5; ++i) {
        if (!isNumeral(string[i])) {
            return false;
        }
    }
    if (string[5] != '.')
        return false;
    for (int i = 6; i < 10; ++i) {
        if (!isNumeral(string[i])) {
            return false;
        }
    }
    return true;
}

bool compareDates(char* firstString, char* secondString)
{
    int firstYear = getNumericalEquivalent(&firstString[6], 4);
    int secondYear = getNumericalEquivalent(&secondString[6], 4);
    if (firstYear < secondYear) {
        return true;
    } else {
        if (firstYear > secondYear) {
            return false;
        } else {
            int firstMonth = getNumericalEquivalent(&firstString[3], 2);
            int secondMonth = getNumericalEquivalent(&secondString[3], 2);
            if (firstMonth < secondMonth) {
                return true;
            } else {
                if (firstMonth > secondMonth) {
                    return false;
                } else {
                    return getNumericalEquivalent(firstString, 2) < getNumericalEquivalent(secondString, 2);
                }
            }
        }
    }
}

void updateString(char* string, char newCharacter)
{
    for (int i = 0; i < 9; ++i) {
        string[i] = string[i + 1];
    }
    string[9] = newCharacter;
}

int main()
{
    FILE* input = NULL;
    input = fopen("D://dates.txt", "r");
    char currentCharacter = fgetc(input);
    char currentString[11];
    memset(currentString, 0, 11 * sizeof(char));
    char stringForMinimumDate[11];
    memset(stringForMinimumDate, 0, 11 * sizeof(char));
    bool notFound = true;
    for (int i = 0; i < 10; ++i) {
        if (currentCharacter == EOF) {
            printf("there are no dates in the file");
            return 0;
        }
        currentString[i] = currentCharacter;
        currentCharacter = fgetc(input);
    }
    currentString[10] = '\0';
    while (currentCharacter != '\0' && currentCharacter != EOF) {
        if (isNumeral(currentString[0])) {
            if (isDate(currentString)) {
                if (compareDates(currentString, stringForMinimumDate) || notFound) {
                    strcpy(stringForMinimumDate, currentString);
                    notFound = false;
                }
            }
        }
        currentCharacter = getc(input);
        if (currentCharacter != EOF && currentCharacter != '\0') {
            updateString(currentString, currentCharacter);
        } else {
            break;
        }
    }
    if (notFound) {
        printf("there are no dates in the file");
    } else {
        printf("minimum date: %s", stringForMinimumDate);
    }
    fclose(input);
    return 00;
}

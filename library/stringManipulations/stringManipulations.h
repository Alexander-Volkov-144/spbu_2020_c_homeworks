#ifndef SPBU_2020_C_HOMEWORKS_STRINGMANIPULATIONS_H
#define SPBU_2020_C_HOMEWORKS_STRINGMANIPULATIONS_H

#include <stdbool.h>

bool isLetter(char character);

char* doubleSize(char* oldString, int* oldSize);

char* readString();

void removeCharacter(char* string, char character);

#endif //SPBU_2020_C_HOMEWORKS_STRINGMANIPULATIONS_H

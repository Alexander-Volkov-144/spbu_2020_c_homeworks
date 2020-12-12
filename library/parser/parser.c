#include "parser.h"
#include "../stringManipulations/stringManipulations.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool E(char* string, int size, int* current);
bool T(char* string, int size, int* current);
bool U(char* string, int size, int* current);
bool F(char* string, int size, int* current);
bool J(char* string, int size, int* current);

bool E(char* string, int size, int* current){
    return T(string, size, current) && J(string, size, current);
}

bool T(char* string, int size, int* current){
    return F(string, size, current) && U(string, size, current);
}

bool U(char* string, int size, int* current){
    int position = *current;
    if (*current >= size) {
        return true;
    }
    if (string[*current] == '*') {
        (*current)++;
        if (F(string, size, current) && U(string, size, current))
            return true;
        else
            *current = position;
    }
    return true;
}

bool F(char* string, int size, int* current){
    int position = *current;
    if (*current >= size) {
        return true;
    }
    if (string[*current] == '(') {
        (*current)++;
        if (E(string, size, current)) {
            if (string[*current] == ')')
                (*current)++;
        }
    }
    else if (string[*current] == 'a') {
        (*current)++;
    }
    else
        return false;
    return true;
}

bool J(char* string, int size, int* current){
    int position = *current;
    if (*current >= size) {
        return false;
    }
    if (string[*current] == '+') {
        (*current)++;
        if (T(string, size, current) && J(string, size, current))
            return true;
        else
            *current = position;
    }
    return true;
}

bool isCorrect(char* string, int size){
    removeCharacter(string,' ');
    int current = 0;
    bool result = E(string, strlen(string), &current);
    return result && current == strlen(string);
}
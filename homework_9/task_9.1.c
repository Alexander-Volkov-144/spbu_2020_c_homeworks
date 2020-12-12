#include "../library/parser/parser.h"
#include "../library/stringManipulations/stringManipulations.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(){
    char* string = readString();
    if(isCorrect(string,(int)strlen(string)))
        printf("correct");
    else
        printf("not correct");
    free(string);
    return 0;
}
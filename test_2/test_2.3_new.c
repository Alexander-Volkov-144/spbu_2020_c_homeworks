#include "../library/fileProcessing/fileProcessing.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Condition {
    shoot,
    toSiberia,
    undefined
} Condition;

typedef struct Person {
    char* surname;
    int loyalty;
    Condition condition;
} Person;

bool isNumber(char character)
{
    return character >= '0' && character <= '9';
}

Person* createPerson(char* surname, int loyalty, Condition condition)
{
    Person* newPerson = (Person*)malloc(sizeof(Person));
    newPerson->surname = (char*)malloc(sizeof(char) * (strlen(surname) + 1));
    for (int i = 0; i < strlen(surname) + 1; ++i) {
        newPerson->surname[i] = surname[i];
    }
    newPerson->loyalty = loyalty;
    newPerson->condition = condition;
    return newPerson;
}

Person** doubleSizeOfArray(Person** oldArray, int oldSize)
{
    Person** newArray = (Person**)malloc(sizeof(Person*) * oldSize * 2);
    for (int i = 0; i < oldSize; ++i) {
        newArray[i] = oldArray[i];
    }
    free(oldArray);
    return newArray;
}

Person** readAListOfPeopleFromAFile(FILE* file, int* peopleCount)
{
    Person** partyMembers = (Person**)malloc(sizeof(Person*));
    int arraySize = 1;
    int index = 0;
    char* currentWord = NULL;
    int currentLoyalty = 0;
    char currentCharacter = 0;
    while (!feof(file)) {
        currentWord = readWordFromFile(file);
        currentLoyalty = 0;
        if (currentWord != NULL) {
            for (int i = 0; i < 3; ++i) {
                currentCharacter = fgetc(file);
            }
            while (isNumber(currentCharacter) && !feof(file)) {
                currentLoyalty *= 10;
                currentLoyalty += (currentCharacter - '0');
                currentCharacter = fgetc(file);
            }
        }
        if (currentWord != NULL) {
            if (index == arraySize) {
                partyMembers = doubleSizeOfArray(partyMembers, arraySize);
                arraySize *= 2;
            }
            partyMembers[index] = createPerson(currentWord, currentLoyalty, undefined);
            ++index;
        }
    }
    free(currentWord);
    *peopleCount = index;
    return partyMembers;
}

int comparePersonsByLoyalty(Person** person1, Person** person2)
{
    if ((*person1)->loyalty > (*person2)->loyalty)
        return 1;
    else {
        if ((*person1)->loyalty < (*person2)->loyalty) {
            return -1;
        }
    }
    return 0;
}

int comparePersonsBySurname(Person** person1, Person** person2)
{
    return strcmp((*person1)->surname, (*person2)->surname);
}

void printListsOfPeople(Person** partyMembers, int peopleCount)
{
    printf("will be shot:\n");
    for (int j = 0; j < peopleCount; ++j) {
        if (partyMembers[j]->condition == shoot) {
            printf("%s\n", partyMembers[j]->surname);
        }
    }
    printf("will be sent to Siberia:\n");
    for (int j = 0; j < peopleCount; ++j) {
        if (partyMembers[j]->condition == toSiberia) {
            printf("%s\n", partyMembers[j]->surname);
        }
    }
    printf("safe:\n");
    for (int j = 0; j < peopleCount; ++j) {
        if (partyMembers[j]->condition == undefined) {
            printf("%s\n", partyMembers[j]->surname);
        }
    }
}

int main()
{
    FILE* input = NULL;
    input = fopen("party_members.txt", "r");
    if (input == NULL) {
        printf("file not found\n");
        return 0;
    }
    int n = 0; //number of people who will be shot
    printf("enter the number of party members to be shot\n");
    scanf("%d", &n);
    int m = 0; //number of people who will be sent to Siberia
    printf("enter the number of party members who will be sent to Siberia\n");
    scanf("%d", &m);
    int peopleCount = 0;
    Person** partyMembers = readAListOfPeopleFromAFile(input, &peopleCount);
    qsort(partyMembers, peopleCount, sizeof(Person*), comparePersonsByLoyalty);
    for (int i = 0; i < n && i < peopleCount; ++i) {
        partyMembers[i]->condition = shoot;
    }
    qsort(partyMembers, peopleCount, sizeof(Person*), comparePersonsBySurname);
    int i = 0;
    while (m > 0) {
        if (partyMembers[i]->condition == undefined) {
            partyMembers[i]->condition = toSiberia;
            --m;
        }
        ++i;
    }
    printListsOfPeople(partyMembers, peopleCount);
    for (int j = 0; j < peopleCount; ++j) {
        free(partyMembers[j]->surname);
        free(partyMembers[j]);
    }
    free(partyMembers);
    fclose(input);
    return 0;
}
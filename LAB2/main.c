#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#define STUDENTS_WITH_LOWEST_RATING  5
typedef struct Sstudent {

    char cSurname[13];
    char cName[10];
    char cBirthday[11];
    int nMarks[5];
    struct student* next;

} student;



int compareBySurname(student* one, student* two);

int compareByRating(student* one, student* two);

double rating(student* ptr);




void dataRead(char* fileName, student** list, student** ratingList) {
    FILE* f = fopen_s(fileName, "r");
    do {
        student* ptrFirst = (student*)malloc(sizeof(student));
        student* ptrSecond = (student*)malloc(sizeof(student));
        fscanf_s(f, "%s %s %s", ptrFirst->cSurname, ptrFirst->cName, ptrFirst->cBirthday);
        for (int i = 0; i < STUDENTS_WITH_LOWEST_RATING; ++i)
            fscanf_s(f, "%i", &(ptrFirst->nMarks[i]));

        strcpy_s(ptrSecond->cSurname, ptrFirst->cSurname);
        strcpy_s(ptrSecond->cName, ptrFirst->cName);
        strcpy_s(ptrSecond->cBirthday, ptrFirst->cBirthday);
        for (int i = 0; i < STUDENTS_WITH_LOWEST_RATING; ++i)
            ptrSecond->nMarks[i] = ptrFirst->nMarks[i];

        newNodeBySurname(ptrFirst, list);
        newNodeByRating(ptrSecond, ratingList);
    } while (fgetc(f) != EOF);
    fclose(f);
}
//_____________________________________________________________________________________
//printing list of students as a spreadsheet
void printList(student* ptr) {
    printf("+---+-------------+----------+----------+--------------+\n");
    printf("| # |   Surname   |   Name   |   Date   |Marks:        |\n");
    printf("+---+-------------+----------+----------+--------------+\n");
    int i = 0;
    while (ptr != NULL) {
        printf("|#%2i|%13s|%10s|%10s|", ++i, ptr->cSurname, ptr->cName, ptr->cBirthday);
        for (int j = 0; j < STUDENTS_WITH_LOWEST_RATING; ++j)
            printf("%2i|", ptr->nMarks[j]);
        printf("\n+---+-------------+----------+----------+--------------+\n");
        ptr = ptr->next;
    }
}
//-----------------------------------------------------------------------------------
void newNodeBySurname(student* ptr, student** headList) {
    if ((*headList) == NULL) {
        (*headList) = ptr;

        (*headList)->next = NULL;
        return;
    }
    if (compareBySurname(*headList, ptr) < 0) //cортування по прізвищу протилежного алфавіту
    {
        ptr->next = *headList; //додавання нового елемента на початок списку
        *headList = ptr;
        return;
    }
    student* current = *headList;  //щоб не затерти звязок
    while ((current->next) != NULL) {
        if (compareBySurname(current, ptr) > 0 && compareBySurname(current->next, ptr) <= 0)//сортування
        {
            ptr->next = current->next;
            current->next = ptr;
            return;
        }
        else current = current->next;
    }
    current->next = ptr;//додаєм останній елемент
    ptr->next = NULL;//присвоєння NULL кінець списку
}
//-----------------------------------------------------------------------------------
void newNodeByRating(student* ptr, student** headList) {
    if ((*headList) == NULL) {
        (*headList) = ptr;

        (*headList)->next = NULL;
        return;
    }
    if (compareByRating(*headList, ptr) < 0) //cортування по прізвищу протилежного алфавіту
    {
        ptr->next = *headList; //додавання нового елемента на початок списку
        *headList = ptr;
        return;
    }
    student* current = *headList;  //щоб не затерти звязок
    while ((current->next) != NULL) {
        if (compareByRating(current, ptr) > 0 && compareByRating(current->next, ptr) <= 0)//сортування
        {
            ptr->next = current->next;
            current->next = ptr;
            return;
        }
        else current = current->next;
    }
    current->next = ptr;//додаєм останній елемент
    ptr->next = NULL;//присвоєння NULL кінець списку
}
//-----------------------------------------------------------------------------------
int compareBySurname(student* one, student* two) {
    return strcmp(one->cSurname, two->cSurname); //перевірка яке прізвище скоріше за алфавітом
}
//-----------------------------------------------------------------------------------
int compareByRating(student* one, student* two) {
    double rOne = rating(one);
    double rTwo = rating(two);

    return rOne == rTwo ? 0 : rOne > rTwo ? -1 : 1;
}
//-----------------------------------------------------------------------------------
void deleteNode(student** headList) {
    student* prev = NULL, * current = *headList;
    while (current != NULL) {
        if ((!prev) &&
            (current->nMarks[0] == 2 || current->nMarks[1] == 2 || current->nMarks[2] == 2 || current->nMarks[3] == 2 ||
                current->nMarks[4] == 2)) // видалення якщо 2 в хеді
        {
            *headList = current->next;
            free(current);
            current = *headList;
            continue;
        }
        if (current->nMarks[0] == 2 || current->nMarks[1] == 2 || current->nMarks[2] == 2 || current->nMarks[3] == 2 ||
            current->nMarks[4] == 2) //якщо не в хеді
        {
            prev->next = current->next; //звязка через 1
            free(current);
            current = prev->next;
            continue;
        }

        prev = current;
        current = prev->next;//перехід до кінця списку
    }
}
//-----------------------------------------------------------------------------------
double rating(student* ptr) {
    double sum = 0;
    for (int i = 0; i < STUDENTS_WITH_LOWEST_RATING; i++) sum += ptr->nMarks[i];
    return sum;
}
//-----------------------------------------------------------------------------------
void printLowestRating(student* headList) {
    student* ptr = headList;

    printf("+---+-------------+----------+----------+--------------+\n");
    printf("|List of students with lowest rating                   |\n");
    printf("+---+-------------+----------+----------+--------------+\n");
    printf("| # |   Surname   |   Name   |   Date   |Marks:        |\n");
    printf("+---+-------------+----------+----------+--------------+\n");
    for (int i = 0; i < STUDENTS_WITH_LOWEST_RATING && ptr->next; i++) {
        printf("|#%2i|%13s|%10s|%10s|", i + 1, ptr->cSurname, ptr->cName, ptr->cBirthday);
        for (int j = 0; j < STUDENTS_WITH_LOWEST_RATING; ++j)
            printf("%2i|", ptr->nMarks[j]);
        printf("\n+---+-------------+----------+----------+--------------+\n");
        ptr = ptr->next;
    }

    printf("\n\n");
}
//-----------------------------------------------------------------------------------
int main(void) {

    student* listBySurname = NULL;
    student* listByRating = NULL;

    dataRead("input.txt", &listBySurname, &listByRating);

    printf("List before:\n");
    printList(listBySurname);
    printf("\n");

    deleteNode(&listBySurname);

    printf("List after:\n");
    printList(listBySurname);
    printf("\n");


    printf("5 students with lowest rating:\n");
    printLowestRating(listByRating);
    printf("\n");

}
#pragma once
typedef struct student {

    char surname[13];
    char name[10];
    char cBirthday[11];
    int marks[5];
    struct student* next;

} student;
void dataRead(char* fileName, student** list, student** ratingList);

void printList(student* ptr);

void newNodeBySurname(student* ptr, student** headList);

void newNodeByRating(student* ptr, student** headList);

void deleteNode(student** headList);

void printLowestRating(student* headList);
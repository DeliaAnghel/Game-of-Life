#ifndef TASK2_H
#define TASK2_H

#include<stdio.h>
#include<stdlib.h>

//structura ce defineste elementele listei
struct element
{
    int linie;
    int coloana;
    struct element *next;
};
typedef struct element Node;

//structura ce defineste elementele stivei
struct S
{
    int nrGeneratie;
    Node *Generatie;
    struct S *nextGen; 
};
typedef struct S Stack;

void addAtBeginning(Node **head, int Linie, int Coloana);
void addAtEnd(Node **head , int Linie, int Coloana);
void push(Stack **top , Node *gen, int nrGen);
void printStack(Stack* top, FILE *fisier_iesire);
void deleteList(Node **head);
void deleteStack(Stack **top);

#endif
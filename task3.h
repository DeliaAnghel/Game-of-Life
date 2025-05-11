#ifndef TASK3_H
#define TASK3_H

#include<stdio.h>
#include<stdlib.h>
#include "task1.h"
#include "task2.h"

struct N{
    Node *head;
    struct N *right, *left;
};
typedef struct N Elem;

Node* initTree(char **tabla, int N, int M);
Node* regula_B(char **tabla, char **tablaB, int N, int M);
Node* regula_standard(char **tabla, char **tabla_standard, int N, int M);
Elem* task3 (Node *h, int generatie, int K, char **tabla, int N, int M, FILE *f);
void afisare_arbore(Elem *root, int generatie, int K, char **tabla, int N, int M, FILE *fisier );
void delete_tree(Elem *root);

#endif
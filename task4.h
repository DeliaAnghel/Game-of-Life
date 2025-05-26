#ifndef TASK4_H
#define TASK4_H
#include<stdio.h>
#include<stdlib.h>
#include "task1.h"
#include "task2.h"
#include "task3.h"

struct c{
    int linie;
    int coloana;
};
typedef struct c Coordonate;

struct g{
    int varfuri;
    int **mAdiacenta;
    Coordonate *coord_celuleVii;
};
typedef struct g Graph;


int **alocare_spatiu_matriceInt( int N, int M);
void createGraph(Graph *g, int n, int m, char **tabla);
void eliberare_mInt(int **tabla, int N);
int *drum_Hamilton( int size, int **a, int vizitat[], int path[], int depth, int poz, int *sizePath);
void DFS_scan( Graph *g, int visited[] , int i, Coordonate *c, int *size, int *count);
void DFS( Graph *g, FILE *fisier);
void task4(Elem *root, int generatie, int K, char **tabla, int N, int M, FILE *fisier);




#endif

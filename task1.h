#include<stdio.h>
#include<stdlib.h>

void numarare_vecini_vii(char **tabla, int i, int j, int *celule_vii, int N, int M);
void afisare(char **tabla, int N, int M, FILE *fisier);
void copy(char **tabla, char **tablaOut, int N, int M);
void calculare_generatie(char **tabla, char **tablaOut, int K, int N, int M, FILE *fisier_iesire);

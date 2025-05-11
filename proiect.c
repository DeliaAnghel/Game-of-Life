#include<stdio.h>
#include<stdlib.h>
#include "task1.h"
#include "task2.h"
#include "task3.h"

//T numarul testului
//N numarul randurilor
//M numarul coloanelor
//K numarul generatiilor de calculat
int main(int argc, const char* argv[])
{int T, N, M, K, generatie, i, j;
    char **tabla;
    if (argc < 3)
    {
        printf("Utilizare: %s fisier1.in fisier2.in ....\n", argv[0]);
        return 1;
    }

    FILE* fisier_intrare;
    FILE* fisier_iesire;
    fisier_intrare = fopen(argv[1], "rt");
    fisier_iesire = fopen(argv[2], "wt");
    if (fisier_intrare == NULL)
    {
        printf("Eroare la deschiderea fisierului!\n");
        exit(1);
    }
    if (fisier_iesire == NULL)
    {
        printf("Eroare la deschiderea fisierului!\n");
        exit(1);
    }

    //citire din fisierul de intrare
    fscanf(fisier_intrare, "%d", &T);
    fscanf(fisier_intrare, "%d%d", &N, &M);
    fscanf(fisier_intrare, "%d", &K);

    tabla = alocare_spatiu_matrice(N, M);
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            fscanf(fisier_intrare, " %c", &tabla[i][j]);
    fclose(fisier_intrare);

    char **tablaOut;
    tablaOut = alocare_spatiu_matrice(N, M);

    if (T == 1) calculare_generatie(tabla, tablaOut, K, N, M, fisier_iesire);
    else if (T == 2)
    {
        Stack *stackTop = NULL;
        int celule_vii = 0;
        char viu = 'X', mort = '+';

        for(generatie = 0; generatie < K; generatie++)
        {
            //creez o noua lista pentru fiecare generatie;
            Node *head = NULL;

            for (i = 0; i < N; i++)
            {
                for (j = 0; j < M; j++)
                {
                    if (tabla[i][j] == viu)
                    {
                        numarare_vecini_vii(tabla, i, j, &celule_vii, N, M);
                        if (celule_vii < 2 || celule_vii > 3)
                        {
                            tablaOut[i][j] = mort;
                            addAtEnd (&head, i, j);
                            
                        }else tablaOut[i][j] = viu;


                    }
                    else if (tabla[i][j] == mort)
                    {
                        numarare_vecini_vii(tabla, i, j, &celule_vii, N, M);
                        if (celule_vii == 3)
                        {
                            tablaOut[i][j] = viu;
                            addAtEnd (&head , i, j);
                            
                        }else tablaOut[i][j] = mort;
                    }
                    celule_vii = 0;
                }
            }
            copy(tabla, tablaOut, N, M);

            //introduc lista in stiva
            push (&stackTop , head, generatie + 1);
        } 
        printStack(stackTop, fisier_iesire);
        deleteStack(&stackTop);
    }else if (T == 3)
    {
        Elem *root = NULL;
        Node *lista_gen0 = NULL;
        int gen = 0;
        lista_gen0 = initTree( tabla, N, M);
        root = task3 (lista_gen0, gen, K, tabla, N, M, fisier_iesire);
        afisare_arbore(root, gen, K, tabla, N, M, fisier_iesire );
        delete_tree(root);

    }
    
    eliberare(tablaOut, N);
    eliberare(tabla, N);
    fclose(fisier_iesire); 
}

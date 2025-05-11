#include "task1.h"

//functie de alocare spatiu pentru matrice
char **alocare_spatiu_matrice( int N, int M)
{
    char **tabla;
    tabla = (char**)malloc(N * sizeof(char*));
    if (tabla == NULL)
    {
        printf("Alocare esuata!");
        exit(1);
    }

    for (int i = 0; i < N; i++)
    {
        tabla[i] = (char*)malloc(M * sizeof(char));
        if (tabla[i] == NULL)
        {
            printf("Alocare esuata!");
            exit(1);
        }
    }
    
    return tabla;  
}

//eliberare spatiu matrice
void eliberare(char **tabla, int N)
{
    int i;
    for (i = 0; i < N; i++)
        free(tabla[i]);
    free(tabla);
}

//functie care numara vecinii vii ai unei celule
//t si v sunt coordonatele unei celule
void numarare_vecini_vii(char **tabla, int i, int j, int *celule_vii, int N, int M)
{
    int t, v;
    for (t = -1; t <= 1; t++)
    {
        if (i + t >= 0 && i + t < N)
        for (v = -1; v <= 1; v++)
        {
            if(j + v >= 0 && j + v < M)
                if ( tabla[i+t][j+v] == 'X' && (t != 0 || v != 0) )
                (*celule_vii)++;
        }
    }
}

//functie afisare tabla
void afisare(char **tabla, int N, int M, FILE *fisier)
{
    for (int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        fprintf(fisier, "%c", tabla[i][j]);

        fprintf(fisier, "\n");
    }
    fprintf(fisier, "\n");
}

//functie care copiaza elementele din tablaOut in tabla
void copy(char **tabla, char **tablaOut, int N, int M)
{
    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            tabla[i][j] = tablaOut[i][j];

}

//functie care calculeaza fiecare generatie conform taskului 1
void calculare_generatie(char **tabla, char **tablaOut, int K, int N, int M, FILE *fisier_iesire)
{int generatie, i, j;

    afisare(tabla, N, M, fisier_iesire);

    int celule_vii = 0;
    char viu = 'X', mort = '+';
    for (generatie = 0; generatie < K; generatie++)
    {
        
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < M; j++)
            {
                if (tabla[i][j] == viu)
                {
                    numarare_vecini_vii(tabla, i, j, &celule_vii, N, M);
                    if (celule_vii < 2 || celule_vii > 3)
                        tablaOut[i][j] = mort;
                    else tablaOut[i][j] = viu;

                }
                else if (tabla[i][j] == mort)
                {
                    numarare_vecini_vii(tabla, i, j, &celule_vii, N, M);
                    if (celule_vii == 3)
                        tablaOut[i][j] = viu;
                    else tablaOut[i][j] = mort;
                }
                celule_vii = 0;

            }
        }
        afisare(tablaOut, N, M, fisier_iesire);
        copy(tabla, tablaOut, N, M);
    }
}
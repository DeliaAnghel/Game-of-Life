#include "task4.h"

//aloca spatiu unei matrici de tip int
int **alocare_spatiu_matriceInt( int N, int M)
{
    int **tabla;
    tabla = (int**)calloc(N, sizeof(int*));
    if (tabla == NULL)
    {
        printf("Alocare esuata!");
        exit(1);
    }

    for (int i = 0; i < N; i++)
    {
        tabla[i] = (int*)calloc(M, sizeof(int));
        if (tabla[i] == NULL)
        {
            printf("Alocare esuata!");
            exit(1);
        }
    }
    
    return tabla;  
}

//functie care creeaza graful
//creaeaza matricea de adiacenta
void createGraph(Graph *g, int n, int m, char **tabla)
{int i, j, size = 0, t, v;
    if (tabla == NULL || g == NULL){

        printf("eroare");
        exit(1);
    }
    g->coord_celuleVii = (Coordonate*)malloc(n*m*sizeof(Coordonate));
    if ( g->coord_celuleVii == NULL ){
    printf ("Eroare");
    return;
    }

    for (i = 0; i < n; i++){
        for (j = 0; j < m; j++){
            if (tabla[i][j] == 'X'){
                g->coord_celuleVii[size].linie = i;
                g->coord_celuleVii[size].coloana = j;
                size++;
            }
        }
    }
    g->varfuri = size;
    
    g->mAdiacenta = alocare_spatiu_matriceInt(size, size);
    if ( g->mAdiacenta == NULL)
        {
            free(g->coord_celuleVii);
            printf("Alocare esuata!");
            return;
        }

    for (i = 0; i < size-1; i++)
    for (j = i+1; j < size; j++){
        for (t = -1; t <= 1; t++)
        {
            if (g->coord_celuleVii[i].linie + t >= 0 && g->coord_celuleVii[i].linie + t < n)
            for (v = -1; v <= 1; v++)
            {
                if (g->coord_celuleVii[i].coloana + v >= 0 && g->coord_celuleVii[i].coloana + v < m)
                if (g->coord_celuleVii[j].linie == g->coord_celuleVii[i].linie + t 
                    && g->coord_celuleVii[j].coloana == g->coord_celuleVii[i].coloana + v 
                    && (t != 0 || v != 0))
                {
                    g->mAdiacenta[i][j] = 1;
                    g->mAdiacenta[j][i] = 1;
                }
            }
        }
    }
    
}

//fc de eliberare a matricei de adiacenta
void eliberare_mInt(int **tabla, int N)
{
    int i;
    for (i = 0; i < N; i++)
        free(tabla[i]);
    free(tabla);
}

//primeste vectorul de noduri ale componentei conexe si nr de noduri
//depth e indexul
int *drum_Hamilton( int size, int **a, int vizitat[], int path[], int depth, int poz, int *sizePath){
    vizitat[poz] = 1;
    path[depth] = poz;

    if(depth == size - 1){
        (*sizePath) = depth + 1;
        return path;
    } else {
        for (int j = 0; j < size; j++){

            if (a[poz][j] == 1 && vizitat[j] == 0){
            const int *drum = drum_Hamilton(size, a, vizitat, path, depth+1, j, sizePath);
            
            if (drum != NULL){
            (*sizePath) = depth;
            return path;
            }
            }
        }
    }
    vizitat[poz] = 0;
    return NULL;
}

//gasirea posibilelor drumuri Hamilton
void DFS_scan( Graph *g, int visited[] , int i, Coordonate *c, int *size, int *count){
    int j, grad = 0;
    for (j = 0; j < g->varfuri; j++)
        if (g->mAdiacenta[i][j] == 1) grad++;
    if (grad < 2) (*count)++;

    visited[i]=1;
    //adaug coordonatele intr-un vector de coordonate
    c[*size].linie = g->coord_celuleVii[i].linie;
    c[*size].coloana = g->coord_celuleVii[i].coloana;
    (*size)++;


    for (j = 0; j < g->varfuri; j++){
        if (g->mAdiacenta[i][j] == 1 && visited[j] == 0)
            DFS_scan(g, visited ,j, c, size, count);
    }
        
}

void DFS( Graph *g, FILE *fisier){
    int i, contor_Hamilton = 0;
    int *visited = (int*)malloc(g->varfuri*sizeof(int));
    if (visited == NULL)
    {
        printf("Alocare esuata!");
        exit(1);
    }
    Coordonate *coordBestPath = NULL;
    int sizeBestPath = 0;
    for (i = 0; i < g->varfuri; i++) visited[i] = 0;
    
    for (i = 0; i < g->varfuri; i++){
        if (visited[i] == 0){
            int count = 0;
            int size = 0;
            Coordonate *c = (Coordonate*)malloc(g->varfuri*sizeof(Coordonate)); //retine coordonatele dintr-o componenta conexa
            DFS_scan(g, visited, i, c, &size, &count);

            //count verifica daca o componenta conexa are mai mult de doua elemente cu grad = 1
            //count numara cate elemente din graful conex au grad=1
            if (count <= 2){
                
                //am gasit componenta conexa acum ii fac matricea de adiacenta
                int **a = alocare_spatiu_matriceInt(size, size);
                for (int I = 0; I < size - 1; I++)
                for (int j = I + 1; j < size; j++){
                    if((c[I].linie +1 >= c[j].linie && c[I].linie - 1 <= c[j].linie) &&
                    (c[I].coloana +1 >= c[j].coloana && c[I].coloana - 1 <= c[j].coloana))
                        a[I][j] = a[j][I] = 1;
                }

                //cu backtracking aflu daca e un posibil drum Hamilton sau nu
                int *bestPath = (int*)calloc(size, sizeof(int));
                for(int j = 0; j < size; j++){
                    int *vizitat = (int*)calloc(size, sizeof(int));
                    int *path = (int*)calloc(size, sizeof(int));
                    int sizePath = 0;

                    path = drum_Hamilton(size, a, vizitat, path, 0, j, &sizePath);

                    if (path != NULL){
                    contor_Hamilton++;
                    if (sizePath > sizeBestPath){
                        free(coordBestPath);
                        coordBestPath = (Coordonate*)malloc((sizePath + 1)*sizeof(Coordonate));
                        for (int I = 0; I <= sizePath; I++){
                            bestPath[I] = path[I];
                            coordBestPath[I].linie = c[bestPath[I]].linie;
                            coordBestPath[I].coloana = c[bestPath[I]].coloana;
                        } 
                        sizeBestPath = sizePath;
                    }else if (sizePath == sizeBestPath)
                            
                            for (int I = 0; I <= sizePath; I++){
                            if (c[path[I]].linie < c[bestPath[I]].linie){
                                free(coordBestPath);
                                coordBestPath = (Coordonate*)malloc((sizePath + 1)*sizeof(Coordonate));
                                for (int J = 0; J < size; J++){
                                    bestPath[J] = path[J];
                                    coordBestPath[J].linie = c[bestPath[J]].linie;
                                    coordBestPath[J].coloana = c[bestPath[J]].coloana;
                                } 
                                break;
                            }else if (c[path[I]].linie == c[bestPath[I]].linie &&
                            c[path[I]].coloana < c[bestPath[I]].coloana){
                                free(coordBestPath);
                                coordBestPath = (Coordonate*)malloc((sizePath + 1)*sizeof(Coordonate));
                                for (int J = 0; J < sizePath; J++){
                                    bestPath[J] = path[J];
                                    coordBestPath[J].linie = c[bestPath[J]].linie;
                                    coordBestPath[J].coloana = c[bestPath[J]].coloana;
                                }
                                break;
                            }
                                
                        }
                    } 
                
                free(vizitat);
                free(path);
                }
                free(bestPath);
                eliberare_mInt(a, size);
                
            }free(c);
        }
    }
    
    if(contor_Hamilton != 0){
        fprintf(fisier, "%d\n", sizeBestPath);
        for (i = 0; i <= sizeBestPath; i++)
        fprintf(fisier, " (%d,%d)", coordBestPath[i].linie, coordBestPath[i].coloana);
     fprintf(fisier, "\n");
    }else{
        fprintf(fisier, "-1\n");

    } 
    free(visited);
    free(coordBestPath);
    coordBestPath = NULL;
}

void task4(Elem *root, int generatie, int K, char **tabla, int N, int M, FILE *fisier){
   
    Graph *g = NULL;
    if (generatie <= K) {
        g = (Graph*)malloc(sizeof(Graph));
        if ( g == NULL ){
            printf ("Eroare"); 
            return;
        }
        createGraph(g, N, M, tabla);

         for (int i = 0; i < g->varfuri; i++)
            {
        for(int j = 0; j < g->varfuri; j++)
        fprintf(fisier, "%d", g->mAdiacenta[i][j]);

        fprintf(fisier, "\n");
        }
        fprintf(fisier, "\n");
        

        DFS(g, fisier);
        free(g->coord_celuleVii);
        eliberare_mInt(g->mAdiacenta, g->varfuri);
        free(g);

        //merg pe stanga
        if(root->left != NULL)
        {
            char **tablaB;
            tablaB = alocare_spatiu_matrice(N, M); 
            copy(tablaB, tabla, N, M);
            Node *iter;
            iter = (root->left)->head;
            while (iter != NULL) { 
                tablaB[iter->linie][iter->coloana] = 'X';
                iter = iter->next;        
	        }
            task4(root->left, generatie + 1, K, tablaB, N, M, fisier );
            eliberare(tablaB, N);
        }

        //merg pe dreapta
        if(root->right != NULL)
        {
            char **tabla_standard;
            tabla_standard = alocare_spatiu_matrice(N, M);
            copy(tabla_standard, tabla, N, M);
            Node *iter2;
            iter2 = (root->right)->head;
            while (iter2 != NULL) {
                if(tabla[iter2->linie][iter2->coloana] == 'X') 
                    tabla_standard[iter2->linie][iter2->coloana] = '+';
                else if(tabla[iter2->linie][iter2->coloana] == '+') 
                    tabla_standard[iter2->linie][iter2->coloana] = 'X';
                iter2 = iter2->next;        
	         }
            task4(root->right, generatie + 1, K, tabla_standard, N, M, fisier);
            eliberare(tabla_standard, N);
        }
            
    } else return;
}

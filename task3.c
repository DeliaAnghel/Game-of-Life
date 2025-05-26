#include "task3.h"

// initializarea radacinii
Node* initTree(char **tabla, int N, int M)
{int i, j;
    char viu = 'X';
    Node *head = NULL;

    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            if (tabla[i][j] == viu)
            addAtEnd(&head, i, j);

    return head;
}

// implementare a regulii B
Node* regula_B(char **tabla, char **tablaB, int N, int M)
{
    int celule_vii = 0, i, j;
    Node *head = NULL;
    char mort = '+';
    char viu = 'X';

    copy(tablaB, tabla, N, M);
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            numarare_vecini_vii(tabla, i, j, &celule_vii, N, M);
            if (tabla[i][j] == mort && celule_vii == 2)
            {
                tablaB[i][j] = viu;
                addAtEnd (&head , i, j);
            }
            celule_vii = 0;
        }
    }
    return head;
}

// implementare a regulii standard
Node* regula_standard(char **tabla, char **tabla_standard, int N, int M)
{
    int celule_vii = 0, i, j;
    Node *head = NULL;
    char mort = '+';
    char viu = 'X';

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            if (tabla[i][j] == viu)
            {
                numarare_vecini_vii(tabla, i, j, &celule_vii, N, M);
                if (celule_vii < 2 || celule_vii > 3)
                {
                    tabla_standard[i][j] = mort;
                    addAtEnd (&head, i, j);
                    
                }else tabla_standard[i][j] = viu;


            }
            else if (tabla[i][j] == mort)
            {
                numarare_vecini_vii(tabla, i, j, &celule_vii, N, M);
                if (celule_vii == 3)
                {
                    tabla_standard[i][j] = viu;
                    addAtEnd (&head , i, j);
                    
                }else tabla_standard[i][j] = mort;
            }
            celule_vii = 0;
        }
    }
    return head;
}

//functie care creeaza arborele conform regulilor: B si standard
// in tabla voi retine tabla careia ii voi calcula 
// urmatoarea generatie prin cele doua reguli(tablaB si tabla_standard)
Elem* task3 ( Node *h, int generatie, int K, char **tabla, int N, int M, FILE *f)
{
    if (generatie > K) return NULL;
    else
    {
        Elem *root;
        Node *headB = NULL, *headStandard = NULL;
        root = (Elem*)malloc(sizeof(Elem));
        root->head = h;
        root->left = root->right = NULL;

        char **tablaB;
        tablaB = alocare_spatiu_matrice(N, M);
        headB = regula_B(tabla, tablaB, N, M);
        root->left = task3(headB, generatie + 1, K, tablaB, N, M, f);
        eliberare(tablaB, N);
        deleteList(&headB);

        char **tabla_standard;
        tabla_standard = alocare_spatiu_matrice(N, M);
        headStandard = regula_standard(tabla, tabla_standard, N, M);
        root->right = task3(headStandard, generatie + 1, K, tabla_standard, N, M, f);
        eliberare(tabla_standard, N); 
        deleteList(&headStandard);

        return root;
    }
}

//functie de afisare a arborelui in preordine
void afisare_arbore(Elem *root, int generatie, int K, char **tabla, int N, int M, FILE *fisier ){
   
    if (generatie <= K) {

        afisare(tabla, N, M, fisier);

        //afisare pe stanga
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
            afisare_arbore(root->left, generatie + 1, K, tablaB, N, M, fisier );
            eliberare(tablaB, N);
        }

        //afisare pe dreapta
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
            afisare_arbore(root->right, generatie + 1, K, tabla_standard, N, M, fisier);
            eliberare(tabla_standard, N);
        }
            
    } else return;
}

//functie de stergere a arborelui
void delete_tree(Elem *root)
{
    if (root == NULL) return;
    else {
        delete_tree(root->left);         
        delete_tree(root->right); 

        deleteList( &(root->head) );
        free(root);
    }
}

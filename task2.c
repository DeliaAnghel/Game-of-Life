#include "task2.h"

//inserare la inceputul listei
void addAtBeginning(Node **head, int Linie, int Coloana)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Alocare esuata!");
        exit(1);
    }
    newNode->linie = Linie;
    newNode->coloana = Coloana;
    newNode->next = *head ;
    *head = newNode ;
}

//inserare la finalul listei
void addAtEnd(Node **head , int Linie, int Coloana)
{
    if (*head == NULL) 
    {
        addAtBeginning(head , Linie, Coloana);
    }
    else {
        Node *aux = *head ;
        Node *newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL)
        {
            printf("Alocare esuata!");
            exit(1);
        }
        newNode->linie = Linie; 
        newNode->coloana = Coloana;

        while (aux->next != NULL) aux = aux->next ;

        aux->next = newNode ;
        newNode->next = NULL ; 
    }
}

//adaugare element in stiva
void push(Stack **top , Node *gen, int nrGen)
{
    Stack *newNode = (Stack *) malloc(sizeof(Stack));
    if (newNode == NULL)
    {
        printf("Alocare esuata!");
        exit(1);
    }
    newNode->nrGeneratie = nrGen;
    newNode->Generatie = gen;
    newNode->nextGen = *top;
    *top = newNode ;
}

//afisare stiva
void printStack(Stack* top, FILE *fisier_iesire)
{
    if (top != NULL) {
        Node *iter;
        printStack(top->nextGen, fisier_iesire);
        fprintf(fisier_iesire, "%d", top->nrGeneratie);
        iter = top->Generatie;
        while (iter != NULL )
        {
            fprintf (fisier_iesire, " %d %d", iter->linie, iter->coloana);
            iter = iter->next ;
        }
        fprintf(fisier_iesire, "\n");
    }
}
# Game of Life

This repository contains the implementation of all 4 tasks for the *Game of Life* simulation project. The project was developed using fundamental data structures such as matrices, lists, stacks, trees, and graphs, to explore and simulate the behavior of Conway's Game of Life.

## Project Overview

**Conway's Game of Life** is a zero-player simulation game based on a grid of cells that evolve through discrete time steps according to a set of deterministic rules. This project explores:
- The simulation of cell generations
- Efficient storage of changes between generations
- Tree-based evolution modeling
- Graph-based analysis for Hamiltonian paths

## Repository Structure

- proiect.c
- task1.c
- task1.h
- task2.c
- task2.h
- task3.c
- task3.h
- task4.c
- task4.h
- Makefile
- README.md

## Task Summary

### Task 1 - Implementation of the Game of Life rules
- Apply the standard rules of Game of Life.
- Generate and print `K` generations from an initial matrix.
- Cell states: `'X'` = alive, `'+'` = dead.

### Task 2 - Efficient storage of differences between generations
- Use a stack of lists to track only the coordinates of cells that change.
- Print the full stack state after `K` generations.
- Bonus: reverse operation (implemented in bonus_task2)

### Task 3 - Binary Tree Evolution
- Build a binary tree up to depth `K`.
  - Left child: rule B (cell is born if it has exactly 2 live neighbors).
  - Right child: standard Game of Life rules.
- Traverse the tree in preorder and print the corresponding matrices.

### Task 4 - Hamiltonian Path in Graph
- Each generation is modeled as a graph (live cells = nodes).
- Edges exist between neighboring live cells.
- For each component:
  - Find the longest Hamiltonian path.
  - Break ties using lexicographic order.
- Print the length and coordinates of the optimal path, or -1 if none exists.

## Key function examples

### Task 3 - function "afisare_arbore"
```c
//This function traverses the tree in preorder
//It displays the appropriate matrix based on the lists of coordinates contained by each node in the tree.
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
```
### Task 4 - function "drum_Hamilton"
```c
//This function recursively searches for a Hamiltonian path in a connected component
//Returnes the path if found, else NULL
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
```
## How to compile and run?

Use the following `make` commands to compile and run the project:
- `make build` - Compiles the source files and creates the executable
- `make run` - Runs the program using the default input/output files
- `make clean` - Removes the compiled executable and object files

## Author : Delia-Maria Anghel
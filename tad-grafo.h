#ifndef TAD_GRAFO_H
#define TAD_GRAFO_H

#include <stdio.h>
#include <stdlib.h>

#define n

struct grafo{
	int v;
	int a;
	int **adj;
};

typedef struct grafo* Grafo;

int** criaMatriz(int linhas, int colunas, int val);

Grafo initGrafo(int v);

void insereAresta(Grafo G, int vs, int vc);

void removeAresta(Grafo G, int vs, int vc);

void mostraGrafo(Grafo G);

int foiVisitado(int visitados[], int i);

int verticeDisponivel(Grafo G, int vs, int visitados[]);

#endif

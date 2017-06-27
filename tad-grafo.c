#include "tad-grafo.h"

int** criaMatriz(int linhas, int colunas, int val){
	int i, j;
	int **m = (int**) malloc(linhas * sizeof(int*)) ;
	for (i = 0; i < linhas; i++) {
		m[i] = (int*) malloc(colunas * sizeof(int));
	}

	return m;
}

Grafo initGrafo(int v){
	Grafo G = (Grafo) malloc(sizeof(Grafo));
	G->v = v;
	G->a = 0;
	G->adj = criaMatriz(v,v,0);
	return G;
}

void insereAresta(Grafo G, int vs, int vc){
	if(G->adj[vs][vc] == 0){
		G->adj[vs][vc] = 1;
		G->a++;
	}
}

void removeAresta(Grafo G, int vs, int vc){
	if(G->adj[vs][vc] == 1){
		G->adj[vs][vc] = 0;
		G->a--;
	}
}

void mostraGrafo(Grafo G){
	int vs, vc;
	for(vs = 0; vs < G->v; vs++){
		printf("%2d:", vs);
		for(vc = 0; vc < G->v; vc++){
			if(G->adj[vs][vc] == 1){
				printf(" %2d\n", vc);
			}
		}
		printf("\n");
	}
}

int foiVisitado(int visitados[], int i){
	for(int a = 0; a < i; a++){
		if(visitados[a] == i){
			return 1;
		}
	}
	return 0;
}

int verticeDisponivel(Grafo G, int vs, int *visitados){
	for(int i = 0; i < G->v; i++){
		if(G->adj[vs][i] == 1){
			if(foiVisitado(visitados, i) == 0){
				return i;
			}
		}
	}
	return -1;
}

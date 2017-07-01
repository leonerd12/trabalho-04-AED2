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

// A quantidade de arestas é determinada pelo grau de conectividade passada
// por parâmetro.
// A variável autoLoop assume:
// (0 = não pode possuir auto-loop / 1 = pode possuir auto-loop)
// Ex.: Existem 5 vértices, e o grau de Conectividade é 1.0 (100%), logo,
// cada vértice possui 4 arestas (uma para cada vértice distinto).
// Ex.2: Existem 5 vértices, e o grau de conectivdade é 0.5 (50%), logo,
// cada vértice possui 2 arestas.
// Nos exemplos, assumiu que autoLoop é 0.
void geraGrafoPorConectividade(Grafo G, float conectividade, int autoLoop) {
	int qtdArestas, qtdVertices;
	int verticeInicio, verticeSaida, verticeDestino;
	int vertices[N_VERTICES];

	qtdVertices = G->v;

	// Cria uma cópia dos vértices do Grafo e os embaralha.
	geraVetor(vertices, qtdVertices);
	embaralhaVetor(vertices, qtdVertices);

	// Calcula quantidade de arestas
	qtdArestas = (G->v) * conectividade;
	if (autoLoop == 0) {
		qtdArestas = (G->v - 1) * conectividade;
	}

	// (*Precisamos discutir sobre isso... se o grau de conectivdade for muito
	// baixo, a quantidade de arestas é insuficiente para ligar todos os
	// vértices. Isso aqui faz com que ele tenha a quantidade mínima.*)
	if (qtdArestas < qtdVertices) {
		qtdArestas = qtdVertices;
	}

	// Salva o vértice inicial e começa distribuir as primeiras arestas a fim de
	// gerar um grafo conexo.
	verticeInicio = vertices[0];
	verticeSaida = verticeInicio;
	for (int i = 1; i < qtdVertices; i++) {
		verticeDestino = vertices[i];
		G->adj[verticeSaida][verticeDestino] = 1;
		verticeSaida = verticeDestino;
		qtdArestas--;
	}
	verticeDestino = verticeInicio;
	G->adj[verticeSaida][verticeDestino] = 1;
	qtdArestas--;

	// Caso seja possível gerar mais arestas, elas serão geradas aleatoriamente.
	while (qtdArestas != 0) {
		verticeSaida = selecionaChave(vertices, qtdVertices);
		verticeDestino = selecionaChave(vertices, qtdVertices);
		G->adj[verticeSaida][verticeDestino] = 1;
		qtdArestas--;
	}
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

#include <stdio.h>
#include <stdlib.h>
#include "tad-grafo.h"
#include "tad-vetor.h"
#include "tad-fila.h"

int** geraMatrizAdjacencia(int dimensao) {
	int **matriz = (int**) malloc(dimensao * sizeof(int*)) ;
	for (int i = 0; i < dimensao; i++) {
		matriz[i] = (int*) malloc(dimensao * sizeof(int));
	}
	return matriz;
}

Grafo inicializaGrafo(int vertices) {
	Grafo G = (Grafo) malloc(sizeof(Grafo));
	G->vertices = vertices;
	G->arestas = 0;
	G->adjacencia = geraMatrizAdjacencia(vertices);
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
	int qtdVertices;
	int arestasPorVertice;
	int verticeInicio, verticeSaida, verticeDestino;
	int vertices[N_VERTICES];

	qtdVertices = G->vertices;

	// Cria uma cópia dos vértices do Grafo e os embaralha.
	geraVetor(vertices, qtdVertices);
	embaralhaVetor(vertices, qtdVertices);

	// Calcula quantidade de arestas por vértice
	arestasPorVertice = (G->vertices) * conectividade;
	if (autoLoop == 0) {
		arestasPorVertice = (G->vertices - 1) * conectividade;
	}

	// Salva o vértice inicial e começa distribuir as primeiras arestas a fim de
	// gerar um grafo conexo.
	verticeInicio = vertices[0];
	verticeSaida = verticeInicio;
	for (int i = 1; i < qtdVertices; i++) {
		verticeDestino = vertices[i];
		insereAresta(G, verticeSaida, verticeDestino);
		verticeSaida = verticeDestino;
	}
	verticeDestino = verticeInicio;
	insereAresta(G, verticeSaida, verticeDestino);
	arestasPorVertice--;

	// Se não precisar mais disbribuir vértices, a função já é finalizada.
	if (arestasPorVertice == 0) return;

	// Distribui o restante das arestas de cada vértice aleatoriamente.
	for (int i = 0; i < qtdVertices; i++) {
		int verticesDistribuicao[qtdVertices];
		int contDistribuicao = 0;

		// Se autoLoop for permitido, o vértice pode ser distribuído
		if (autoLoop == 1){
			verticesDistribuicao[contDistribuicao] = i;
			contDistribuicao++;
		}

		// Coleta todos os vértices que ainda não foram ligados p/ distribuição
		for (int j = 0; j < qtdVertices; j++) {
			if(G->adjacencia[i][j] == 0 && i != j) {
				verticesDistribuicao[contDistribuicao] = j;
				contDistribuicao++;
			}
		}

		// Embaralha os vértices para disbribuir aleatoriamente.
		embaralhaVetor(verticesDistribuicao, contDistribuicao);

		// Cria as adjacências a partir dos vértices de distribuição.
		verticeSaida = i;
		for (int j = 0; j < arestasPorVertice; j++) {
			insereAresta(G, verticeSaida, verticesDistribuicao[j]);
		}
	}
}

void insereAresta(Grafo G, int verticeSaida, int verticeDestino){
	if(G->adjacencia[verticeSaida][verticeDestino] == 0){
		G->adjacencia[verticeSaida][verticeDestino] = 1;
		G->arestas++;
	}
}

void removeAresta(Grafo G, int verticeSaida, int verticeDestino){
	if(G->adjacencia[verticeSaida][verticeDestino] == 1){
		G->adjacencia[verticeSaida][verticeDestino] = 0;
		G->arestas--;
	}
}

void mostraGrafo(Grafo G){
	int verticeSaida, verticeDestino;
	for(verticeSaida = 0; verticeSaida < G->vertices; verticeSaida++){
		printf("%2d:", verticeSaida);
		for(verticeDestino = 0; verticeDestino < G->vertices; verticeDestino++){
			if(G->adjacencia[verticeSaida][verticeDestino] == 1){
				printf(" %2d", verticeDestino);
			}
		}
		printf("\n");
	}
}

int foiVisitado(int visitados[], int i){
	for (int a = 0; a < i; a++) {
		if (visitados[a] == i) {
			return 1;
		}
	}
	return 0;
}

int verticeDisponivel(Grafo G, int verticeSaida, int *visitados){
	for(int i = 0; i < G->vertices; i++){
		if(G->adjacencia[verticeSaida][i] == 1){
			if(foiVisitado(visitados, i) == 0){
				return i;
			}
		}
	}
	return -1;
}

//Busca em Largura (Breadth-First Search)
void BFS(Grafo G, int verticeSaida, int verticeDestino){
	Fila aVisitar;
	tipoNo *v;
	int visitados[G->vertices];
	initFila(&aVisitar);

	for(int a = 0; a < G->vertices; a++){
		visitados[a] = 0;
	}

	insereFila(&aVisitar, verticeSaida);
	printf("%d ", verticeSaida);
	while(!filaVazia(aVisitar)){
		v = aVisitar.inicio;
		int vizinho;
		// mostraFila(aVisitar);
		vizinho = v->val;
		visitados[v->val] = 1;
		if(vizinho == verticeDestino){
			printf("\n");
			return;
		}

		for(int a = 0; a < G->vertices; a++){
			if(visitados[a] == 0){
				if(G->adjacencia[vizinho][a] == 1){
					insereFila(&aVisitar, a);
					printf("%d ", a);
					visitados[a] = 1;
				}
			}
		}

		removeFila(&aVisitar);

		// imprimeVetor(visitados, G->v);
	}
	printf("\n");
}

#include <stdio.h>
#include <stdlib.h>
#include "tad-grafo.h"
#include "tad-vetor.h"
#include "tad-fila.h"
#include "tad-pilha.h"

int** geraMatrizAdjacencia(int dimensao) {
	int **matriz = (int**) malloc(dimensao * sizeof(int*)) ;
	for (int i = 0; i < dimensao; i++) {
		matriz[i] = (int*) malloc(dimensao * sizeof(int));
	}

	int i, j;

	for (i = 0; i < dimensao; i ++) {
		for (j = 0; j < dimensao; j++) {
			matriz[i][j] = 0;
		}
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
	int vertices[G->vertices];

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
	//printf("%d ", verticeSaida);
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
	//printf("\n");
}


void DFS(Grafo G, int verticeSaida, int verticeDestino) {
	int visitados[G->vertices];
	for (int i = 0; i < G->vertices; i++) {
		visitados[i] = 0;
	}
	DFSprimeiro(G,verticeSaida,verticeDestino,visitados);
}

int DFSprimeiro(Grafo G, int verticeSaida, int verticeDestino, int *visitados) {
	Pilha visitar;
	//tipoNop* aux;
	int verticeAtual;
	criarPilha(&visitar);
	inserirPilha(&visitar, verticeSaida);
	while(visitar.topo) {
		if (verticeAtual == verticeDestino) {
			return 1;
		}
		verticeAtual = visitar.topo->elemento;
		//printf("Andei pelo vertice: %d\n", verticeAtual);
		removerPilha(&visitar);
		visitados[verticeAtual] = 1;
		for (int i = 0; i < G->vertices; i ++) {
			if(G->adjacencia[verticeAtual][i] == 1 && verticeAtual != i && visitados[i] != 1) {
				inserirPilha(&visitar, i);
			}
		}
	}

	//printf("Não encontrei!\n");
	return 0;
}

void DFSRecursivo(Grafo G, int vertice){
	int visitados[G->vertices];
	for(int a = 0; a < G->vertices; a++){
		visitados[a] = 0;
	}
	chamaDFSrecursivo(G, visitados, G->vertices, vertice);
}

void chamaDFSrecursivo(Grafo G, int visitados[], int numVertices, int vertice){
	// printf("%d\n", vertice);
	visitados[vertice] = 1;
	for(int verticeChegada = 0; verticeChegada < numVertices; verticeChegada++){
		if(!visitados[verticeChegada] && (G->adjacencia[vertice][verticeChegada] == 1)){
			chamaDFSrecursivo(G, visitados, numVertices, verticeChegada);
		}
	}
}

void percorreTudo(Grafo G, int verticeSaida) {
	int visitados[G->vertices];
	for (int i = 0; i < G->vertices; i++) {
		visitados[i] = 0;
	}
	percorreTudoInterno(G,verticeSaida,visitados);
}

void percorreTudoInterno(Grafo G, int verticeSaida, int *visitados) {
	Pilha visitar;
	//tipoNop* aux;
	int verticeAtual;
	criarPilha(&visitar);
	inserirPilha(&visitar, verticeSaida);
	while(visitar.topo) {
		verticeAtual = visitar.topo->elemento;
		if(visitados[verticeAtual] != 1) printf("Andei pelo vértice: %d\n", verticeAtual);
		removerPilha(&visitar);
		visitados[verticeAtual] = 1;
		for (int i = 0; i < G->vertices; i ++) {
			if(G->adjacencia[verticeAtual][i] == 1 && verticeAtual != i && visitados[i] != 1) {
				inserirPilha(&visitar, i);
			}
		}
	}

}

void todosOsCaminhos(Grafo G, int verticeSaida, int verticeChegada){
	int visitados[G->vertices];
	int caminho[G->vertices];
	int caminhoInicio = 0;

	for (int i = 0; i < G->vertices; i++) {
		visitados[i] = 0;
	}

	mostrarTodosOsCaminhos(G, G->vertices, verticeSaida, verticeChegada, visitados, caminho, caminhoInicio);
}

void mostrarTodosOsCaminhos(Grafo G, int numVertices, int verticeSaida, int verticeChegada, int visitados[], int caminho[], int caminhoInicio) {
	//Marcar o vertice atual como visitado
	visitados[verticeSaida] = 1;

	caminho[caminhoInicio] = verticeSaida;
	caminhoInicio++;

	//Se o verticeChegada = verticeSaida, então imprima o vetor caminho atual
	if (verticeSaida == verticeChegada) {
		for(int a = 0; a < caminhoInicio; a++){
			printf("%d ", caminho[a]);
		}
		printf("\n");
	}else{ //Se o verticeChegada for diferente do verticeSaida
		//mostrarTodosOscaminho para o vertice atual
		for(int a = 0; a < numVertices; a++){
			if((!visitados[a]) && (G->adjacencia[verticeSaida][a] == 1)){
				mostrarTodosOsCaminhos(G, numVertices, a, verticeChegada, visitados, caminho, caminhoInicio);
			}
		}
	}

	//remove o vertice atual dos caminho e marque como não-visitado
	caminhoInicio--;
	visitados[verticeSaida] = 0;
}

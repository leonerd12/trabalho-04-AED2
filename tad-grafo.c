#include "tad-grafo.h"
#include "tad-fila.h"
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
	int qtdVertices;
	int arestasPorVertice;
	int verticeInicio, verticeSaida, verticeDestino;
	int vertices[N_VERTICES];

	qtdVertices = G->v;

	// Cria uma cópia dos vértices do Grafo e os embaralha.
	geraVetor(vertices, qtdVertices);
	embaralhaVetor(vertices, qtdVertices);

	// Calcula quantidade de arestas por vértice
	arestasPorVertice = (G->v) * conectividade;
	if (autoLoop == 0) {
		arestasPorVertice = (G->v - 1) * conectividade;
	}

	// Salva o vértice inicial e começa distribuir as primeiras arestas a fim de
	// gerar um grafo conexo.
	verticeInicio = vertices[0];
	verticeSaida = verticeInicio;
	for (int i = 1; i < qtdVertices; i++) {
		verticeDestino = vertices[i];
		G->adj[verticeSaida][verticeDestino] = 1;
		verticeSaida = verticeDestino;
	}
	verticeDestino = verticeInicio;
	G->adj[verticeSaida][verticeDestino] = 1;
	arestasPorVertice--;

	//i = vertice de saida
	//j = vertice de chegada
	//k = contador de arestas distribuidas
	//aux = tamanho do vetor distribuicao
	//auxVertices = vetor de distribuicao
	for(int i = 0; i < qtdVertices; i++){ //linha da matriz
		int aux = 0;
		int auxVertices[qtdVertices];
		if(autoLoop == 1){
			auxVertices[aux] = i;
			aux++;
		}
		for(int j = 0; j < qtdVertices; j++){ //coluna da matriz
			if(G->adj[i][j] == 0 && i != j){
				auxVertices[aux] = j;
				aux++;
			}
		}
		embaralhaVetor(auxVertices, aux);
		for(int k = 0; k < arestasPorVertice; k++){
			verticeDestino = auxVertices[k];
			G->adj[i][verticeDestino] = 1;
		}

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
				printf(" %2d", vc);
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

//Busca em Largura (Breadth-First Search)
void BFS(Grafo G, int vs, int vc){
	Fila aVisitar;
	tipoNo *v;
	int visitados[G->v];
	initFila(&aVisitar);

	for(int a = 0; a < G->v; a++){
		visitados[a] = 0;
	}

	insereFila(&aVisitar, vs);
	printf("%d ", vs);
	while(!filaVazia(aVisitar)){
		v = aVisitar.inicio;
		int vizinho;
		// mostraFila(aVisitar);
		vizinho = v->val;
		visitados[v->val] = 1;


		for(int a = 0; a < G->v; a++){
			if(visitados[a] == 0){
				if(G->adj[vizinho][a] == 1){
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

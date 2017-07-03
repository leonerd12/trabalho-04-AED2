#ifndef TAD_GRAFO_H
#define TAD_GRAFO_H

struct grafo{
	int vertices;
	int arestas;
	int **adjacencia;
};

typedef struct grafo* Grafo;

int** geraMatrizAdjacencia(int dimensao);

Grafo inicializaGrafo(int vertices);

void geraGrafoPorConectividade(Grafo G, float conectividade, int autoLoop);

void insereAresta(Grafo G, int verticeSaida, int verticeDestino);

void removeAresta(Grafo G, int verticeSaida, int verticeDestino);

void mostraGrafo(Grafo G);

int foiVisitado(int visitados[], int i);

int verticeDisponivel(Grafo G, int verticeSaida, int visitados[]);

void BFS(Grafo G, int verticeSaida, int verticeDestino);

void DFS(Grafo G, int verticeSaida, int verticeDestino);

int DFSprimeiro(Grafo G, int verticeSaida, int verticeDestino, int *visitados);

void DFSRecursivo(Grafo G, int vertice);

void chamaDFSrecursivo(Grafo G, int visitados[], int numVertices, int vertice);

void percorreTudo(Grafo G, int verticeSaida);

void percorreTudoInterno(Grafo G, int verticeSaida, int *visitados);

void todosOsCaminhos(Grafo G, int verticeSaida, int verticeChegada);

void mostrarTodosOsCaminhos(Grafo G, int numVertices, int verticeSaida, int verticeChegada, int visitados[], int caminho[], int caminhoInicio) ;

#endif

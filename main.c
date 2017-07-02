#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tad-grafo.h"
#include "tad-fila.h"

#define N_VERTICES1 10

int main(){
    Grafo G = inicializaGrafo(N_VERTICES1);
    geraGrafoPorConectividade(G, 0.25, 0);
    mostraGrafo(G);
    //BFS(G, 1 , 5);

    //DFS(G, 1, 9);

    percorreTudo(G, 1);

}

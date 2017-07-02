#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tad-grafo.h"
#include "tad-fila.h"

int main(){
    Grafo G = initGrafo(6);
    geraGrafoPorConectividade(G, 0.1, 0);
    mostraGrafo(G);
    BFS(G, 1 , 5);
}

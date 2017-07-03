#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tad-grafo.h"

#define N_VERTICES1 10

int main(){
    clock_t start;
    double tempoBFS = 0, tempoDFS = 0;
    Grafo G = inicializaGrafo(N_VERTICES1);
    geraGrafoPorConectividade(G, 0.5, 0);
    mostraGrafo(G);
    //BFS(G, 1 , 5);

    //DFS(G, 1, 9);

    // percorreTudo(G, 1);

    printf("--------------- QUESTÃO 1 e 2 ---------------\n");
    // Grafo G1 = inicializaGrafo(N_VERTICES1);
    // for (float i = 0.1; i <= 1; i = i+0.05) {
    //     printf("Porcentagem de conectividade do grafo: %0.2f\n", i);
    //     start = clock();
    //     BFS(G1, 0, N_VERTICES1);
    //     tempoBFS = (clock() - start) / (double) CLOCKS_PER_SEC;
    //     printf("Tempo BFS (Busca em Largura):      %0.15lf\n", tempoBFS);
    //     start = clock();
    //     DFS(G1, 0, N_VERTICES1);
    //     tempoDFS = (clock() - start) / (double) CLOCKS_PER_SEC;
    //     printf("Tempo DFS (Busca em Profundidade): %0.15lf\n", tempoDFS);
    // }
}

#ifndef TADPILHA_H
#include <stdio.h>
#include <stdlib.h>

typedef struct tipoNop {
    int elemento;
    struct tipoNop *prox;
} tipoNop;

typedef struct Pilha{
    tipoNop *topo;
} Pilha;

void criarPilha(Pilha *pilha);

int pilhaVazia(Pilha pilha);

void inserirPilha(Pilha *pilha, int dado);

void removerPilha(Pilha *pilha);

void mostraPilha(Pilha pilha);

#endif

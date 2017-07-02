#include <stdio.h>
#include <stdlib.h>

typedef struct tipoNop {
    int elemento;
    struct tipoNop *prox;
} tipoNo;

typedef struct Pilha{
    tipoNo *topo;
} tipoPilha;

void criarPilha(tipoPilha *pilha);

int pilhaVazia(Pilha pilha);

void inserirPilha(tipoPilha *pilha, tipoDados dado);

void removerPilha(Pilha *pilha);

void mostraPilha(Pilha pilha);

#include "tad-pilha.h"

void criarPilha(Pilha *pilha) {
    pilha->topo = NULL;
}

int pilhaVazia(Pilha pilha){
    if(pilha.topo == NULL){
        return 1;
    }
    return 0;
}

void inserirPilha(Pilha *pilha, int dado) {
  tipoNop *aux;

  aux = (tipoNop*) malloc (sizeof(tipoNop));
  aux->prox = pilha->topo;
  aux->elemento = dado;
  pilha->topo = aux;

}

void removerPilha(Pilha *pilha) {
    tipoNop *atual;

    atual = pilha->topo;
    if(atual != NULL) {
        pilha->topo = atual->prox;
        free(atual);
    }
}

void mostraPilha(Pilha pilha){
    tipoNop *aux = pilha.topo;
    while (aux) {
        printf("%d - ", aux->elemento);
        aux = aux->prox;
    }
}

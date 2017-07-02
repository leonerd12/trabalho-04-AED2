#include <stdio.h>
#include <stdlib.h>
#include "tad-fila.h"

void initFila(Fila *f){
    f->inicio = NULL;
    f->fim = NULL;
}

void mostraFila(Fila f){
    tipoNo *aux = f.inicio;
    while (aux) {
        printf("%d - ", aux->val);
        aux = aux->prox;
    }
}

int filaVazia(Fila f){
    if(f.inicio == NULL){
        return 1;
    }
    return 0;
}

void insereFila(Fila *f, int val){
    tipoNo *aux = (tipoNo*) malloc(sizeof(tipoNo));
    aux->val = val;
    if(f->inicio != NULL){
        f->fim->prox = aux;
        f->fim = aux;
    }else{
        f->inicio = aux;
        f->fim = aux;
    }
}

void removeFila(Fila *f){
    tipoNo *aux = f->inicio;
    if(f->inicio == f->fim){
        f->inicio = NULL;
    }else{
        f->inicio = f->inicio->prox;
    }
    free(aux);
}

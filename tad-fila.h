#ifndef TAD_FILA_H
#define TAD_FILA_H

typedef struct tipoNo{
    int val;
    struct tipoNo *prox;
}tipoNo;

typedef struct Fila{
    tipoNo *inicio;
    tipoNo *fim;
}Fila;

void initFila(Fila *f);

void mostraFila(Fila f);

int filaVazia(Fila f);

void insereFila(Fila *f, int val);

void removeFila(Fila *f);

#endif

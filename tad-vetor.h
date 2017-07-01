#ifndef TADVETOR_H
#define TADVETOR_H

void embaralhaVetor(int vetor[], int tamanho);

void embaralhaVetorFloat(float vetor[], int tamanho);

void imprimeVetor(int vetor[], int tamanho);

void imprimeVetorFloat(float vetor[], int tamanho);

void selecionaChaves(int chaves[], int n, int vetor[], int tamanho);

void selecionaChave(int chaves[], int n, int vetor[], int tamanho);

void quickSortInterno(int vetor[], int inicio, int fim);

void quickSort(int vetor[], int tamanho);

int buscaBinaria(int vetor[], int tamanho, int chave);

#endif

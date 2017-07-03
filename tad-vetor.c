#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tad-vetor.h"

void embaralhaVetor(int vetor[], int tamanho) {
	// srand(time(NULL));
	int temp, novaPosicao;
	// Embaralha os valores do vetor
	for (int i = 0; i < tamanho; i++) {
		novaPosicao = rand() % tamanho;
		temp = vetor[i];
		vetor[i] = vetor[novaPosicao];
		vetor[novaPosicao] = temp;
	}
}

void embaralhaVetorFloat(float vetor[], int tamanho) {
	int temp, novaPosicao;
	// Embaralha os valores do vetor
	for (int i = 0; i < tamanho; i++) {
		novaPosicao = rand() % tamanho;
		temp = vetor[i];
		vetor[i] = vetor[novaPosicao];
		vetor[novaPosicao] = temp;
	}
}

void geraVetor(int vetor[], int tamanho) {
	// Gera vetor com valores de 1 à 'tamanho'
	for (int i = 0; i < tamanho; i++) {
		vetor[i] = i;
	}
}

void geraVetorFloat(float vetor[], int tamanho) {
	// Gera vetor com valores de 1 à 'tamanho'
	for (int i = 0; i < tamanho; i++) {
		vetor[i] = i+1;
	}
}

void imprimeVetor(int vetor[], int tamanho) {
	for (int i = 0; i < tamanho; i++) {
		printf("%d ", vetor[i]);
	}
	printf("\n");
}

void imprimeVetorFloat(float vetor[], int tamanho) {
	for (int i = 0; i < tamanho; i++) {
		printf("%.2f ", vetor[i]);
	}
	printf("\n");
}

void selecionaChaves(int chaves[], int n, int vetor[], int tamanho) {
    int i, posicao;
    for (i = 0; i < n; i++) {
        posicao = rand() % tamanho; // Sorteia posição no intervalo 0 - 'tamanho'
        chaves[i] = vetor[posicao];
    }
}

int selecionaChave(int vetor[], int tamanho) {
    int posicao = rand() % tamanho;
	return vetor[posicao];
}

void quickSortInterno(int vetor[], int inicio, int fim) {
    int pivot;
    int temp;
    int i,j;

    if (fim - inicio > 0) {
        i = inicio;
        j = fim;
        pivot = vetor[(i + j) / 2];

        do {
            while (vetor[i] < pivot) i++;
            while (vetor[j] > pivot) j--;
            if (i <= j) {
                temp = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = temp;
                i++;
                j--;
            }
        } while (i <= j);

        if (inicio < j) quickSortInterno(vetor, inicio, j);
        if (i < fim) quickSortInterno(vetor, i, fim);
    }
}

void quickSort(int vetor[], int tamanho) {
    quickSortInterno(vetor, 0, tamanho-1);
}

int buscaBinaria(int vetor[], int tamanho, int chave) {
    int meio, inicio = 0, fim = tamanho -1;
	int cont = 0;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
		cont++;
        if (chave > vetor[meio]) {
            inicio = meio + 1;
        }
        else if (chave < vetor[meio]) {
            fim = meio - 1;
        }
        else {
			printf(">> ITERAÇÕES BUSCA BINÁRIA: %d\n", cont);
            return meio;
        }
    }
    return -1;
}

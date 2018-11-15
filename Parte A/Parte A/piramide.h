#ifndef PIRAMIDE_H
#define PIRAMIDE_H

#include <stdio.h>
#include <stdlib.h>
#define INFINITO 999999999

typedef struct Piramide{
    int **piramide;
    int qtdLinhas;
    int qtdColunas;
} Piramide;

/*funções para apoio*/
int** alocarMatriz(int Linhas, int Colunas, int valorPadrao);
int** copiaMatriz(int **a, int qtdLinhas, int qtdColunas);
int stringToInt(char *num);
int maximo(int v1, int v2, int *contaComparacoes);
int recursivo(int i, int j, int **max, Piramide *p, int *contaComparacoes, int *contaChamadas);
int memoization(int i, int j, int **max, Piramide *p, int *contaComparacoes, int *contaChamadas);

/*interface para uso*/
int carregaArquivo(char *nomeArq, Piramide *retorno);
void mostrarPiramide(Piramide *p);
void calcularRecursivo(Piramide *p);
void calcularMemoization(Piramide *p);
void calcularTrasFrente(Piramide *p);
void imprimeResultado(int **max, Piramide *p);

#endif /* PIRAMIDE_H */


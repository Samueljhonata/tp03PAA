#ifndef CIDADE_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define NORTE 1
#define LESTE 2
#define NORTE_LESTE 3

typedef struct Posicao{
    int linha;
    int coluna;
} Posicao;

typedef struct Mapa{
    int **mapa;
    Posicao inicio;
    Posicao fim;
    int qtdLinhas;
    int qtdColunas;
} Mapa;

int** alocarMatriz(int Linhas, int Colunas);
int stringToInt(char *num);
void insereObra(int linha, int coluna, Mapa* mapa, char lado);
int carregaArquivo(char *nomeArq, Mapa *retorno);
void mostraMapa(Mapa *mapa);
int temObra(int linha, int coluna, int direcao, Mapa * mapa);
void calcular(Mapa *m);
void mostraCaminho(int **count, Mapa *m);

#endif /* CIDADE_H */


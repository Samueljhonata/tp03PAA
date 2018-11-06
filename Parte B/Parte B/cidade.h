#ifndef CIDADE_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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


#endif /* CIDADE_H */


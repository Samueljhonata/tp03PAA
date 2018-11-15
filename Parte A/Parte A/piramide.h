#ifndef PIRAMIDE_H
#define PIRAMIDE_H

#include <stdio.h>
#include <stdlib.h>
#define INFINITO -999999999

typedef struct Posicao{
    int linha;
    int coluna;
} Posicao;

typedef struct Piramide{
    int **piramide;
    int qtdLinhas;
    int qtdColunas;
} Piramide;



#endif /* PIRAMIDE_H */


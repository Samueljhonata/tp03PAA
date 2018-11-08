#include <stdio.h>
#include <stdlib.h>
#include "cidade.h"

int main(int argc, char** argv) {
    Mapa m;
    
    carregaArquivo("cidade1.txt",&m);
    printf("\n---------\n%d %d\n", m.qtdLinhas, m.qtdColunas);
    printf("%d %d\n", m.inicio.linha, m.inicio.coluna);
    printf("%d %d", m.fim.linha, m.fim.coluna);
    mostraMapa(&m);
    
    printf("\n----------------\n");
    /*int i,j;
    for (i = 0; i < m.qtdLinhas; i++) {
        for (j = 0; j < m.qtdColunas; j++) {
            printf("\n%d",temObra(i,j,NORTE, &m));
            printf("\n%d",temObra(i,j,LESTE, &m));
        }


    }*/
    calcular(&m);

}


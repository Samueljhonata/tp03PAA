#include <stdio.h>
#include <stdlib.h>
#include "cidade.h"

int main(int argc, char** argv) {
    Mapa m;
    
    carregaArquivo("cidade.txt",&m);
    printf("\n---------\n%d %d\n", m.qtdLinhas, m.qtdColunas);
    printf("%d %d\n", m.inicio.linha, m.inicio.coluna);
    printf("%d %d", m.fim.linha, m.fim.coluna);
    mostraMapa(&m);
}


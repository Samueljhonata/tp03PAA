#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "piramide.h"



/*
 * 
 */
int main(int argc, char** argv) {
    Piramide p;
    carregaArquivo("piramide.txt",&p);
    mostrarPiramide(&p);
    printf("\n-----------------------------\n");
    calcularRecursivo(&p);
    printf("\n-----------------------------\n");
    calcularMemoization(&p);
}


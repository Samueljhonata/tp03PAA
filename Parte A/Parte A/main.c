#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "piramide.h"


int main(int argc, char** argv) {
    Piramide p;
    int opcao = -1, carregadoSucesso = 0;
    char nomeArq[50];

    while (opcao != 0) {
        printf("* * * * * * * * * * * M E N U * * * * * * * * * * * \n");
        printf("* 1- Carregar arquivo                             * \n");
        printf("* 2- Mostrar Piramide                             * \n");
        printf("* 3- Calcular rota                                * \n");
        printf("* 0- SAIR                                         * \n");
        printf("* * * * * * * * * * * * * * * * * * * * * * * * * * \n");
        do {
            printf("   Escolha uma opcao:");
            fflush(stdout);
            scanf("%d", &opcao);
            fflush(stdout);
        } while (opcao < 0 || opcao > 3);

        switch (opcao) {
            case 1: //carregar arquivo
                printf("\n Nome do arquivo a ser carregado: ");
                fflush(stdout);
                scanf("%s", &nomeArq);
                fflush(stdout);
                if (carregaArquivo(nomeArq, &p)) {
                    printf("\n Arquivo carregado com sucesso!");
                    carregadoSucesso = 1;
                } else {
                    printf("\n Arquivo nao foi carregado!");
                    carregadoSucesso = 0;
                }
                printf("\n\n");
                break;


            case 2: //mostrar piramide
                if (carregadoSucesso == 1) {
                    mostrarPiramide(&p);
                } else {
                    printf("\n -- Primeiro carregue um arquivo");
                }
                break;

            case 3: //calcular e mostrar rota
                if (carregadoSucesso == 1) {
                    printf("\n -- Recursivo:");
                    calcularRecursivo(&p);
                    
                    printf("\n -- Memoization:");
                    calcularMemoization(&p);
                    
                    printf("\n -- Tras pra Frente:");
                    calcularTrasFrente(&p);
                    
                } else {
                    printf("\n -- Primeiro carregue um arquivo");
                }
                break;

            case 0:
                printf("\n\n");
                printf(" Programa encerrado!");
                return 0;
        }
        printf("\n");

    }

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    //******************
    carregaArquivo("piramide1.txt",&p);
    mostrarPiramide(&p);
    printf("\n-----------------------------\n");
    calcularRecursivo(&p);
    printf("\n-----------------------------\n");
    calcularMemoization(&p);
    printf("\n-----------------------------\n");
    calcularTrasFrente(&p);
}


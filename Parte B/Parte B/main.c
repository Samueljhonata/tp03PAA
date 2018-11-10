#include <stdio.h>
#include <stdlib.h>
#include "cidade.h"

int main(int argc, char** argv) {
    int opcao = -1, carregadoSucesso = 0;
    char nomeArq[50];
    Mapa m;

    while (opcao != 0) {
        printf("* * * * * * * * * * * M E N U * * * * * * * * * * * \n");
        printf("* 1- Carregar arquivo                             * \n");
        printf("* 2- Mostrar Mapa                                 * \n");
        printf("* 3- Calcular Caminhos                            * \n");
        printf("* 4- Mostrar Mapa e Calcular Caminhos             * \n");
        printf("* 0- SAIR                                         * \n");
        printf("* * * * * * * * * * * * * * * * * * * * * * * * * * \n");
        do {
            printf("   Escolha uma opcao:");
            fflush(stdout);
            scanf("%d", &opcao);
            fflush(stdout);
        } while (opcao < 0 || opcao > 4);

        switch (opcao) {
            case 1: //carregar arquivo
                printf("\n Nome do arquivo a ser carregado: ");
                fflush(stdout);
                scanf("%s", &nomeArq);
                fflush(stdout);
                if (carregaArquivo(nomeArq, &m)) {
                    printf("\n Arquivo carregado com sucesso!");
                    carregadoSucesso = 1;
                } else {
                    printf("\n Arquivo nao foi carregado!");
                    carregadoSucesso = 0;
                }
                printf("\n\n");
                break;

            case 2: //mostrar mapa
                if (carregadoSucesso == 1) {
                    mostraMapa(&m);
                } else {
                    printf("\n -- Primeiro carregue um arquivo");
                }
                break;

            case 3: //mostrar e calcular
                if (carregadoSucesso == 1) {
                    calcular(&m);
                } else {
                    printf("\n -- Primeiro carregue um arquivo");
                }
                break;

            case 4: //mostrar e calcular
                if (carregadoSucesso == 1) {
                    mostraMapa(&m);
                    calcular(&m);
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

}


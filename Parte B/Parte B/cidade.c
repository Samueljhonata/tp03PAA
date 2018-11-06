#include "cidade.h"


//https://programacaodescomplicada.wordpress.com/2012/11/09/aula-64-alocacao-dinamica-pt-6-alocacao-de-matrizes/
//Adaptado
int** alocarMatriz(int Linhas, int Colunas) { //Recebe a quantidade de Linhas e Colunas como Parâmetro

    int i, j; //Variáveis Auxiliares

    int **m = (char**) malloc(Linhas * sizeof (char*)); //Aloca um Vetor de Ponteiros

    for (i = 0; i < Linhas; i++) { //Percorre as linhas do Vetor de Ponteiros
        m[i] = (int*) malloc(Colunas * sizeof (int)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
        for (j = 0; j < Colunas; j++) { //Percorre o Vetor de Inteiros atual.
            m[i][j] = 0; //Inicializa com 0.
        }
    }
    return m; //Retorna o Ponteiro para a Matriz Alocada
}

int stringToInt(char *num) {
    int i, n = 0;
    for (i = 0; i < strlen(num); i++) {
        n = (n * 10) + num[i] - 48;
    }
    return n;
}

void inserePosicao(int linha, int coluna, Mapa* mapa, char lado){
    if(lado == 'L'){
        mapa->mapa[linha-1][coluna-1] = 1;
    }
    if(lado == 'N'){
        mapa->mapa[linha-1][coluna-1] = 2;
    }
}

int carregaArquivo(char *nomeArq, Mapa *retorno) {
    FILE *arq;
    arq = fopen(nomeArq, "r");
    char ch;
    char numLinhas[5] = {}, numColunas[5] = {};
    int i = 0, cont = 0;
    int atual = 0;
    char xInicial[5], yInicial[5], xFinal[5], yFinal[5];
    char x[5], y[5], lado;

    if (arq == NULL) { //erro ao carregar arquivo
        printf("ERRO AO LER ARQUIVO");
        return 0;
    } else {
        while (1) { //enquanto o arquivo não termina
            ch = fgetc(arq);
            //printf("\n olhando: %c",ch);
            switch (i) {
                case 0: //tamanhos de linha e coluna
                    if (ch == '\n') {//termina de olhar qtd de linhas e colunas
                        i = 1;
                        numColunas[cont] = '\0';
                        retorno->qtdLinhas = stringToInt(numLinhas);
                        retorno->qtdColunas = stringToInt(numColunas);
                        retorno->mapa = alocarMatriz(retorno->qtdLinhas, retorno->qtdColunas);
                        atual = 0;
                        cont=0;
                    } else {
                        if (ch != ' ') {
                            if (atual == 0) {
                                numLinhas[cont] = ch;
                                cont++;
                            } else {
                                numColunas[cont] = ch;
                                cont++;
                            }
                        } else {
                            atual = 1;
                            numLinhas[cont] = '\0';
                            cont = 0;
                        }
                    }
                    break;

                case 1: //ponto inicial
                    if (ch == '\n') {//termina de olhar ponto inicial
                        i = 2;
                        yInicial[cont] = '\0';
                        retorno->inicio.linha = stringToInt(xInicial)-1;
                        retorno->inicio.coluna = stringToInt(yInicial)-1;
                        retorno->mapa[retorno->inicio.linha][retorno->inicio.coluna] = 6;
                        atual = 0;
                        cont=0;
                    } else {
                        if (ch != ' ') {
                            if (atual == 0) {
                                xInicial[cont] = ch;
                                cont++;
                            } else {
                                yInicial[cont] = ch;
                                cont++;
                            }
                        } else {
                            atual = 1;
                            xInicial[cont] = '\0';
                            cont = 0;
                            
                        }
                    }
                    break;

                case 2: //pronto final
                    if (ch == '\n') {//termina de olhar ponto final
                        i = 3;
                        yFinal[cont] = '\0';
                        retorno->fim.linha = stringToInt(xFinal)-1;
                        retorno->fim.coluna = stringToInt(yFinal)-1;
                        retorno->mapa[retorno->fim.linha][retorno->fim.coluna] = 9;
                        atual = 0;
                        cont=0;
                    } else {
                        if (ch != ' ') {
                            if (atual == 0) {
                                xFinal[cont] = ch;
                                cont++;
                            } else {
                                yFinal[cont] = ch;
                                cont++;
                            }
                        } else {
                            atual = 1;
                            xFinal[cont] = '\0';
                            cont = 0;
                            
                        }
                    }

                    break;

                default: //locais das obras
                    if (ch == '\n' || ch == EOF) {//termina de olhar local
                        //i = 2;
                        y[cont] = '\0';
                        printf("\n************************** %d %d\n", stringToInt(x),stringToInt(y));
                        
                        inserePosicao(stringToInt(x),stringToInt(y),retorno, lado);
                        //retorno->mapa[stringToInt(x)][stringToInt(y)] = 1;
                        atual = 0;
                        cont=0;
                        
                    } else {
                        if (ch != ' ') {
                            if (atual == 0) {
                                x[cont] = ch;
                                cont++;
                            } else if(atual == 1) {
                                y[cont] = ch;
                                cont++;
                            } else if(atual == 2){
                                lado = ch;
                            }
                        } else {
                            if(atual == 0){
                                printf("\nquebra X");
                                atual = 1;
                                x[cont] = '\0';
                                cont = 0;
                            }else if(atual == 1){
                                printf("\nquebra Y");
                                atual = 2;
                                y[cont] = '\0';
                                //cont = 0;
                            }
                            
                        }
                    }
                    
            }
            if(ch == EOF){
                            break;
                        }
        }
    }
    /*            //tamanhos de linha e coluna
                if (i == 0) { //olhando a qtd de linhas e colunas
                    if (ch == '\n') {//termina de olhar qtd de linhas e colunas
                        i = 1;
                        numColunas[cont] = '\0';
                        retorno->qtdLinhas = stringToInt(numLinhas);
                        retorno->qtdColunas = stringToInt(numColunas);
                    } else {
                        if (ch != ' ') {
                            if (atual == 0) {
                                numLinhas[cont] = ch;
                                cont++;
                            } else {
                                numColunas[cont] = ch;
                                cont++;
                            }
                        } else {
                            atual = 1;
                            numLinhas[cont] = '\0';
                            cont = 0;
                        }
                    }
                } else { //depois de pegar qtd de linhas e colunas
                    if (i == 1) { //aloca a matriz uma vez
                        retorno->mapa = alocarMatriz(retorno->qtdLinhas, retorno->qtdColunas);
                        i = 2;
                    }

                    if (ch == '\n') {//quebra de linha
                        l++;
                        c = 0;
                    } else { //pegando os caracteres

                        retorno->mapa[l][c] = ch;
                        c++;
                    }
                }
            }
        }
     */
    fclose(arq);
    return 1;
}

void mostraMapa(Mapa *mapa ){ //imprime o tabuleiro na tela
    int i, j;
    printf("\n Tamanho: n%dx%d\n", mapa->qtdLinhas, mapa->qtdColunas);
    printf(" ");
    for (i = 0; i <= mapa->qtdColunas; i++) {
        printf("__");
    }

    printf("\n");
    for (i = 0; i < mapa->qtdLinhas; i++) {


        for (j = 0; j < mapa->qtdColunas; j++) {
            if (j == 0) {
                printf(" |");
            }
            printf("%d|", mapa->mapa[i][j]);
        }
        printf("|\n");
    }

    printf(" ");
    for (i = 0; i <= mapa->qtdColunas; i++) {
        printf("__");
    }
}

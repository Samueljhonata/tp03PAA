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

//transforma vetor de caracteres em inteiro
int stringToInt(char *num) {
    int i, n = 0;
    for (i = 0; i < strlen(num); i++) {
        n = (n * 10) + num[i] - 48;
    }
    return n;
}

void insereObra(int linha, int coluna, Mapa* mapa, char lado) {
    linha--;
    coluna--;
    if (lado == 'L') {
        if (mapa->mapa[linha][coluna] == NORTE) { //caso ja houver norte inserido
            mapa->mapa[linha][coluna] = NORTE_LESTE;
            return;
        }
        mapa->mapa[linha][coluna] = LESTE;
    }

    if (lado == 'N') {
        if (mapa->mapa[linha][coluna] == LESTE) { //caso ja houver leste inserido
            mapa->mapa[linha][coluna] = NORTE_LESTE;
            return;
        }
        mapa->mapa[linha][coluna] = NORTE;
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
                        cont = 0;
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
                        retorno->inicio.linha = stringToInt(xInicial) - 1;
                        retorno->inicio.coluna = stringToInt(yInicial) - 1;
                        retorno->mapa[retorno->inicio.linha][retorno->inicio.coluna] = 6;
                        atual = 0;
                        cont = 0;
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
                        retorno->fim.linha = stringToInt(xFinal) - 1;
                        retorno->fim.coluna = stringToInt(yFinal) - 1;
                        retorno->mapa[retorno->fim.linha][retorno->fim.coluna] = 9;
                        atual = 0;
                        cont = 0;
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
                        y[cont] = '\0';
                        insereObra(stringToInt(x), stringToInt(y), retorno, lado);
                        atual = 0;
                        cont = 0;

                    } else {
                        if (ch != ' ') {
                            if (atual == 0) {
                                x[cont] = ch;
                                cont++;
                            } else if (atual == 1) {
                                y[cont] = ch;
                                cont++;
                            } else if (atual == 2) {
                                lado = ch;
                            }
                        } else {
                            if (atual == 0) {
                                atual = 1;
                                x[cont] = '\0';
                                cont = 0;
                            } else if (atual == 1) {
                                atual = 2;
                                y[cont] = '\0';
                            }
                        }
                    }
            }
            if (ch == EOF) { //fim do arquivo
                break;
            }
        }
    }

    fclose(arq);
    return 1;
}

//imprime o mapa na tela
void mostraMapa(Mapa *mapa) { 
    int i, j;
    char cI, cF;
    
    printf("Mapa:\n");
    for (i = 0; i <= mapa->qtdLinhas; i++) {//faz borda superior
        printf("_ _ _ _ ");
    }
    printf("\n");

    for (j = mapa->qtdColunas - 1; j >= 0; j--) {

        if (j != mapa->qtdColunas - 1) { //insere as ruas
            for (i = 0; i < mapa->qtdLinhas - 1; i++) {
                printf("          ");
            }
            printf("      |\n");
            for (i = 0; i < mapa->qtdLinhas - 1; i++) {
                printf("|      |MM");
            }

            printf("|      |\n");

            for (i = 0; i < mapa->qtdLinhas - 1; i++) {
                if (mapa->mapa[i][j] == NORTE || mapa->mapa[i][j] == NORTE_LESTE) { //olha se tem obra no norte
                    printf("|  XX  |WW");
                } else {
                    printf("|      |WW");
                }
            }

            if (mapa->mapa[i][j] == NORTE || mapa->mapa[i][j] == NORTE_LESTE) { //olha se tem obra no norte na ultima coluna
                printf("|  XX  |\n|");
            } else {
                printf("|      |\n|");
            }

            for (i = 0; i < mapa->qtdLinhas - 1; i++) {
                printf("          ");
            }

            printf("      |\n");
        }
        for (i = 0; i < mapa->qtdLinhas; i++) {
            if (i == 0) {
                printf("|");
            }

            //para posições inicial e final mostrarem de forma diferente
            if (i == mapa->inicio.linha && j == mapa->inicio.coluna) {
                cI = '(';
                cF = ')';
            } else if (i == mapa->fim.linha && j == mapa->fim.coluna) {
                cI = '[';
                cF = ']';
            } else {
                cI = ' ';
                cF = ' ';
            }

            printf(" %c%d,%d%c", cI, i + 1, j + 1, cF);

            if (i == mapa->qtdLinhas - 1) {
                printf("|");
            } else {
                if (mapa->mapa[i][j] == LESTE || mapa->mapa[i][j] == NORTE_LESTE) { //olha se tem obra no leste
                    printf(" XX ");
                } else {
                    printf("    ");
                }
            }
        }
        printf("\n|");
    }

    printf(" ");
    for (i = 0; i <= mapa->qtdLinhas; i++) { //faz borda inferior
        printf("_ _ _ _ ");
    }
    printf("\n");
 }


//retorna 1 se tem obra ou não existe a posição ou 0 se não tem
int temObra(int linha, int coluna, int direcao, Mapa * mapa) {

    //se não consigo ir para NORTE, na vdd não consigo ir para DIREITA (i,j+1)
    //se não consigo ir para LESTE, na vdd não consigo ir para BAIXO (i+1,j)
    if (direcao == NORTE) {
        if (linha >= mapa->qtdLinhas || linha < 0 || (coluna - 1) >= mapa->qtdColunas || (coluna - 1) < 0) { //se estrapolar o mapa
            return 1;
        }
        if (mapa->mapa[linha][coluna - 1] == NORTE || mapa->mapa[linha][coluna - 1] == NORTE_LESTE) {
            return 1;
        }
    }

    if (direcao == LESTE) {
        if ((linha - 1) >= mapa->qtdLinhas || (linha - 1) < 0 || coluna >= mapa->qtdColunas || coluna < 0) {//se estrapolar o mapa
            return 1;
        }
        if (mapa->mapa[linha - 1][coluna] == LESTE || mapa->mapa[linha - 1][coluna] == NORTE_LESTE) {
            return 1;
        }
    }

    return 0;
}

void calcular(Mapa *m) {
    int i, j;
    int **count = alocarMatriz(m->qtdLinhas + 1, m->qtdColunas + 1);
    int **caminho = alocarMatriz(m->qtdLinhas + 1, m->qtdColunas + 1);
    count[m->fim.linha][m->fim.coluna] = 1;

    //adaptação feita a partir dos slides
    for (i = m->qtdLinhas - 1; i >= 0; i--) {
        for (j = m->qtdColunas - 1; j >= 0; j--) {
            if (j > 0 && !temObra(i, j, NORTE, m)) {
                count[i][j - 1] += count[i][j];
                caminho[i][j] = -1;
            } 

            if (i > 0 && !temObra(i, j, LESTE, m)) {
                count[i - 1][j] += count[i][j];
                caminho[i][j] = 1;
            }
        }
    }

    printf("Count:");
    printf("\n");
    for (j = m->qtdColunas - 1; j >= 0; j--) {
        for (i = 0; i < m->qtdLinhas; i++) {
            printf("%d ", count[i][j]);
        }
        printf("\n");
    }    

    mostraCaminho(count, m);
}

void mostraCaminho(int **count, Mapa *m) {
    int i, j, cont = 0;
    int tamMax = m->qtdColunas * m->qtdLinhas;
    Posicao caminho[tamMax];
    int x = m->inicio.linha, y = m->inicio.coluna;

    while (x < (m->fim.linha) || y < (m->fim.coluna)) { //percorre o caminho
        if (count[x][y] == 0) {
            if (x == m->fim.linha - 1 && y == m->fim.coluna - 1) { //chegada
                caminho[cont].linha = x + 1;
                caminho[cont].coluna = y + 1;
                cont++;
            }
            break;
        }

        //insere posição no caminho
        caminho[cont].linha = x + 1;
        caminho[cont].coluna = y + 1;
        cont++;

        if (count[x + 1][y] > 0 && m->mapa[x][y] != LESTE && m->mapa[x][y] != NORTE_LESTE) { //anda pra leste
            x++;
        } else if (count[x][y + 1] > 0 && m->mapa[x][y] != NORTE && m->mapa[x][y] != NORTE_LESTE) { //anda pra norte
            y++;
        } else { //nao ha caminhos
            cont = 0;
            break;
        }
    }

    printf("\nCaminho possivel: ");
    for (i = 0; i < cont; i++) {
        printf("(%d,%d)-> ", caminho[i].linha, caminho[i].coluna);
    }
    if (cont > 0) {
        printf("(%d,%d)", m->fim.linha + 1, m->fim.coluna + 1);
    } else {
        printf(" Nao ha caminho!");
    }

}
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

void insereObra(int linha, int coluna, Mapa* mapa, char lado){
    if(lado == 'L'){
        mapa->mapa[linha-1][coluna-1] = LESTE;
    }
    if(lado == 'N'){
        mapa->mapa[linha-1][coluna-1] = NORTE;
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
                        //printf("\n************************** %d %d\n", stringToInt(x),stringToInt(y));
                        
                        insereObra(stringToInt(x),stringToInt(y),retorno, lado);
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
                                atual = 1;
                                x[cont] = '\0';
                                cont = 0;
                            }else if(atual == 1){
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
    for (j = mapa->qtdColunas-1; j >= 0; j--) {


        for (i = 0; i < mapa->qtdLinhas; i++) {
            if (i == 0) {
                printf(" |");
            }
            printf("(%d,%d)%d|", i+1,j+1, mapa->mapa[i][j]);
            
        }
        printf("|\n");
    }

    printf(" ");
    for (i = 0; i <= mapa->qtdColunas; i++) {
        printf("__");
    }
    
    printf("\n\n");
    for (i = 0; i < mapa->qtdLinhas; i++) {


        for (j = 0; j < mapa->qtdColunas; j++) {
            if (j == 0) {
                printf(" |");
            }
            printf("(%d,%d)%d|", i+1,j+1, mapa->mapa[i][j]);
            
        }
        printf("|\n");
    }
}


//retorna 1 se tem obra ou não existe a posição ou 0 se não tem
int temObra(int linha, int coluna, int direcao, Mapa * mapa) {
    printf("\n olhando (%d,%d)", linha + 1, coluna + 1);
    if (direcao == NORTE) {
        printf(" N");
    }
    if (direcao == LESTE) {
        printf(" L");
    }

    //se não consigo ir para NORTE, na vdd não consigo ir para DIREITA (i,j+1)
    //se não consigo ir para LESTE, na vdd não consigo ir para BAIXO (i+1,j)
    if (direcao == NORTE) {
        if (linha >= mapa->qtdLinhas || linha < 0 || (coluna - 1) >= mapa->qtdColunas || (coluna - 1) < 0) {
            printf(" para (%d,%d) ERRO", linha + 1, coluna - 1 + 1);
            return 1;
        }
        printf(" para (%d,%d)", linha + 1, coluna - 1 + 1);
        if (mapa->mapa[linha][coluna - 1] == NORTE) {
            return 1;
        }
    }

    if (direcao == LESTE) {
        if ((linha - 1) >= mapa->qtdLinhas || (linha - 1) < 0 || coluna >= mapa->qtdColunas || coluna < 0) {
             printf(" para (%d,%d) ERO", linha -1 + 1, coluna + 1);
            return 1;
        }
        printf(" para (%d,%d)", linha - 1 + 1, coluna + 1);
        if (mapa->mapa[linha - 1][coluna] == LESTE) {
            return 1;
        }
    }

    return 0;
}

void calcular(Mapa *m){
    int **count = alocarMatriz(m->qtdLinhas+1, m->qtdColunas+1);
    int **caminho = alocarMatriz(m->qtdLinhas+1, m->qtdColunas+1);
    
    count[m->fim.linha][m->fim.coluna] = 1;
    
    
    int i,j;
    for (i = m->qtdLinhas-1; i >= 0; i--) {
        for (j = m->qtdColunas-1; j >=0; j--) {
            //printf("\ni=%d  temObra = %d (%d)",i, temObra(i,j,NORTE,m), m->qtdLinhas);
            if (j > 0 && !temObra(i,j,NORTE,m)) {
                printf("\n count[%d][%d]=%d ",i,j-1,count[i][j-1]);
                count[i][j-1] += count[i][j];
                printf("count[%d][%d]= %d",i,j-1 , count[i][j-1]);
                //imprimeCount(count, m);
                
            }else{
                if (j > 0) {
                    caminho[i][j-1] = -1; 
                }
            }
            
            //printf("\ni=%d  temObra = %d",i, temObra(i,j,LESTE,m));
            if (i > 0 && !temObra(i,j,LESTE,m)) {
                printf("\n count[%d][%d]",i,j+1);
                count[i-1][j] += count[i][j];
                //imprimeCount(count, m);
                
            }else{
                if (i > 0) {
                    caminho[i-1][j] = -1;
                }
            }

        }
    }

    imprimeCount(count, m);

    
    imprimeCount(caminho,m);

    
}

void imprimeCount(int ** count, Mapa *m){
    int i,j;
    /*for (i = 0; i < m->qtdLinhas; i++) {
        printf("\n");
        for (j = 0; j < m->qtdColunas; j++) {
            printf("%d ",count[i][j]);

        }
    } */
    
    printf("\n");
    for (j = m->qtdColunas-1; j >= 0; j--) {
        for (i = 0; i < m->qtdLinhas; i++) {
            printf("%d ", count[i][j]);
            
        }
        printf("\n");
    }
}

#include "piramide.h"

//https://programacaodescomplicada.wordpress.com/2012/11/09/aula-64-alocacao-dinamica-pt-6-alocacao-de-matrizes/
//Adaptado

int** alocarMatriz(int Linhas, int Colunas, int valorPadrao) { //Recebe a quantidade de Linhas e Colunas como Parâmetro
    int i, j; //Variáveis Auxiliares
    int **m = (char**) malloc(Linhas * sizeof (char*)); //Aloca um Vetor de Ponteiros

    for (i = 0; i < Linhas; i++) { //Percorre as linhas do Vetor de Ponteiros
        m[i] = (int*) malloc(Colunas * sizeof (int)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
        for (j = 0; j < Colunas; j++) { //Percorre o Vetor de Inteiros atual.
            m[i][j] = valorPadrao; 
        }
    }
    return m; //Retorna o Ponteiro para a Matriz Alocada
}

int** copiaMatriz(int **a, int qtdLinhas, int qtdColunas) { //cria uma nova matriz com os mesmos valores da matriz 'a'
    int **retorno;
    int i, j;
    retorno = alocarMatriz(qtdLinhas, qtdColunas, INFINITO);

    for (i = 0; i < qtdLinhas; i++) {
        for (j = 0; j < qtdColunas; j++) {
            retorno[i][j] = a[i][j];
        }
    }

    return retorno;
}

//transforma vetor de caracteres em inteiro

int stringToInt(char *num) {
    int i, n = 0;
    for (i = 0; i < strlen(num); i++) {
        n = (n * 10) + num[i] - 48;
    }
    return n;
}

void mostrarPiramide(Piramide *p) {
    int i, j;
    printf("\n");
    for (i = 0; i < p->qtdLinhas; i++) {
        for (j = 0; j < p->qtdColunas; j++) {
            if (p->piramide[i][j] < INFINITO) {
                printf("%d ", p->piramide[i][j]);
            }
        }
        printf("\n");

    }

}

int carregaArquivo(char *nomeArq, Piramide *retorno) {
    FILE *arq;
    arq = fopen(nomeArq, "r");
    char ch;
    char linha[200];
    int x = 0, y = 0, qtdLinhas = 0, cont = 0;
    char cNumero[5];

    if (arq == NULL) { //erro ao carregar arquivo
        printf("ERRO AO LER ARQUIVO");
        return 0;
    } else {
        while (fgets(linha, sizeof (linha), arq) != NULL) { //enquanto o arquivo não termina
            //printf("%s",linha);
            qtdLinhas++;
        }

        retorno->qtdLinhas = qtdLinhas;
        retorno->qtdColunas = qtdLinhas;
        retorno->piramide = alocarMatriz(qtdLinhas, qtdLinhas, INFINITO);

        rewind(arq); //volta para o inicio do arquivo

        while (1) { //enquanto o arquivo não termina
            ch = fgetc(arq);

            if (ch != ' ' && ch != '\n' && ch != EOF) {
                cNumero[cont] = ch;
                cont++;


            } else {
                cNumero[cont] = '\0';
                retorno->piramide[x][y] = stringToInt(cNumero);
                cont = 0;
                y++;
                if (ch == '\n') {
                    x++;
                    y = 0;
                }
            }

            if (ch == EOF) { //fim do arquivo
                break;
            }
        }
    }
}

int maximo(int v1, int v2, int *contaComparacoes) {
    (*contaComparacoes)++;
    if (v1 > v2) {
        return v1;
    }
    return v2;
}

int recursivo(int i, int j, int **max, Piramide *p, int *contaComparacoes, int *contaChamadas) {
    (*contaChamadas)++;
    (*contaComparacoes)++;
    if (i == p->qtdLinhas - 1) {
        return p->piramide[i][j];
    }
    
    max[i][j] = p->piramide[i][j] + maximo(recursivo(i + 1, j, max, p,contaComparacoes,contaChamadas), recursivo(i + 1, j + 1, max, p,contaComparacoes,contaChamadas), contaComparacoes);
    return max[i][j];
}

void calcularRecursivo(Piramide *p) {
    int **max = alocarMatriz(p->qtdLinhas, p->qtdColunas, INFINITO); /*copiaMatriz(p->piramide, p->qtdLinhas, p->qtdColunas);*/
    int i = 0, j = 0, contaComparacoes = 0, contaChamadas = 0;

    max[0][0] = recursivo(i, j, max, p, &contaComparacoes, &contaChamadas);

    imprimeResultado(max, p);
    
    printf("\n Comparacoes: %d", contaComparacoes);
    printf("\n Chamadas Recursivas: %d", contaChamadas);
}

int memoization(int i, int j, int **max, Piramide *p, int *contaComparacoes, int *contaChamadas) {
    (*contaChamadas)++;
    (*contaComparacoes)++;
    if (i == p->qtdLinhas - 1) {
        return p->piramide[i][j];
    }
    
    (*contaComparacoes)++;
    if (max[i][j] != INFINITO) {
        return max[i][j];
    }
    max[i][j] = p->piramide[i][j] + maximo(memoization(i + 1, j, max, p,contaComparacoes,contaChamadas), memoization(i + 1, j + 1, max, p,contaComparacoes,contaChamadas), contaComparacoes);
    return max[i][j];
}

void calcularMemoization(Piramide *p) {
    int **max = alocarMatriz(p->qtdLinhas, p->qtdColunas, INFINITO); /*copiaMatriz(p->piramide, p->qtdLinhas, p->qtdColunas);*/
    int i = 0, j = 0, contaComparacoes = 0, contaChamadas = 0;

    max[0][0] = memoization(i, j, max, p, &contaComparacoes, &contaChamadas);

    imprimeResultado(max, p);
    
    printf("\n Comparacoes: %d", contaComparacoes);
    printf("\n Chamadas Recursivas: %d", contaChamadas);
}

void calcularTrasFrente(Piramide *p){
    int **max = copiaMatriz(p->piramide, p->qtdLinhas, p->qtdColunas);
    int i, j, contaComparacoes = 0;
    
    //percorre de baixo pra cima, a partir da penultima linha
    for (i = p->qtdLinhas-2; i >= 0; i--) {
        for (j = 0; j < p->qtdColunas ; j++) {
            contaComparacoes++;
            if (max[i][j] < INFINITO) {
                //verifica pra qual lado deve ir
                contaComparacoes++;
                if ((max[i][j]+max[i+1][j]) > (max[i][j]+max[i+1][j+1])) {
                    max[i][j] += max[i+1][j];
                }else{
                    max[i][j] += max[i+1][j+1];
                }
            }
        }
    }

    imprimeResultado(max,p);
    printf("\n Comparacoes: %d", contaComparacoes);
}

void imprimeResultado(int **max, Piramide *p) {
    int i, j, k;
    
    printf("\n Maior soma = %d\n", max[0][0]);

    i = 1;
    j = 0;
    printf("Caminho:\n%d\n", p->piramide[0][0]);
    while (i < p->qtdLinhas) { //percorre o caminho de cima pra baixo
        if (max[i][j] > max[i][j + 1]) { //se deve ir pra direita
            for (k = 0; k < j; k++) {//insere vazio esquerda
                printf("* ");
            }
            printf("%d ", p->piramide[i][j]);
            
        } else { //se deve ir pra esquerda
            for (k = 0; k < j + 1; k++) {//insere vazio esquerda
                printf("* ");
            }
            printf("%d ", p->piramide[i][j + 1]);
            j++;
        }
        for (k = j; k < i; k++) { //insere vazio direita
            printf("* ");
        }
        i++;
        printf("\n");
    }

}
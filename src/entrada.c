#include <stdio.h>
#include <stdlib.h>
#include "entrada.h"

int lerInteiro(const char *mensagem, int minimo, int maximo) {
    char buffer[100];
    char *fim;
    long valor;

    while (1) {
        printf("%s", mensagem);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\nEntrada encerrada. Saindo do programa.\n");
            exit(0);
        }
        valor = strtol(buffer, &fim, 10);
        if (fim == buffer || (*fim != '\n' && *fim != '\0')) {
            printf("Valor invalido. Digite um numero inteiro.\n");
        } else if (valor < minimo || valor > maximo) {
            printf("Valor fora do intervalo. Digite entre %d e %d.\n", minimo, maximo);
        } else {
            return (int)valor;
        }
    }
}

double lerReal(const char *mensagem) {
    char buffer[100];
    char *fim;
    double valor;

    while (1) {
        printf("%s", mensagem);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\nEntrada encerrada. Saindo do programa.\n");
            exit(0);
        }
        valor = strtod(buffer, &fim);
        if (fim == buffer || (*fim != '\n' && *fim != '\0')) {
            printf("Valor invalido. Digite um numero (use ponto para decimais).\n");
        } else {
            return valor;
        }
    }
}

void lerMatriz(Matriz *m, int numero) {
    char mensagem[100];
    int i, j;

    printf("\n--- Matriz %d ---\n", numero);
    m->linhas = lerInteiro("Quantidade de linhas: ", 1, MAX_DIM);
    m->colunas = lerInteiro("Quantidade de colunas: ", 1, MAX_DIM);

    for (i = 0; i < m->linhas; i++) {
        for (j = 0; j < m->colunas; j++) {
            sprintf(mensagem, "Elemento [%d][%d]: ", i + 1, j + 1);
            m->dados[i][j] = lerReal(mensagem);
        }
    }
}

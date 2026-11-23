#include <stdio.h>
#include <math.h>
#include "exibicao.h"

void exibirMatriz(const Matriz *m) {
    int i, j;
    double valor;

    for (i = 0; i < m->linhas; i++) {
        printf("| ");
        for (j = 0; j < m->colunas; j++) {
            valor = m->dados[i][j];
            if (fabs(valor) < TOLERANCIA) {
                valor = 0.0;
            }
            printf("%10.3f ", valor);
        }
        printf("|\n");
    }
}

void exibirMenu(void) {
    printf("\n===== MENU DE OPERACOES =====\n");
    printf("1 - Adicao\n");
    printf("2 - Subtracao\n");
    printf("3 - Multiplicacao\n");
    printf("4 - Divisao matricial (A x B^-1)\n");
    printf("0 - Encerrar programa\n");
}

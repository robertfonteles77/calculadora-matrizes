#include <stdio.h>
#include "matriz.h"
#include "entrada.h"
#include "exibicao.h"
#include "operacoes.h"

int main(void) {
    Matriz matrizes[MAX_MATRIZES];
    Matriz resultado;
    int quantidade, opcao, i;

    printf("===== CALCULADORA DE MATRIZES =====\n");
    printf("(Tamanho maximo de cada matriz: %dx%d)\n\n", MAX_DIM, MAX_DIM);

    quantidade = lerInteiro("Quantas matrizes deseja utilizar (minimo 2)? ", 2, MAX_MATRIZES);

    for (i = 0; i < quantidade; i++) {
        lerMatriz(&matrizes[i], i + 1);
    }

    printf("\nMatrizes cadastradas:\n");
    for (i = 0; i < quantidade; i++) {
        printf("\nMatriz %d (%dx%d):\n", i + 1, matrizes[i].linhas, matrizes[i].colunas);
        exibirMatriz(&matrizes[i]);
    }

    do {
        exibirMenu();
        opcao = lerInteiro("Escolha uma opcao: ", 0, 4);

        if (opcao != 0) {
            if (executarOperacao(opcao, matrizes, quantidade, &resultado)) {
                printf("\nMatriz resultante (%dx%d):\n", resultado.linhas, resultado.colunas);
                exibirMatriz(&resultado);
            } else {
                printf("\nA operacao nao pode ser realizada.\n");
            }
        }
    } while (opcao != 0);

    printf("\nPrograma encerrado.\n");
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_MATRIZES 10
#define MAX_DIM 10
#define TOLERANCIA 1e-9

typedef struct {
    int linhas;
    int colunas;
    double dados[MAX_DIM][MAX_DIM];
} Matriz;

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

int mesmasDimensoes(const Matriz *a, const Matriz *b) {
    return a->linhas == b->linhas && a->colunas == b->colunas;
}

int podeMultiplicar(const Matriz *a, const Matriz *b) {
    return a->colunas == b->linhas;
}

int ehQuadrada(const Matriz *m) {
    return m->linhas == m->colunas;
}

int somar(const Matriz *a, const Matriz *b, Matriz *res) {
    int i, j;

    if (!mesmasDimensoes(a, b)) {
        printf("Erro: adicao exige matrizes com as mesmas dimensoes (%dx%d e %dx%d).\n",
               a->linhas, a->colunas, b->linhas, b->colunas);
        return 0;
    }
    res->linhas = a->linhas;
    res->colunas = a->colunas;
    for (i = 0; i < a->linhas; i++) {
        for (j = 0; j < a->colunas; j++) {
            res->dados[i][j] = a->dados[i][j] + b->dados[i][j];
        }
    }
    return 1;
}

int subtrair(const Matriz *a, const Matriz *b, Matriz *res) {
    int i, j;

    if (!mesmasDimensoes(a, b)) {
        printf("Erro: subtracao exige matrizes com as mesmas dimensoes (%dx%d e %dx%d).\n",
               a->linhas, a->colunas, b->linhas, b->colunas);
        return 0;
    }
    res->linhas = a->linhas;
    res->colunas = a->colunas;
    for (i = 0; i < a->linhas; i++) {
        for (j = 0; j < a->colunas; j++) {
            res->dados[i][j] = a->dados[i][j] - b->dados[i][j];
        }
    }
    return 1;
}

int multiplicar(const Matriz *a, const Matriz *b, Matriz *res) {
    int i, j, k;

    if (!podeMultiplicar(a, b)) {
        printf("Erro: multiplicacao exige colunas da primeira = linhas da segunda "
               "(%dx%d e %dx%d).\n", a->linhas, a->colunas, b->linhas, b->colunas);
        return 0;
    }
    res->linhas = a->linhas;
    res->colunas = b->colunas;
    for (i = 0; i < a->linhas; i++) {
        for (j = 0; j < b->colunas; j++) {
            res->dados[i][j] = 0.0;
            for (k = 0; k < a->colunas; k++) {
                res->dados[i][j] += a->dados[i][k] * b->dados[k][j];
            }
        }
    }
    return 1;
}

int inverter(const Matriz *m, Matriz *inv) {
    double aux[MAX_DIM][MAX_DIM];
    int n = m->linhas;
    int i, j, k, linhaPivo;
    double pivo, fator, temp;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            aux[i][j] = m->dados[i][j];
            inv->dados[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
    inv->linhas = n;
    inv->colunas = n;

    for (i = 0; i < n; i++) {

        linhaPivo = i;
        for (k = i + 1; k < n; k++) {
            if (fabs(aux[k][i]) > fabs(aux[linhaPivo][i])) {
                linhaPivo = k;
            }
        }
        if (fabs(aux[linhaPivo][i]) < TOLERANCIA) {
            return 0;
        }

        if (linhaPivo != i) {
            for (j = 0; j < n; j++) {
                temp = aux[i][j];
                aux[i][j] = aux[linhaPivo][j];
                aux[linhaPivo][j] = temp;

                temp = inv->dados[i][j];
                inv->dados[i][j] = inv->dados[linhaPivo][j];
                inv->dados[linhaPivo][j] = temp;
            }
        }

        pivo = aux[i][i];
        for (j = 0; j < n; j++) {
            aux[i][j] /= pivo;
            inv->dados[i][j] /= pivo;
        }

        for (k = 0; k < n; k++) {
            if (k != i) {
                fator = aux[k][i];
                for (j = 0; j < n; j++) {
                    aux[k][j] -= fator * aux[i][j];
                    inv->dados[k][j] -= fator * inv->dados[i][j];
                }
            }
        }
    }
    return 1;
}

int dividir(const Matriz *a, const Matriz *b, Matriz *res) {
    Matriz inversa;

    if (!ehQuadrada(b)) {
        printf("Erro: a matriz divisora precisa ser quadrada (ela e %dx%d).\n",
               b->linhas, b->colunas);
        return 0;
    }
    if (!podeMultiplicar(a, b)) {
        printf("Erro: divisao A x B^-1 exige colunas de A = linhas de B (%dx%d e %dx%d).\n",
               a->linhas, a->colunas, b->linhas, b->colunas);
        return 0;
    }
    if (!inverter(b, &inversa)) {
        printf("Erro: a matriz divisora e singular (determinante zero) e nao possui inversa.\n");
        return 0;
    }
    return multiplicar(a, &inversa, res);
}

int executarOperacao(int opcao, const Matriz matrizes[], int quantidade, Matriz *resultado) {
    Matriz parcial, novo;
    int i, ok;

    parcial = matrizes[0];

    for (i = 1; i < quantidade; i++) {
        switch (opcao) {
            case 1: ok = somar(&parcial, &matrizes[i], &novo); break;
            case 2: ok = subtrair(&parcial, &matrizes[i], &novo); break;
            case 3: ok = multiplicar(&parcial, &matrizes[i], &novo); break;
            default: ok = dividir(&parcial, &matrizes[i], &novo); break;
        }
        if (!ok) {
            printf("(Falha na etapa com a matriz %d.)\n", i + 1);
            return 0;
        }
        parcial = novo;
    }
    *resultado = parcial;
    return 1;
}

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

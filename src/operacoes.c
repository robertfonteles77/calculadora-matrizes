#include <stdio.h>
#include <math.h>
#include "operacoes.h"
#include "validacao.h"

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

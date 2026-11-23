#include "validacao.h"

int mesmasDimensoes(const Matriz *a, const Matriz *b) {
    return a->linhas == b->linhas && a->colunas == b->colunas;
}

int podeMultiplicar(const Matriz *a, const Matriz *b) {
    return a->colunas == b->linhas;
}

int ehQuadrada(const Matriz *m) {
    return m->linhas == m->colunas;
}

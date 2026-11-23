#ifndef VALIDACAO_H
#define VALIDACAO_H

#include "matriz.h"

int mesmasDimensoes(const Matriz *a, const Matriz *b);
int podeMultiplicar(const Matriz *a, const Matriz *b);
int ehQuadrada(const Matriz *m);

#endif

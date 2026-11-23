#ifndef OPERACOES_H
#define OPERACOES_H

#include "matriz.h"

int somar(const Matriz *a, const Matriz *b, Matriz *res);
int subtrair(const Matriz *a, const Matriz *b, Matriz *res);
int multiplicar(const Matriz *a, const Matriz *b, Matriz *res);
int inverter(const Matriz *m, Matriz *inv);
int dividir(const Matriz *a, const Matriz *b, Matriz *res);
int executarOperacao(int opcao, const Matriz matrizes[], int quantidade, Matriz *resultado);

#endif

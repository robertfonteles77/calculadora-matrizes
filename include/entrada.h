#ifndef ENTRADA_H
#define ENTRADA_H

#include "matriz.h"

int lerInteiro(const char *mensagem, int minimo, int maximo);
double lerReal(const char *mensagem);
void lerMatriz(Matriz *m, int numero);

#endif

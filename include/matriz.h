#ifndef MATRIZ_H
#define MATRIZ_H

#define MAX_MATRIZES 10
#define MAX_DIM 10
#define TOLERANCIA 1e-9

typedef struct {
    int linhas;
    int colunas;
    double dados[MAX_DIM][MAX_DIM];
} Matriz;

#endif

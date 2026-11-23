# Calculadora de Matrizes em C

## Objetivo

Sistema interativo em linguagem C que permite cadastrar duas ou mais matrizes e realizar operações matemáticas entre elas: adição, subtração, multiplicação e divisão matricial.

## Funcionalidades

- Cadastro de 2 a 10 matrizes (tamanho máximo de cada matriz: 10x10).
- Para cada matriz, o usuário informa as linhas, as colunas e cada elemento individualmente.
- Exibição das matrizes cadastradas.
- Menu com as operações: adição, subtração, multiplicação e divisão matricial.
- As operações usam as matrizes na ordem em que foram informadas, da esquerda para a direita.
- Exibição da matriz resultante de forma organizada (linhas e colunas).
- Mensagem de erro quando a operação não é possível (dimensões incompatíveis, divisor não quadrado ou singular).
- Possibilidade de realizar novas operações ou encerrar o programa.
- Validação das entradas (texto no lugar de número, valores fora do intervalo etc.).

## Regras matemáticas

- **Adição e subtração:** exigem matrizes com as mesmas dimensões.
- **Multiplicação:** o número de colunas da matriz da esquerda deve ser igual ao número de linhas da matriz da direita, em cada etapa.
- **Divisão:** A / B = A × B⁻¹. A matriz B deve ser quadrada, inversível e ter dimensões compatíveis com A. O programa avisa quando B é singular (sem inversa).
- Com três ou mais matrizes, as operações são feitas em sequência, da esquerda para a direita. Exemplo: `(M1 / M2) / M3`.

## Estrutura do projeto

```
calculadora-matrizes/
├── Makefile
├── README.md
├── include/
│   ├── matriz.h
│   ├── entrada.h
│   ├── exibicao.h
│   ├── validacao.h
│   └── operacoes.h
└── src/
    ├── main.c
    ├── entrada.c
    ├── exibicao.c
    ├── validacao.c
    └── operacoes.c
```

- `src/main.c`: função `main()`, que apenas coordena o fluxo do programa.
- `src/`: arquivos `.c` com a implementação das funções, separados por responsabilidade.
- `include/`: arquivos de cabeçalho (`.h`) com a estrutura `Matriz`, as constantes e as declarações das funções.
- `Makefile`: automatiza a compilação.

## Compilação e execução

Requisito: compilador GCC. Execute os comandos na pasta principal do projeto (onde está o `Makefile`).

**Com Makefile:**

```bash
make
./calculadora_matrizes
```

Para apagar o executável: `make clean`.

**Sem Makefile (comando direto):**

```bash
gcc -Wall -Wextra -std=c99 -Iinclude -o calculadora_matrizes src/main.c src/entrada.c src/exibicao.c src/validacao.c src/operacoes.c -lm
./calculadora_matrizes
```

No Windows (MinGW), execute `calculadora_matrizes.exe`.

## Funções implementadas

| Arquivo | Função | Responsabilidade |
|---|---|---|
| `src/main.c` | `main` | Coordena o fluxo principal do programa |
| `src/entrada.c` | `lerInteiro` | Lê e valida um número inteiro dentro de um intervalo |
| `src/entrada.c` | `lerReal` | Lê e valida um número real |
| `src/entrada.c` | `lerMatriz` | Lê linhas, colunas e elementos de uma matriz |
| `src/exibicao.c` | `exibirMatriz` | Mostra uma matriz organizada em linhas e colunas |
| `src/exibicao.c` | `exibirMenu` | Mostra o menu de operações |
| `src/validacao.c` | `mesmasDimensoes` | Verifica se duas matrizes têm as mesmas dimensões |
| `src/validacao.c` | `podeMultiplicar` | Verifica se a multiplicação é possível |
| `src/validacao.c` | `ehQuadrada` | Verifica se a matriz é quadrada |
| `src/operacoes.c` | `somar` | Soma duas matrizes |
| `src/operacoes.c` | `subtrair` | Subtrai duas matrizes |
| `src/operacoes.c` | `multiplicar` | Multiplica duas matrizes |
| `src/operacoes.c` | `inverter` | Calcula a inversa (Gauss-Jordan); informa se é singular |
| `src/operacoes.c` | `dividir` | Calcula A × B⁻¹ com as validações necessárias |
| `src/operacoes.c` | `executarOperacao` | Aplica a operação escolhida em sequência sobre todas as matrizes |

## Exemplos de utilização

**Exemplo 1: adição e multiplicação**

Matrizes informadas:

```
A = | 1  2 |      B = | 4  7 |
    | 3  4 |          | 2  6 |
```

- Adição (opção 1): `| 5 9 |` e `| 5 10 |`
- Subtração (opção 2): `| -3 -5 |` e `| 1 -2 |`
- Multiplicação (opção 3): `| 8 19 |` e `| 20 45 |`

**Exemplo 2: divisão**

Com as mesmas matrizes A e B, a opção 4 calcula A × B⁻¹:

```
| 0.200   0.100 |
| 1.000  -0.500 |
```

**Exemplo 3: operação impossível**

Duas matrizes 2x3 na multiplicação:

```
Erro: multiplicacao exige colunas da primeira = linhas da segunda (2x3 e 2x3).
A operacao nao pode ser realizada.
```

**Exemplo 4: divisor singular**

Com B = `| 1 2 |` e `| 2 4 |`:

```
Erro: a matriz divisora e singular (determinante zero) e nao possui inversa.
```

## Testes realizados

- Todas as operações com duas matrizes 2x2 (resultados conferidos à mão).
- Multiplicação de uma matriz 2x3 por uma 3x2.
- Operações com três matrizes (soma, multiplicação e divisão sequenciais).
- Dimensões incompatíveis na soma e na multiplicação.
- Divisor não quadrado e divisor singular.
- Elementos decimais e negativos.
- Entradas inválidas (letras, números fora do intervalo, quantidade de matrizes menor que 2).

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

## Compilação e execução

Requisito: compilador GCC.

```bash
gcc -Wall -Wextra -std=c99 -o calculadora_matrizes calculadora_matrizes.c -lm
./calculadora_matrizes
```

No Windows (MinGW), execute `calculadora_matrizes.exe`.

## Funções implementadas

| Função | Responsabilidade |
|---|---|
| `lerInteiro` | Lê e valida um número inteiro dentro de um intervalo |
| `lerReal` | Lê e valida um número real |
| `lerMatriz` | Lê linhas, colunas e elementos de uma matriz |
| `exibirMatriz` | Mostra uma matriz organizada em linhas e colunas |
| `exibirMenu` | Mostra o menu de operações |
| `mesmasDimensoes` | Verifica se duas matrizes têm as mesmas dimensões |
| `podeMultiplicar` | Verifica se a multiplicação é possível |
| `ehQuadrada` | Verifica se a matriz é quadrada |
| `somar` | Soma duas matrizes |
| `subtrair` | Subtrai duas matrizes |
| `multiplicar` | Multiplica duas matrizes |
| `inverter` | Calcula a inversa (Gauss-Jordan); informa se é singular |
| `dividir` | Calcula A × B⁻¹ com as validações necessárias |
| `executarOperacao` | Aplica a operação escolhida em sequência sobre todas as matrizes |
| `main` | Coordena o fluxo principal do programa |

## Exemplos de utilização

**Exemplo 1: adição e multiplicação**

Matrizes informadas:

```
A = | 1  2 |      B = | 4  7 |
    | 3  4 |          | 2  6 |
```

- Adição (opção 1): `| 5 9 |` e `| 5 10 |`
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
- Operações com três matrizes (soma, multiplicação e divisão sequenciais).
- Dimensões incompatíveis na soma e na multiplicação.
- Divisor não quadrado e divisor singular.
- Entradas inválidas (letras, números fora do intervalo, quantidade de matrizes menor que 2).

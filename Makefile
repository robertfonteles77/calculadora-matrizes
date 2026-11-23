CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
TARGET = calculadora_matrizes
SRC = src/main.c src/entrada.c src/exibicao.c src/validacao.c src/operacoes.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) -lm

clean:
	rm -f $(TARGET) $(TARGET).exe

.PHONY: all clean

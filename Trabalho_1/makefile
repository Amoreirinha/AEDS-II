# Nome do projeto
PROJ_NAME = pilha

# Fontes e cabeçalhos
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
DEPS = $(wildcard *.h)

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -g -pedantic

# Regra principal
all: $(PROJ_NAME)

# Linkagem
$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^

# Compilação dos objetos
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJ) $(PROJ_NAME)

# Para facilitar, adiciona 'phony' para evitar conflitos com arquivos reais
.PHONY: all clean

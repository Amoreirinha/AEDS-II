# Nome do projeto
PROJ_NAME = palindromo

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -g -pedantic -std=c99

# Flags para Windows (descomente se necessário)
# CFLAGS += -D_WIN32

# Fontes e objetos
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

# Regra principal
all: $(PROJ_NAME)

# Linkagem
$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Compilação dos objetos
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJ) $(PROJ_NAME)

# Limpeza completa (incluindo arquivos de backup)
distclean: clean
	rm -f *~ *.bak

# Para reinstalar
re: clean all

# Para facilitar, adiciona 'phony' para evitar conflitos com arquivos reais
.PHONY: all clean distclean re
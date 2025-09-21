# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c99 -g

# Nome do executável
TARGET = lista

# Arquivos fonte
SRCS = fila.c

# Arquivos objeto
OBJS = $(SRCS:.c=.o)

# Arquivo de cabeçalho
HEADER = fila.h

# Regra padrão
all: $(TARGET)

# Compilar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilar arquivos objeto
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $<

# Limpar arquivos compilados
clean:
	rm -f $(OBJS) $(TARGET)

# Recompilar tudo
re: clean all

# Executar o programa
run: $(TARGET)
	./$(TARGET)

# Debug com valgrind
debug: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Verificar dependências
deps:
	$(CC) -MM $(SRCS)

# Ajuda
help:
	@echo "Makefile para Lista Duplamente Encadeada"
	@echo ""
	@echo "Comandos disponíveis:"
	@echo "  make all     - Compila o programa (padrão)"
	@echo "  make clean   - Remove arquivos objeto e executável"
	@echo "  make re      - Recompila tudo"
	@echo "  make run     - Executa o programa"
	@echo "  make debug   - Executa com valgrind para detectar memory leaks"
	@echo "  make deps    - Mostra dependências dos arquivos"
	@echo "  make help    - Mostra esta ajuda"

.PHONY: all clean re run debug deps help
# Makefile para Listas de Prioridade
# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = priority_queues
SOURCE = priority_queues.c

# Regra principal
all: $(TARGET)

# Compilar o programa principal
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

# Compilar com debug information
debug: CFLAGS += -g -DDEBUG
debug: $(TARGET)

# Compilar com otimização máxima
release: CFLAGS += -O3
release: $(TARGET)

# Executar o programa
run: $(TARGET)
	./$(TARGET)

# Executar com valgrind para detectar memory leaks
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Limpar arquivos compilados
clean:
	rm -f $(TARGET) *.o

# Instalar (copiar para /usr/local/bin - requer permissão)
install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/

# Desinstalar
uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)

# Ajuda
help:
	@echo "Targets disponíveis:"
	@echo "  all       - Compila o programa (padrão)"
	@echo "  debug     - Compila com informações de debug"
	@echo "  release   - Compila com otimização máxima"
	@echo "  run       - Executa o programa"
	@echo "  valgrind  - Executa com valgrind para detectar memory leaks"
	@echo "  clean     - Remove arquivos compilados"
	@echo "  install   - Instala no sistema (requer sudo)"
	@echo "  uninstall - Remove do sistema (requer sudo)"
	@echo "  help      - Mostra esta ajuda"

# Regra padrão
.PHONY: all debug release run valgrind clean install uninstall help
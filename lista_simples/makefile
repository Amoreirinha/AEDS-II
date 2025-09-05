# Nome do projeto
PROJ_NAME := lista

# Fontes e cabeçalhos
SRC := $(wildcard *.c)
HDR := $(wildcard *.h)
OBJ := $(SRC:.c=.o)

# Compilador e flags
CC := gcc
CFLAGS := -Wall -g -pedantic

# Regra padrão
.PHONY: all clean help

all: $(PROJ_NAME)

# Linkagem
$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^

# Compilação
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	@echo "Removendo arquivos objeto e executável..."
	rm -f $(OBJ) $(PROJ_NAME) *~

# Ajuda
help:
	@echo "Uso:"
	@echo "  make         # Compila o projeto"
	@echo "  make clean   # Remove arquivos gerados"
	@echo "  make help    # Mostra esta mensagem"

# Dependências automáticas
-include $(OBJ:.o=.d)

%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
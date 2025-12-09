CC = gcc
CFLAGS = -Wall -Wextra -g3
TARGET = output/main
SOURCES = main.c tabela_hash.c funcoes_hash.c
OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

run: $(TARGET)
	./$(TARGET)
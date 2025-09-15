#ifndef _H_FILA
#define _H_FILA

#include <stdbool.h>

typedef struct no {
    int valor;
    struct no *proximo;
} no;

typedef struct f {
    no *inicio;
    no *fim;
    int quant;
} fila;

fila *criar_fila();
bool ehCheia(fila *Fila);
bool ehVazia(fila *Fila);
void add(fila *Fila, int item);
void mostrar(fila *Fila);
int delete(fila* Fila);
void liberar_fila(fila *Fila);

#endif // _H_FILA
#ifndef _H_FILA
#define _H_FILA

typedef struct f
{
    int inicio;
    int fim;
    int tamanho;
    int quant;
    int *items;
} fila;
fila *criar_fila(int tamanho);
bool ehCheia(fila *Fila);
bool ehVazia(fila *Fila);
void add(fila *Fila, int item);
void mostrar(fila *Fila);
int delete(fila* Fila);

#endif // _H_FILA
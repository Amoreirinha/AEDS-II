#ifndef _H_PILHA
#define _H_PILHA

typedef struct itens
{
    int valor;
    struct itens *prox;
} Item;

typedef struct pilha
{
    Item *topo;
    int tamanho;
} Pilha;

void push(Pilha *pilha, int item);
int pop(Pilha *pilha);
int obtem_elemento(Pilha *pilha);
void mostrar_pilha_inteira(Pilha *pilha);
void libera_pilha(Pilha *pilha);

#endif // _H_PILHA
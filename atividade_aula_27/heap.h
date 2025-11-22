#ifndef _H_HEAP_
#define _H_HEAP_

struct Heap {
 int max;
 int pos;
 int* prioridade;
};

struct Heap* heap_inicializa(int max);

void heap_insere(struct Heap* heap, int prioridade);

void troca(int a, int b, int* v);

void corrige_acima(struct Heap* heap, int pos);

int heap_remove(struct Heap* heap);

void corrige_abaixo(int *prios, int atual, int tam);

int heap_vazia(struct Heap* heap);

int heap_cheia(struct Heap* heap);

void heap_libera(struct Heap* heap);

void heap_imprime(struct Heap* heap);

#endif
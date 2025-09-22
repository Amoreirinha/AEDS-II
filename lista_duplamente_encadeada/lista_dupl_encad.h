#ifndef _H_FILA
#define _H_FILA

#include <stdbool.h>

typedef struct no {
    int valor;
    struct no *prev;
    struct no *next;
} no;

typedef struct lista {
    no *inicio;
    no *fim;
    int quant;
} lista;

lista *criar_lista();
bool ehCheia(lista *Lista);
bool ehVazia(lista *Lista);
int tamanho(lista *Lista);
void inserir_inicio(lista *Lista, int item);
void inserir_fim(lista *Lista, int item);
void inserir_posicao(lista *Lista, int item, int posicao);
int remover_inicio(lista *Lista);
int remover_fim(lista *Lista);
int remover_posicao(lista *Lista, int posicao);
int buscar_valor(lista *Lista, int valor);
int buscar_posicao(lista *Lista, int posicao);
void mostrar(lista *Lista);
void mostrar_inverso(lista *Lista);
void liberar_lista(lista *Lista);

#endif // _H_FILA
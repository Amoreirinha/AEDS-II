#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista_dupl_encad.h"

lista *criar_lista()
{
    lista *Lista = (lista *)malloc(sizeof(lista));
    Lista->inicio = NULL;
    Lista->fim = NULL;
    Lista->quant = 0;
    return Lista;
}

bool ehCheia(lista *Lista)
{
    return false; // Lista encadeada nunca fica cheia
}

bool ehVazia(lista *Lista)
{
    return (Lista->quant == 0);
}

int tamanho(lista *Lista)
{
    return Lista->quant;
}

void inserir_inicio(lista *Lista, int item)
{
    no *novo_no = (no *)malloc(sizeof(no));
    if (novo_no == NULL) {
        printf("\nErro: memória insuficiente\n");
        return;
    }
    
    novo_no->valor = item;
    novo_no->prev = NULL;
    novo_no->next = Lista->inicio;
    
    if (ehVazia(Lista))
    {
        Lista->fim = novo_no;
    }
    else
    {
        Lista->inicio->prev = novo_no;
    }
    
    Lista->inicio = novo_no;
    Lista->quant++;
    
    printf("\nItem %d inserido no início da lista\n", item);
    mostrar(Lista);
}

void inserir_fim(lista *Lista, int item)
{
    no *novo_no = (no *)malloc(sizeof(no));
    if (novo_no == NULL) {
        printf("\nErro: memória insuficiente\n");
        return;
    }
    
    novo_no->valor = item;
    novo_no->next = NULL;
    novo_no->prev = Lista->fim;
    
    if (ehVazia(Lista))
    {
        Lista->inicio = novo_no;
    }
    else
    {
        Lista->fim->next = novo_no;
    }
    
    Lista->fim = novo_no;
    Lista->quant++;
    
    printf("\nItem %d inserido no final da lista\n", item);
    mostrar(Lista);
}

void inserir_posicao(lista *Lista, int item, int posicao)
{
    if (posicao < 0 || posicao > Lista->quant) {
        printf("\nPosição inválida!\n");
        return;
    }
    
    if (posicao == 0) {
        inserir_inicio(Lista, item);
        return;
    }
    
    if (posicao == Lista->quant) {
        inserir_fim(Lista, item);
        return;
    }
    
    no *novo_no = (no *)malloc(sizeof(no));
    if (novo_no == NULL) {
        printf("\nErro: memória insuficiente\n");
        return;
    }
    
    novo_no->valor = item;
    
    // Encontrar a posição de inserção
    no *atual;
    if (posicao <= Lista->quant / 2) {
        // Percorre do início
        atual = Lista->inicio;
        for (int i = 0; i < posicao - 1; i++) {
            atual = atual->next;
        }
    } else {
        // Percorre do fim (vantagem da lista duplamente encadeada)
        atual = Lista->fim;
        for (int i = Lista->quant - 1; i > posicao; i--) {
            atual = atual->prev;
        }
    }
    
    // Inserir o novo nó
    novo_no->next = atual->next;
    novo_no->prev = atual;
    atual->next->prev = novo_no;
    atual->next = novo_no;
    
    Lista->quant++;
    printf("\nItem %d inserido na posição %d\n", item, posicao);
    mostrar(Lista);
}

int remover_inicio(lista *Lista)
{
    if (ehVazia(Lista))
    {
        printf("\nLista vazia. Impossível remover elementos\n");
        return -1;
    }

    no *primeiro = Lista->inicio;
    int item = primeiro->valor;
    
    Lista->inicio = primeiro->next;
    
    if (Lista->inicio == NULL)
    {
        Lista->fim = NULL;
    }
    else
    {
        Lista->inicio->prev = NULL;
    }
    
    free(primeiro);
    Lista->quant--;
    
    printf("\nItem %d removido do início da lista\n", item);
    return item;
}

int remover_fim(lista *Lista)
{
    if (ehVazia(Lista))
    {
        printf("\nLista vazia. Impossível remover elementos\n");
        return -1;
    }

    no *ultimo = Lista->fim;
    int item = ultimo->valor;
    
    Lista->fim = ultimo->prev;
    
    if (Lista->fim == NULL)
    {
        Lista->inicio = NULL;
    }
    else
    {
        Lista->fim->next = NULL;
    }
    
    free(ultimo);
    Lista->quant--;
    
    printf("\nItem %d removido do final da lista\n", item);
    return item;
}

int remover_posicao(lista *Lista, int posicao)
{
    if (ehVazia(Lista))
    {
        printf("\nLista vazia. Impossível remover elementos\n");
        return -1;
    }
    
    if (posicao < 0 || posicao >= Lista->quant) {
        printf("\nPosição inválida!\n");
        return -1;
    }
    
    if (posicao == 0) {
        return remover_inicio(Lista);
    }
    
    if (posicao == Lista->quant - 1) {
        return remover_fim(Lista);
    }
    
    no *atual;
    if (posicao <= Lista->quant / 2) {
        // Percorre do início
        atual = Lista->inicio;
        for (int i = 0; i < posicao; i++) {
            atual = atual->next;
        }
    } else {
        // Percorre do fim
        atual = Lista->fim;
        for (int i = Lista->quant - 1; i > posicao; i--) {
            atual = atual->prev;
        }
    }
    
    int item = atual->valor;
    atual->prev->next = atual->next;
    atual->next->prev = atual->prev;
    
    free(atual);
    Lista->quant--;
    
    printf("\nItem %d removido da posição %d\n", item, posicao);
    return item;
}

int buscar_valor(lista *Lista, int valor)
{
    no *atual = Lista->inicio;
    int posicao = 0;
    
    while (atual != NULL)
    {
        if (atual->valor == valor) {
            printf("\nValor %d encontrado na posição %d\n", valor, posicao);
            return posicao;
        }
        atual = atual->next;
        posicao++;
    }
    
    printf("\nValor %d não encontrado na lista\n", valor);
    return -1;
}

int buscar_posicao(lista *Lista, int posicao)
{
    if (posicao < 0 || posicao >= Lista->quant) {
        printf("\nPosição inválida!\n");
        return -1;
    }
    
    no *atual;
    if (posicao <= Lista->quant / 2) {
        atual = Lista->inicio;
        for (int i = 0; i < posicao; i++) {
            atual = atual->next;
        }
    } else {
        atual = Lista->fim;
        for (int i = Lista->quant - 1; i > posicao; i--) {
            atual = atual->prev;
        }
    }
    
    printf("\nValor na posição %d: %d\n", posicao, atual->valor);
    return atual->valor;
}

void mostrar(lista *Lista)
{
    printf("\nLista (início → fim):\n");
    if (ehVazia(Lista))
    {
        printf("Lista vazia!\n");
        return;
    }

    no *atual = Lista->inicio;
    int posicao = 0;
    
    printf("Pos: ");
    while (atual != NULL)
    {
        printf("%d\t", posicao++);
        atual = atual->next;
    }
    
    atual = Lista->inicio;
    printf("\nVal: ");
    while (atual != NULL)
    {
        printf("%d\t", atual->valor);
        atual = atual->next;
    }
    printf("\n\n");
}

void mostrar_inverso(lista *Lista)
{
    printf("\nLista (fim → início):\n");
    if (ehVazia(Lista))
    {
        printf("Lista vazia!\n");
        return;
    }

    no *atual = Lista->fim;
    int posicao = Lista->quant - 1;
    
    printf("Pos: ");
    while (atual != NULL)
    {
        printf("%d\t", posicao--);
        atual = atual->prev;
    }
    
    atual = Lista->fim;
    printf("\nVal: ");
    while (atual != NULL)
    {
        printf("%d\t", atual->valor);
        atual = atual->prev;
    }
    printf("\n\n");
}

void liberar_lista(lista *Lista)
{
    no *atual = Lista->inicio;
    no *proximo;
    
    while (atual != NULL)
    {
        proximo = atual->next;
        free(atual);
        atual = proximo;
    }
    
    free(Lista);
}

int main()
{
    int val, pos, n;
    bool aux;
    lista *Lista = criar_lista();
    
    do
    {
        printf("\n************************* MENU ************************");
        printf("\n1. Inserir no início");
        printf("\n2. Inserir no final");
        printf("\n3. Inserir em posição específica");
        printf("\n4. Remover do início");
        printf("\n5. Remover do final");
        printf("\n6. Remover de posição específica");
        printf("\n7. Buscar valor");
        printf("\n8. Buscar por posição");
        printf("\n9. Mostrar lista (início→fim)");
        printf("\n10. Mostrar lista inversa (fim→início)");
        printf("\n11. Tamanho da lista");
        printf("\n12. Lista vazia?");
        printf("\n13. Lista cheia?");
        printf("\n14. Sair");
        printf("\n Digite sua escolha : ");
        scanf("%d", &n);
        
        switch (n)
        {
        case 1:
            printf("\nDigite o valor: ");
            scanf("%d", &val);
            inserir_inicio(Lista, val);
            break;
        case 2:
            printf("\nDigite o valor: ");
            scanf("%d", &val);
            inserir_fim(Lista, val);
            break;
        case 3:
            printf("\nDigite o valor: ");
            scanf("%d", &val);
            printf("Digite a posição: ");
            scanf("%d", &pos);
            inserir_posicao(Lista, val, pos);
            break;
        case 4:
            printf("\nElemento removido: %d", remover_inicio(Lista));
            break;
        case 5:
            printf("\nElemento removido: %d", remover_fim(Lista));
            break;
        case 6:
            printf("\nDigite a posição: ");
            scanf("%d", &pos);
            printf("Elemento removido: %d", remover_posicao(Lista, pos));
            break;
        case 7:
            printf("\nDigite o valor a buscar: ");
            scanf("%d", &val);
            buscar_valor(Lista, val);
            break;
        case 8:
            printf("\nDigite a posição: ");
            scanf("%d", &pos);
            buscar_posicao(Lista, pos);
            break;
        case 9:
            mostrar(Lista);
            break;
        case 10:
            mostrar_inverso(Lista);
            break;
        case 11:
            printf("\nTamanho da lista: %d\n", tamanho(Lista));
            break;
        case 12:
            aux = ehVazia(Lista);
            printf(aux ? "\nLista vazia\n" : "\nLista não está vazia\n");
            break;
        case 13:
            aux = ehCheia(Lista);
            printf(aux ? "\nLista cheia\n" : "\nLista não está cheia\n");
            break;
        case 14:
            liberar_lista(Lista);
            return 0;
        default:
            printf("\nOpção inválida!");
            break;
        }
    } while (1);

    return 0;
}
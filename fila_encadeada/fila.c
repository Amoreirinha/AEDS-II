#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fila.h"

fila *criar_fila()
{
    fila *Fila = (fila *)malloc(sizeof(fila));
    Fila->inicio = NULL;
    Fila->fim = NULL;
    Fila->quant = 0;
    return Fila;
}

bool ehCheia(fila *Fila)
{
    // Lista encadeada nunca fica cheia (a menos que a memória acabe)
    return false;
}

bool ehVazia(fila *Fila)
{
    return (Fila->quant == 0);
}

void add(fila *Fila, int item)
{
    no *novo_no = (no *)malloc(sizeof(no));
    if (novo_no == NULL) {
        printf("\nErro: memória insuficiente\n");
        return;
    }
    
    novo_no->valor = item;
    novo_no->proximo = NULL;
    
    if (ehVazia(Fila))
    {
        Fila->inicio = novo_no;
        Fila->fim = novo_no;
    }
    else
    {
        Fila->fim->proximo = novo_no;
        Fila->fim = novo_no;
    }
    
    Fila->quant++;
    printf("\nItem %d inserido no final da fila\n", item);
    mostrar(Fila);
}

void mostrar(fila *Fila)
{
    printf("\nFila:\n");
    if (ehVazia(Fila))
    {
        printf("Fila vazia!\n");
        return;
    }

    no *atual = Fila->inicio;
    int posicao = 0;
    
    while (atual != NULL)
    {
        printf("%d\t", atual->valor);
        atual = atual->proximo;
        posicao++;
    }
    printf("\n\n");
}

int delete(fila *Fila)
{
    if (ehVazia(Fila))
    {
        printf("\nFila vazia. Impossível remover elementos\n");
        return -1;
    }

    no *primeiro = Fila->inicio;
    int item = primeiro->valor;
    
    Fila->inicio = primeiro->proximo;
    
    // Se era o único elemento, atualiza o fim também
    if (Fila->inicio == NULL)
    {
        Fila->fim = NULL;
    }
    
    free(primeiro);
    Fila->quant--;
    
    printf("\nItem %d removido do início da fila\n", item);
    return item;
}

void liberar_fila(fila *Fila)
{
    no *atual = Fila->inicio;
    no *proximo;
    
    while (atual != NULL)
    {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    
    free(Fila);
}

int main()
{
    int val, n;
    bool aux;
    fila *Fila = criar_fila();
    
    do
    {
        printf("\n************************* MENU ************************");
        printf("\n1. Adicionar a fila");
        printf("\n2. Retirar da fila");
        printf("\n3. Mostrar Fila");
        printf("\n4. Fila vazia?");
        printf("\n5. Fila cheia?");
        printf("\n6. Sair");
        printf("\n Digite sua escolha : ");
        scanf("%d", &n);
        
        switch (n)
        {
        case 1:
            printf("\nDigite o valor ");
            scanf("%d", &val);
            add(Fila, val);
            break;
        case 2:
            printf("\nElemento retirado : %d", delete(Fila));
            break;
        case 3:
            mostrar(Fila);
            break;
        case 4:
            aux = ehVazia(Fila);
            if (aux)
            {
                printf("\nFila vazia");
            }
            else
            {
                printf("\nFila não está vazia");
            }
            break;
        case 5:
            aux = ehCheia(Fila);
            if (aux)
            {
                printf("\nFila cheia");
            }
            else
            {
                printf("\nFila não está cheia (lista encadeada ilimitada)");
            }
            break;
        case 6:
            liberar_fila(Fila);
            return (1);
            break;
        default:
            printf("\nOpção errada!");
            break;
        }
    } while (1);

    return (0);
}
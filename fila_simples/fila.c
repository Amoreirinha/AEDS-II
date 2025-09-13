#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "fila.h"

fila *criar_fila(int tamanho)
{
    fila *Fila = (fila *)malloc(sizeof(fila));
    Fila->tamanho = tamanho;
    Fila->quant = 0;
    Fila->inicio = -1;
    Fila->fim = -1;
    Fila->items = (int *)malloc(Fila->tamanho * sizeof(int));
    return Fila;
}

bool ehCheia(fila *Fila)
{
    return (Fila->quant == Fila->tamanho);
}

bool ehVazia(fila *Fila)
{
    return (Fila->quant == 0);
}

void add(fila *Fila, int item)
{
    if (ehCheia(Fila))
    {
        printf("\nFila cheia. Impossível inserir elementos");
        return;
    }
    else if (ehVazia(Fila))
    {
        Fila->inicio++;
        Fila->fim++;
        Fila->quant++;
        Fila->items[Fila->fim] = item;
        printf("\nItem %d inserido na posição %d\n", Fila->items[Fila->fim], Fila->fim);
        mostrar(Fila);
    }
    else
    {
        Fila->fim = (Fila->fim + 1) % Fila->tamanho;
        Fila->items[Fila->fim] = item;
        Fila->quant++;
        printf("\nItem %d inserido na posição %d\n", Fila->items[Fila->fim], Fila->fim);
        mostrar(Fila);
    }
}

void mostrar(fila *Fila)
{
    printf("\nFila:\n");
    if (ehVazia(Fila))
    {
        printf("Fila vazia!\n");
        return;
    }

    int i = Fila->inicio;
    int count = 0;

    while (count < Fila->quant)
    {
        printf("%d\t", Fila->items[i]);
        i = (i + 1) % Fila->tamanho;
        count++;
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

    int item = Fila->items[Fila->inicio];

    if (Fila->quant == 1)
    {
        Fila->inicio = -1;
        Fila->fim = -1;
    }
    else
    {
        Fila->inicio = (Fila->inicio + 1) % Fila->tamanho;
    }

    Fila->quant--;
    printf("\nItem %d removido da posição %d\n", item, Fila->inicio);
    return item;
}

int main()
{
    int val, n;
    bool aux;
    fila *Fila = criar_fila(5);
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
                printf("\nFila não está cheia");
            }
            break;
        case 6:
            free(Fila->items);
            free(Fila);
            return (1);
            break;
        default:
            printf("\nOpção errada!");
            break;
        }
    } while (1);

    return (0);
}

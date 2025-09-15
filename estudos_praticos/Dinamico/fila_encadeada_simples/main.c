#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct n
{
    int valor;
    struct n *prox;
} no;

no *insere(no *inicio, no *fim)
{
    no *novo = malloc(sizeof(no));
    int valor;
    printf("\nDigite o valor a ser inserido: ");
    scanf("%d", &valor);
    novo->valor = valor;
    novo->prox = NULL;

    if (fim != NULL)
    {
        fim->prox = novo;
        fim = novo;
    }
    else
    {
        inicio = novo;
        fim = novo;
    }

    return novo;
}

no *remover(no *inicio, no *fim)
{
    no *removido = NULL;
    if (inicio != NULL)
    {
        removido = inicio;
        inicio = inicio->prox;
    }

    return removido;
}

void mostrar(no *inicio, no *fim)
{
    printf("\n\nINICIO ");
    no *temp = inicio;
    while (temp != NULL)
    {
        printf("%d ", temp->valor);
        temp = temp->prox;
    }
    printf("FIM\n");
}

int main()
{
    no *inicio = NULL;
    no *fim = NULL;
    int choice = 0;
    bool run = true;

    while (run)
    {
        switch (choice)
        {
        case 0:
            printf("\nMENU\n1. Insere\n2. Remove\n3. Mostrar\n4. Sair\n");
            scanf("%d", &choice);
            break;
        case 1:
            fim = insere(inicio, fim);
            if (inicio == NULL)
                inicio = fim;
            choice = 0;
            break;
        case 2:
        {
            no *removido = remover(inicio, fim);
            if (removido != NULL)
            {
                printf("Removido: %d\n", removido->valor);
                inicio = removido->prox;
                free(removido);
                inicio = (inicio != NULL) ? inicio : NULL;
                if (inicio == NULL)
                    fim = NULL;
            }
            else
            {
                printf("Fila vazia!\n");
            }
            choice = 0;
            break;
        }
        case 3:
            mostrar(inicio, fim);
            choice = 0;
            break;
        case 4:
            run = false;
            break;
        default:
            printf("Opcao invalida!\n");
            choice = 0;
            break;
        }
    }
    while (inicio != NULL)
    {
        no *temp = inicio;
        inicio = inicio->prox;
        free(temp);
    }
    return 0;
}
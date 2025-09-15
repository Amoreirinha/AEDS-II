#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct n
{
    int valor;
    struct n *prox;
} no;

typedef struct br
{
    no *ende;
    no *ant;
} bus_remove;

no *busca(no *ptlista, int valor)
{
    no *ant = ptlista;
    no *prox = ptlista->prox;

    while (prox != NULL)
    {
        if (prox->valor < valor)
        {
            ant = prox;
            prox = prox->prox;
        }
        else if (prox->valor == valor)
        {
            return prox;
        }
        else if (prox->valor < valor)
        {
            break;
        }
    }

    return NULL;
}

no *busca_insere(no *ptlista, int valor)
{
    no *ant = ptlista;
    no *prox = ptlista->prox;

    while (prox != NULL)
    {
        if (prox->valor < valor)
        {
            ant = prox;
            prox = prox->prox;
        }
        else if (prox->valor == valor)
        {
            return NULL;
        }
        else
        {
            break;
        }
    }

    return ant;
}

no *busca_remove(no *ptlista, int valor)
{
    no *ant = ptlista;
    no *prox = ptlista->prox;

    while (prox != NULL)
    {
        if (prox->valor < valor)
        {
            ant = prox;
            prox = prox->prox;
        }
        else if (prox->valor == valor)
        {
            return ant;
        }
        else
        {
            break;
        }
    }

    return NULL;
}

bool insere(no *ptlista)
{
    int valor;
    printf("\nDigite o valor a ser inserido: ");
    scanf("%d", &valor);
    no *ende = busca_insere(ptlista, valor);
    if (ende == NULL)
        return false;

    no *novo = malloc(sizeof(no));
    novo->valor = valor;
    novo->prox = ende->prox;
    ende->prox = novo;
    return true;
}

no *remover(no *ptlista)
{
    int valor;
    printf("\nDigite o valor a ser removido: ");
    scanf("%d", &valor);
    no *ende = busca_remove(ptlista, valor);
    if (ende == NULL)
        return NULL;

    no *removido = ende->prox;
    if (removido == NULL)
        return NULL;
    ende->prox = removido->prox;
    return removido;
}

void mostrar_lista(no *ptlista)
{
    no *ant = ptlista;
    no *prox = ptlista->prox;

    printf("\n\nLISTA: ");
    while (prox != NULL)
    {
        printf("%d ", prox->valor);
        ant = prox;
        prox = prox->prox;
    }
}

int main()
{
    no lista;
    lista.prox = NULL;
    no *ptlista = &lista;
    int choice = 0;
    bool run = true;

    while (run)
    {
        switch (choice)
        {
        case 0:
            printf("\nMENU\n1. Buscar Elemento\n2. Inserir Elemento\n3. Remover Elemento\n4. Mostrar Lista\n5. Sair\n");
            scanf("%d", &choice);
            break;
        case 1:
        {
            int valor;
            printf("\nDigite o valor a ser buscado: ");
            scanf("%d", &valor);
            no *res = busca(ptlista, valor);
            if (res != NULL)
                printf("Elemento %d encontrado.\n", valor);
            else
                printf("Elemento %d nao encontrado.\n", valor);
            choice = 0;
            break;
        }
        case 2:
            if (insere(ptlista))
                printf("Elemento inserido com sucesso.\n");
            else
                printf("Elemento ja existe ou erro ao inserir.\n");
            choice = 0;
            break;
        case 3:
        {
            no *rem = remover(ptlista);
            if (rem != NULL)
            {
                printf("Elemento %d removido.\n", rem->valor);
                free(rem);
            }
            else
            {
                printf("Elemento nao encontrado para remocao.\n");
            }
            choice = 0;
            break;
        }
        case 4:
            mostrar_lista(ptlista);
            choice = 0;
            break;
        case 5:
            run = false;
            break;
        default:
            printf("Opcao invalida.\n");
            choice = 0;
            break;
        }
    }

    while (ptlista->prox != NULL)
    {
        no *temp = ptlista->prox;
        ptlista->prox = temp->prox;
        free(temp);
    }

    return 0;
}
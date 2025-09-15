#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct n
{
    int valor;
    struct n *prox;
    struct n *ant;
} no;

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
    novo->ant = ende;

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
    no *temp = removido->prox;
    temp->ant = ende;
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

void mostrar_lista_inversa(no *ptlista){
    no *ant = ptlista;
    no *prox = ptlista->prox;

    printf("\n\nLISTA inversa: ");
    while (prox != NULL)
    {
        ant = prox;
        prox = prox->prox;
    }
    while (ant != ptlista)
    {
        printf("%d ", ant->valor);
        ant = ant->ant;
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
            printf("\nMENU\n1. Buscar Elemento\n2. Inserir Elemento\n3. Remover Elemento\n4. Mostrar Lista\n5. Mostrar Lista Inversa\n6. Sair\n");
            scanf("%d", &choice);
            break;
        case 1:
        {
            int valor;
            printf("\nDigite o valor a ser buscado: ");
            scanf("%d", &valor);
            no *resultado = busca(ptlista, valor);
            if (resultado != NULL)
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
            no *removido = remover(ptlista);
            if (removido != NULL)
            {
            printf("Elemento %d removido com sucesso.\n", removido->valor);
            free(removido);
            }
            else
            printf("Elemento nao encontrado ou erro ao remover.\n");
            choice = 0;
            break;
        }
        case 4:
            mostrar_lista(ptlista);
            choice = 0;
            break;
        case 5:
            mostrar_lista_inversa(ptlista);
            choice = 0;
            break;
        case 6:
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
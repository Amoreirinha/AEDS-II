#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct v
{
    int key;
    int value;
} vector;

const int TAM = 5;

bool ehVazia(int inicio, int fim)
{
    if (inicio == fim && inicio == -1)
        return true;
    return false;
}

bool ehCheia(int inicio, int fim, int tam)
{
    if (inicio == 0)
    {
        if (fim == tam - 1)
            return true;
    }
    else if (fim == inicio - 1)
    {
        return true;
    }

    return false;
}

void mostrar_fila(vector *fila, int inicio, int fim, int tam)
{
    if (ehVazia(inicio, fim))
    {
        printf("\nFila vazia");
        return;
    }

    printf("\nInicio\t");
    int i = inicio;
    while (true)
    {
        printf("%d\t", fila[i].value);
        if (i == fim)
            break;
        i = (i + 1) % tam;
    }
    printf("Fim\n");
}

void insere(vector *fila, int *fim, int *inicio, int tam)
{
    if (ehCheia(*inicio, *fim, tam))
    {
        printf("\nFila lotada\n");
        return;
    }
    else
    {
        int value;
        printf("Digite o valor a ser inserido: ");
        scanf("%d", &value);
        if (ehVazia(*inicio, *fim))
        {
            *inicio = 0;
            *fim = 0;
            fila[*fim].value = value;
            fila[*fim].key = *fim;
        }
        else
        {
            *fim = (*fim + 1) % tam;
            fila[*fim].value = value;
            fila[*fim].key = *fim;
        }
    }
}

void remover(vector *fila, int *fim, int *inicio, int tam)
{
    if (ehVazia(*inicio, *fim))
    {
        printf("\nFila Vazia\n");
        return;
    }
    else
    {
        printf("Removendo valor: %d\n", fila[*inicio].value);
        if (*inicio == *fim)
        {
            *fim = -1;
            *inicio = -1;
        }
        else
        {
            *inicio = (*inicio + 1) % tam;
        }
    }
}

int main()
{
    int inicio = -1;
    int fim = -1;
    vector fila[TAM];
    bool run = true;
    int choice = 0;

    while (run)
    {
        switch (choice)
        {
        case 0:
            printf("Menu\n1. Mostrar\n2. eh Cheia\n3. eh Vazia\n4. Inserir\n5. Remover\n6. Sair\n");
            scanf("%d", &choice);
            break;
        case 1:
            mostrar_fila(fila, inicio, fim, TAM);
            choice = 0;
            break;
        case 2:
            if (ehCheia(inicio, fim, TAM))
                printf("Fila está cheia\n");
            else
                printf("Fila não está cheia\n");
            choice = 0;
            break;
        case 3:
            if (ehVazia(inicio, fim))
                printf("Fila está vazia\n");
            else
                printf("Fila não está vazia\n");
            choice = 0;
            break;
        case 4:
            insere(fila, &fim, &inicio, TAM);
            choice = 0;
            break;
        case 5:
            remover(fila, &fim, &inicio, TAM);
            choice = 0;
            break;
        case 6:
            run = false;
            break;
        default:
            printf("Opção inválida\n");
            choice = 0;
            break;
        }
    }
    return 0;
}
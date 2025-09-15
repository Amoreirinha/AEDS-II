#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct v
{
    int key;
    int value;
} vector;

const int TAM = 10;

// Função que verifica se a pilha está vazia.
// Retorna true se o topo for -1, indicando que não há elementos.
bool ehVazio(int topo)
{
    if (topo == -1)
        return true;
    return false;
}

// Função que verifica se a pilha está cheia.
// Retorna true se o topo for igual ao tamanho máximo - 1.
bool ehCheio(int topo, int tam)
{
    if (topo == tam - 1)
        return true;
    return false;
}

// Função para mostrar todos os elementos da pilha.
// Percorre do topo até o início, exibindo chave e valor de cada elemento.
void mostrar_pilha(vector *pilha, int topo)
{
    printf("KEY - VALUE\n");
    for (int i = topo; i >= 0; i--)
    {
        printf("%d - %d\n", pilha[i].key, pilha[i].value);
    }
}

// Função para inserir um novo elemento na pilha.
// Primeiro verifica se a pilha está cheia.
// Se não estiver, lê o valor do usuário, incrementa o topo e insere o valor e a chave.
void insere(vector *pilha, int *topo, int tam)
{
    if (ehCheio(*topo, tam))
    {
        printf("\nPilha Cheia\n");
        return;
    }
    int value;
    printf("Digite o valor a ser inserido: ");
    scanf("%d", &value);
    *topo = *topo + 1; // Incrementa o topo para apontar para o novo elemento.
    pilha[*topo].value = value; // Insere o valor.
    pilha[*topo].key = *topo;   // Define a chave como o índice do topo.
}

// Função para remover o elemento do topo da pilha.
// Primeiro verifica se a pilha está vazia.
// Se não estiver, decrementa o topo, "removendo" o elemento.
void remover(int *topo)
{
    if (ehVazio(*topo))
    {
        printf("\nPilha Vazia\n");
        return;
    }
    *topo = *topo - 1; // Decrementa o topo, removendo o elemento do topo.
}

int main()
{
    vector pilha[TAM];
    int topo = -1;
    int choice = 0;
    bool run = true;

    while (run)
    {

        switch (choice)
        {
        case 0:
            printf("Menu\n1. Mostrar pilha\n2. eh cheia\n3. eh vazia\n4. inserir\n5. remove\n6. sair\n");
            scanf("%d", &choice);
            break;

        case 1:
            mostrar_pilha(pilha, topo);
            choice = 0;
            break;

        case 2:
            if (ehCheio(topo, TAM))
                printf("A pilha está cheia.\n");
            else
                printf("A pilha não está cheia.\n");
            choice = 0;
            break;

        case 3:
            if (ehVazio(topo))
                printf("A pilha está vazia.\n");
            else
                printf("A pilha não está vazia.\n");
            choice = 0;
            break;

        case 4:
            insere(pilha, &topo, TAM);
            choice = 0;
            break;

        case 5:
            remover(&topo);
            choice = 0;
            break;

        case 6:
            printf("Saindo...\n");
            run = false;
            break;

        default:
            printf("Opção inválida.\n");
            choice = 0;
            break;
        }
    }

    return 0;
}
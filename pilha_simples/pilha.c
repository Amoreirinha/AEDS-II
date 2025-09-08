#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "pilha.h"

// Verifica se a pilha está vazia
bool ehVazia(Pilha *pilha)
{
    // Se o topo == NULL, então a pilha é vazia
    if (pilha->topo == NULL)
    {
        return (true);
    }
    return (false);
}

// Insere um elemento no topo da pilha
void push(Pilha *pilha, int item)
{
    Item *novo_item = (Item *)malloc(sizeof(Item)); // Aloca novo item
    if (pilha->topo == NULL)
    {
        // Se a pilha está vazia, novo item será o topo
        novo_item->valor = item;
        novo_item->prox = NULL;
        pilha->topo = novo_item;
        pilha->tamanho++;
    }
    else
    {
        // Se não está vazia, novo item aponta para o topo atual
        novo_item->valor = item;
        novo_item->prox = pilha->topo;
        pilha->topo = novo_item;
        pilha->tamanho++;
    }
    printf("\nLista com %d elementos", pilha->tamanho);
}

// Remove e retorna o elemento do topo da pilha
int pop(Pilha *pilha)
{
    // Se a pilha estiver vazia, não tem como remover nenhum elemento
    if (ehVazia(pilha))
    {
        printf("\nPilha  vazia. Impossível remover elementos");
        return -1;
    }
    // Remove o elemento no topo da pilha e diminui o topo
    Item *item_removido = pilha->topo;
    pilha->topo = pilha->topo->prox;
    pilha->tamanho--;
    int valor = item_removido->valor;
    free(item_removido); // Libera memória do item removido
    printf("\nLista com %d elementos", pilha->tamanho);
    return valor;
}

// Obtém o valor do elemento no topo da pilha sem removê-lo
int obtem_elemento(Pilha *pilha)
{
    // Se a pilha estiver vazia, não tem como obter nenhum elemento
    if (ehVazia(pilha))
    {
        printf("\nPilha  vazia. Impossível obter elementos");
        return INT_MIN;
    }
    // Retorna o elemento do topo da pilha
    printf("\nLista com %d elementos", pilha->tamanho);
    return pilha->topo->valor;
}

// Mostra todos os elementos da pilha
void mostrar_pilha_inteira(Pilha *pilha)
{
    if (ehVazia(pilha))
    {
        printf("\nPilha  vazia. Impossível mostrar elementos");
        return;
    }
    Item *atual = pilha->topo;
    printf("\nTamanho da pilha: %d", pilha->tamanho);
    printf("\nElementos da pilha: ");
    printf("\n------\n");
    printf("| %d |\t<-- TOPO\n", atual->valor); // Mostra topo
    atual = atual->prox;
    while (true)
    {
        if (atual->prox == NULL)
        {
            break;
        }
        printf("------\n");
        printf("| %d |\n", atual->valor); // Mostra elementos intermediários
        atual = atual->prox;
    }
    printf("------\n");
    printf("| %d |<-- FUNDO\n", atual->valor); // Mostra fundo
    printf("\n");
}

// Libera toda a memória alocada para a pilha
void libera_pilha(Pilha *pilha)
{
    Item *atual = pilha->topo;
    Item *prox;
    while (atual != NULL)
    {
        prox = atual->prox;
        free(atual); // Libera cada item
        atual = prox;
    }
    free(pilha); // Libera estrutura da pilha
    printf("\n\nPilha liberada com sucesso\n\n");
}

// Função principal: menu de operações da pilha
int main()
{
    int val, n, temp;
    bool aux;
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha)); // Cria pilha
    pilha->topo = NULL;
    pilha->tamanho = 0;

    do
    {
        // Exibe menu de opções
        printf("\n************************* MENU ************************");
        printf("\n1. Push");
        printf("\n2. Pop");
        printf("\n3. Obtém elemento");
        printf("\n4. Pilha vazia?");
        printf("\n5. Mostrar Lista Completa");
        printf("\n6. Sair");
        printf("\n Digite sua escolha : ");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            // Insere elemento
            printf("\nDigite o valor ");
            scanf("%d", &val);
            push(pilha, val);
            break;
        case 2:
            // Remove elemento do topo
            temp = pop(pilha);
            if (temp != -1)
            {
                printf("\nElemento retirado : %d", temp);
            }
            else
            {
                printf("\nNenhum elemento retirado");
            }
            break;
        case 3:
            // Obtém elemento do topo
            temp = obtem_elemento(pilha);
            if (temp == INT_MIN)
            {
                printf("\nNenhum elemento no topo");
            }
            else
            {
                printf("\nElemento do topo: %d", temp);
            }
            break;
        case 4:
            // Verifica se pilha está vazia
            aux = ehVazia(pilha);
            if (aux)
            {
                printf("\nPilha vazia");
            }
            else
            {
                printf("\nPilha não está vazia");
            }
            break;
        case 5:
            // Mostra todos os elementos da pilha
            mostrar_pilha_inteira(pilha);
            break;
        case 6:
            // Libera pilha e encerra programa
            libera_pilha(pilha);
            return (1);
            break;
        default:
            printf("\nOpção errada!");
            break;
        }
    } while (1); // Repete até o usuário escolher sair
    return (0);
}

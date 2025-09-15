#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct n
{
    int valor;
    struct n *prox;
} no;

no* insere(no* topo){
    int valor;
    printf("\nDigite o valor a ser inserido: ");
    scanf("%d", &valor);
    no* novo = malloc(sizeof(no));
    novo->valor = valor;
    novo->prox = topo;
    return novo;
}

no* remover(no* topo){
    if(topo == NULL){
        printf("\nPilha Vazia");
        return NULL;
    }
    no* removido = topo;
    topo = topo->prox;
    return removido;
}

void motrar(no* topo){
    no* temp = topo;
    printf("\nPILHA:\n\n|TOPO|");
    while(temp != NULL){
        printf("\n| %d |", temp->valor);
        temp = temp->prox;
    }
    printf("\n|INICIO|");
}

int main(){
    no* topo = NULL;
    int choice = 0;
    bool run = true;

    while(run){
        switch (choice)
        {
        case 0:
            printf("\nMenu\n1. Inserir\n2. Remover\n3. Mostrar\n4. Sair\nEscolha: ");
            scanf("%d", &choice);
            break;
        case 1:
            topo = insere(topo);
            choice = 0;
            break;
        case 2: {
            no* removido = remover(topo);
            if(removido != NULL){
                printf("\nRemovido: %d\n", removido->valor);
                topo = topo->prox;
                free(removido);
            }
            choice = 0;
            break;
        }
        case 3:
            motrar(topo);
            choice = 0;
            break;
        case 4:
            run = false;
            break;
        default:
            printf("\nOpção inválida!\n");
            choice = 0;
            break;
        }
    }
    while(topo != NULL){
        no* temp = topo;
        topo = topo->prox;
        free(temp);
    }

    return 0;
}
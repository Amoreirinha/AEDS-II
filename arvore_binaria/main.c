#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// #include "arvore_bin.h"

/*
 * ESTRUTURA DA ÁRVORE BINÁRIA DE BUSCA (ABB)
 * 
 * Conceito: Árvore binária onde para cada nó:
 * - Todos os valores na subárvore esquerda são MENORES que o nó
 * - Todos os valores na subárvore direita são MAIORES que o nó
 * - Não permite valores duplicados
 */

// Definição da estrutura do nó da árvore
typedef struct n {
    int valor;          // Valor armazenado no nó
    struct n *esq;      // Ponteiro para subárvore esquerda (valores menores)
    struct n *dir;      // Ponteiro para subárvore direita (valores maiores)
} no;

/*
 * FUNÇÃO: insere
 * Propósito: Insere um novo nó na árvore binária de busca mantendo a propriedade de ordenação
 * Complexidade: O(h) onde h é a altura da árvore
 * 
 * Funcionamento:
 * - Se a raiz é NULL, retorna o novo nó (árvore vazia ou chegou na posição de inserção)
 * - Se o valor do novo nó é MENOR que a raiz, insere recursivamente na subárvore esquerda
 * - Se o valor do novo nó é MAIOR que a raiz, insere recursivamente na subárvore direita
 * - Retorna a raiz (possivelmente atualizada) para manter a estrutura da árvore
 */
no* insere(no* raiz, no* n){
    // Caso base: encontrou posição de inserção
    if (raiz == NULL)
        return n;
    
    // Inserção recursiva na subárvore adequada
    if (raiz->valor > n->valor)
        raiz->esq = insere(raiz->esq, n);  // Inserir na esquerda se valor é menor
    else
        raiz->dir = insere(raiz->dir, n);  // Inserir na direita se valor é maior ou igual
    
    return raiz;  // Retorna a raiz inalterada (estrutura não muda acima do ponto de inserção)
}

/*
 * FUNÇÃO: novo_no
 * Propósito: Cria e insere um novo nó na árvore a partir de entrada do usuário
 * 
 * Funcionamento:
 * - Aloca memória para novo nó
 * - Lê valor do usuário
 * - Inicializa ponteiros como NULL
 * - Chama função insere para adicionar na posição correta
 * - Atualiza a raiz da árvore através de ponteiro para ponteiro
 */
void novo_no(no** raiz){
    // Alocação de memória para novo nó
    no* n = (no*) malloc(sizeof(no));
    
    // Entrada do usuário
    printf("Digite o valor do novo nó: ");
    scanf("%d", &n->valor);
    
    // Inicialização dos ponteiros (novo nó é sempre uma folha inicialmente)
    n->esq = NULL;
    n->dir = NULL;

    // Insere na árvore e atualiza raiz se necessário
    *raiz = insere(*raiz, n);
    printf("Novo nó inserido");
}

/*
 * FUNÇÃO: busca
 * Propósito: Busca um valor na árvore binária de busca
 * Complexidade: O(h) onde h é a altura da árvore
 * 
 * Funcionamento:
 * - Caso base: raiz NULL (não encontrado) ou valor encontrado
 * - Se valor buscado é MENOR que raiz, busca na subárvore esquerda
 * - Se valor buscado é MAIOR que raiz, busca na subárvore direita
 * - Retorna ponteiro para nó encontrado ou NULL se não existe
 */
no* busca(no* raiz, int valor){
    // Casos base: árvore vazia ou valor encontrado na raiz
    if(raiz == NULL || raiz->valor == valor)
        return raiz;
    
    // Busca recursiva na subárvore adequada
    if (raiz->valor > valor)
        return busca(raiz->esq, valor);  // Busca na esquerda se valor é menor
    else
        return busca(raiz->dir, valor);  // Busca na direita se valor é maior
}

/*
 * FUNÇÃO: busca_pai
 * Propósito: Encontra o nó pai de um determinado nó na árvore
 * 
 * Funcionamento:
 * - Se o nó procurado é a própria raiz, retorna NULL (raiz não tem pai)
 * - Verifica se a raiz atual é pai do nó procurado (um dos filhos é o nó)
 * - Se não é pai direto, busca recursivamente na subárvore adequada
 */
no* busca_pai(no* raiz, no* n){
    // Caso base: nó procurado é a raiz (não tem pai)
    if(raiz == n){
        return NULL;
    }
    
    // Verifica se a raiz atual é pai do nó n
    if((raiz->esq != NULL && raiz->esq == n) || (raiz->dir != NULL && raiz->dir == n))
        return raiz;
    
    // Busca recursiva na subárvore adequada baseada no valor
    if(raiz->valor > n->valor)
        return busca_pai(raiz->esq, n);
    else
        return busca_pai(raiz->dir, n);
}

/*
 * FUNÇÃO: remove_raiz
 * Propósito: Remove um nó raiz de uma subárvore e retorna a nova raiz
 * 
 * CASOS TRATADOS:
 * 1. Nó folha: simplesmente remove retornando NULL
 * 2. Apenas filho direito: retorna o filho direito como nova raiz
 * 3. Apenas filho esquerdo: retorna o filho esquerdo como nova raiz
 * 4. Dois filhos: substitui pelo maior valor da subárvore esquerda
 * 
 * IMPORTANTE: Esta função NÃO faz free na memória - isso é feito posteriormente
 */
no* remove_raiz(no* r){
    if(r == NULL) return NULL;
    
    // Caso 1: Nó folha (sem filhos)
    if(r->esq == NULL && r->dir == NULL){
        return NULL;  // Simplesmente remove o nó
    }
    
    // Caso 2: Apenas filho direito
    if(r->esq == NULL){
        return r->dir;  // Filho direito se torna a nova raiz
    }
    
    // Caso 3: Apenas filho esquerdo
    if(r->dir == NULL){
        return r->esq;  // Filho esquerdo se torna a nova raiz
    }
    
    // Caso 4: Dois filhos - Estratégia: usar o maior valor da subárvore esquerda
    no* p = r;          // Ponteiro para acompanhar o pai do nó substituto
    no* q = r->esq;     // Começa na subárvore esquerda

    // Encontra o maior valor da subárvore esquerda (nó mais à direita)
    while(q->dir != NULL){
        p = q;
        q = q->dir;
    }

    // Reorganização dos ponteiros:
    // Se q não é filho direto de r, precisa ajustar os ponteiros
    if(p != r){
        p->dir = q->esq;    // Conecta o pai de q ao filho esquerdo de q
        q->esq = r->esq;    // q herda toda a subárvore esquerda de r
    }
    // Se q é filho direto de r, não precisa ajustar q->esq (já está correto)
    
    q->dir = r->dir;  // q herda a subárvore direita de r
    
    return q;  // q é o novo nó raiz da subárvore
}

/*
 * FUNÇÃO: remover_no
 * Propósito: Remove um nó com valor específico da árvore
 * 
 * Funcionamento:
 * 1. Busca o nó a ser removido
 * 2. Encontra o pai do nó (se existir)
 * 3. Chama remove_raiz para o nó e atualiza o ponteiro do pai ou da raiz
 * 4. Retorna o nó removido (para posterior free)
 */
no* remover_no(no** raiz, int valor){
    // Busca o nó a ser removido
    no* n = busca(*raiz, valor);
    
    if(n != NULL){
        // Encontra o pai do nó (NULL se n é a raiz)
        no* pai = busca_pai(*raiz, n);
        
        if (pai != NULL) { 
            // Caso: nó tem pai (não é raiz)
            if (pai->dir == n) 
                pai->dir = remove_raiz(n);  // Atualiza ponteiro direito do pai
            else 
                pai->esq = remove_raiz(n);  // Atualiza ponteiro esquerdo do pai

        } else { 
            // Caso: nó é a raiz da árvore
            *raiz = remove_raiz(n);  // Atualiza a raiz global
        }
    }
    return n;  // Retorna o nó removido (ou NULL se não encontrado)
}

/*
 * FUNÇÃO: func_remov
 * Propósito: Interface para remoção de nó com entrada do usuário
 * 
 * Funcionamento:
 * - Recebe valor a ser removido
 * - Chama remover_no para executar a remoção
 * - Verifica se nó foi encontrado
 * - Faz free na memória do nó removido
 * - Atualiza raiz se necessário (quando raiz é removida)
 */
void func_remov(no** raiz){
    printf("Digite o número a ser removido: ");
    int valor_remover;
    scanf("%d", &valor_remover);
    
    // Remove o nó e obtém referência para ele
    no* status_remover = remover_no(raiz, valor_remover);
    
    if(status_remover == NULL){
        printf("nó não encontrado");
    }else{
        printf("Valor %d removido", status_remover->valor);
        
        // Verifica se o nó removido era a raiz para atualizar ponteiro
        if(status_remover == *raiz){
            *raiz = NULL;
        }
        
        // Libera a memória do nó removido
        free(status_remover);
    }
}

/*
 * FUNÇÕES DE PERCURSO EM ÁRVORE
 * 
 * Pré-ordem: Raiz -> Esquerda -> Direita
 * Em-ordem: Esquerda -> Raiz -> Direita (valores em ordem crescente)
 * Pós-ordem: Esquerda -> Direita -> Raiz
 */

// Função auxiliar para imprimir valor de um nó
void imprimi(no* n){
    printf("%d ", n->valor);
}

// Pré-ordem: visita raiz primeiro, depois subárvores
void pre_ordem(no* raiz){
    if(raiz != NULL){
        imprimi(raiz);  // Processa raiz
        
        if(raiz->esq != NULL)
            pre_ordem(raiz->esq);  // Percorre esquerda
        
        if(raiz->dir != NULL)
            pre_ordem(raiz->dir);  // Percorre direita
    } else{
        printf("raiz nula");
    }
}

// Em-ordem: produz os valores em ordem crescente
void em_ordem(no* raiz){
    if(raiz != NULL){
        if(raiz->esq != NULL)
            em_ordem(raiz->esq);  // Percorre esquerda primeiro

        imprimi(raiz);  // Processa raiz (no meio)

        if(raiz->dir != NULL)
            em_ordem(raiz->dir);  // Percorre direita depois
    }
}

// Pós-ordem: visita folhas primeiro, raiz por último
void pos_ordem(no* raiz){
    if(raiz != NULL){
        if(raiz->esq != NULL)
            pos_ordem(raiz->esq);  // Percorre esquerda

        if(raiz->dir != NULL)
            pos_ordem(raiz->dir);  // Percorre direita

        imprimi(raiz);  // Processa raiz por último
    }
}

/*
 * FUNÇÃO: time_quest
 * Propósito: Pausa a execução e aguarda entrada do usuário
 * Utilizada para dar tempo do usuário ver resultados antes de limpar a tela
 */
void time_quest(){
    printf("\nPressione Enter para prosseguir...");
    getchar(); // Limpa o buffer do scanf anterior
    getchar(); // Aguarda Enter do usuário
}

/*
 * FUNÇÃO MAIN
 * Propósito: Menu interativo para manipulação da árvore binária
 * 
 * Funcionalidades:
 * 1. Inserir nó
 * 2. Percursos: pré-ordem, em-ordem, pós-ordem
 * 3. Buscar valor
 * 4. Remover nó
 * 5. Sair
 */
int main(){
    no* raiz = NULL;      // Raiz da árvore (inicialmente vazia)
    bool loop = true;     // Controle do loop principal
    int choice = 0;       // Opção do menu selecionada

    while(loop){
        switch (choice)
        {
        case 0:
            // Menu principal - \033c limpa o terminal
            printf("\033c\nMenu\n1. Inserir\n2. Pre-Ordem\n3. Em Ordem\n4. Pos-Ordem\n5. Buscar\n6. Remoção\n7. Sair\n");
            scanf("%d", &choice);
            break;
        
        case 1:
            novo_no(&raiz);    // Inserir novo nó
            choice = 0;
            time_quest();
            break;
        
        case 2:
            pre_ordem(raiz);   // Percurso pré-ordem
            choice = 0;
            time_quest();
            break;

        case 3:
            em_ordem(raiz);    // Percurso em-ordem (ordenado)
            choice = 0;
            time_quest();
            break;
        
        case 4:
            pos_ordem(raiz);   // Percurso pós-ordem
            choice = 0;
            time_quest();
            break;

        case 5:{
            // Busca de valor na árvore
            int valor_busca;
            no* result;
            printf("\nDigite o valor a ser procurado: ");
            scanf("%d", &valor_busca);
            result = busca(raiz, valor_busca);
            if(result == NULL)
                printf("Valor não encontrado");
            else
                printf("Valor %d encontrado", result->valor);
            choice = 0;
            time_quest();
            break;
        }

        case 6:
            func_remov(&raiz);  // Remoção de nó
            choice = 0;
            time_quest();
            break;

        default:
            loop = false;  // Sai do programa
            break;
        }
    }

    return 0;
}
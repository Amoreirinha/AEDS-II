#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define tam 10  // Define o tamanho máximo da heap - número máximo de elementos que podemos armazenar

// Estrutura da heap - representa uma árvore binária completa usando um array
typedef struct h{
    int size;        // Número atual de elementos na heap - controla quantos elementos estão atualmente armazenados
    int tree[tam];   // Array que armazena os elementos da heap - a "árvore" é representada como um array onde:
                     // - Índice 0: raiz da árvore
                     // - Para um nó no índice i: 
                     //   * Pai: (i-1)/2
                     //   * Filho esquerdo: 2*i + 1
                     //   * Filho direito: 2*i + 2
} heap;

// Encontra o índice do nó pai no array
// Em uma heap representada como array, a relação pai-filho é matemática:
int find_parent(int i){
    int father = (i-1)/2;  // Fórmula matemática para encontrar o pai de um nó no índice i
    return father;          // Exemplo: para i=3 → pai = (3-1)/2 = 1
}                           // para i=4 → pai = (4-1)/2 = 1 (divisão inteira)

// Troca dois elementos na heap - função utilitária para reorganizar a heap
void make_swap(heap *heap, int i, int k){
    int temp = heap->tree[i];        // Guarda o valor da posição i temporariamente
    heap->tree[i] = heap->tree[k];   // Move o valor de k para i
    heap->tree[k] =  temp;           // Move o valor original de i para k
    return;                          // Após esta função, os elementos nas posições i e k estão trocados
}

// Insere um novo elemento na heap mantendo a propriedade de min-heap
// Em uma min-heap, o pai é sempre menor ou igual aos filhos
void insere (heap *heap, int k){
    // PASSO 1: Verificação de capacidade
    if (heap->size == tam){
        printf("\n\nOverflow\n\n");  // Se a heap está cheia, não podemos inserir
        return;                      // Sai da função sem fazer nada
    }

    // PASSO 2: Adiciona o novo elemento no final da heap
    heap->size++;                   // Aumenta o contador de elementos
    int i = heap->size -1;          // i recebe o índice do último elemento (novo elemento)
    heap->tree[i] = k;              // Coloca o novo valor na última posição

    // PASSO 3: Corrige a heap subindo (Heapify Up/Bubble Up)
    // Este loop garante que a propriedade da min-heap seja mantida
    // Propriedade: todo pai deve ser menor ou igual aos filhos
    while (i != 0 && heap->tree[find_parent(i)] > heap->tree[i]){
        // Se não estamos na raiz E o pai é maior que o filho atual
        // Isso viola a propriedade da min-heap, então precisamos corrigir
        
        make_swap(heap, i, find_parent(i));  // Troca o filho com o pai
        i = find_parent(i);                   // Atualiza a posição atual para a do pai
                                              // Continua verificando para cima
    }
    // Ao sair do loop, a propriedade da min-heap está restaurada
}

// Código comentado alternativo - mostra outra forma de fazer a inserção
/*
void insere (heap *heap, int k){
    if (heap->size == tam){
        printf("\n\nOverflow\n\n");
        return;
    }

    heap->size++;
    int i = heap->size -1;
    heap->tree[i] = k;

    while (i != 0 && heap->tree[parent(i)] > heap->tree[i]){
        swap(&heap->tree[i], &heap->tree[parent(i)]);
        i = parent(i);
    }
}
*/

// Calcula o índice do filho esquerdo no array
int left(int i){
    return (2*i + 1);  // Fórmula padrão: filho esquerdo do nó i está em 2*i + 1
}                      // Exemplo: para i=0 → filho esquerdo = 2*0 + 1 = 1
                       // para i=1 → filho esquerdo = 2*1 + 1 = 3

// Calcula o índice do filho direito no array
int right(int i){
    return (2*i + 2);  // Fórmula padrão: filho direito do nó i está em 2*i + 2
}                      // Exemplo: para i=0 → filho direito = 2*0 + 2 = 2
                       // para i=1 → filho direito = 2*1 + 2 = 4

// Função CRÍTICA: Reorganiza a heap a partir do nó i (Heapify Down/Bubble Down)
// Usada quando removemos um elemento ou quando a propriedade da heap é violada
void MinHeapify(heap *heap, int i){
    int l = left(i);    // Índice do filho esquerdo do nó i
    int r = right(i);   // Índice do filho direito do nó i
    int smallest = i;   // Inicialmente assume que o nó atual (i) é o menor

    // PASSO 1: Encontra o menor entre o nó atual e seus filhos
    // Verifica se o filho esquerdo existe E se é menor que o nó atual
    if(l < heap->size && heap->tree[l] < heap->tree[i])
        smallest = l;   // Se sim, o filho esquerdo é o menor até agora
    
    // Verifica se o filho direito existe E se é menor que o menor encontrado até agora
    if (r < heap->size && heap->tree[r] < heap->tree[smallest])
        smallest = r;   // Se sim, o filho direito é o menor
    
    // PASSO 2: Se o menor não é o nó atual, precisamos fazer ajustes
    if(smallest != i){
        // Troca o nó atual com o menor dos filhos
        make_swap(heap, i, smallest);
        // Chama recursivamente para o nó que acabou de descer
        // Isso garante que a propriedade da heap seja mantida em toda a subárvore
        MinHeapify(heap, smallest);
    }
    // Se smallest == i, a propriedade da heap já está satisfeita
}

// Remove e retorna o menor elemento (raiz) da heap
// Em uma min-heap, o menor elemento está sempre na raiz (índice 0)
int extractMin(heap *heap){
    // PASSO 1: Verificações de segurança
    if(heap->size <= 0)
        return INT_MAX;  // Retorna o maior inteiro possível para indicar heap vazia
    
    // PASSO 2: Caso especial - apenas um elemento na heap
    if(heap->size == 1){
        heap->size --;    // Decrementa o tamanho
        return heap->tree[0];  // Retorna o único elemento
    }

    // PASSO 3: Caso geral - múltiplos elementos
    int root = heap->tree[0];  // Salva o menor elemento (raiz)
    
    // PASSO 4: Move o último elemento para a raiz
    // Esta é a chave da operação: substituímos a raiz pelo último elemento
    heap->tree[0] = heap->tree[heap->size - 1];
    heap->size --;  // Reduz o tamanho (remove o último elemento)
    
    // PASSO 5: Reorganiza a heap a partir da raiz
    // O último elemento agora está na raiz, mas provavelmente viola a propriedade da heap
    // MinHeapify fará esse elemento "descer" para sua posição correta
    MinHeapify(heap, 0);

    return root;  // Retorna o menor elemento que foi removido
}

// Imprime todos os elementos da heap em ordem do array
// NOTA: Esta impressão não mostra a estrutura hierárquica da árvore
void print(heap *heap){
    // Percorre todo o array da heap do primeiro ao último elemento
    for(int i = 0; i < heap->size;i++){
        printf("\n%d\n", heap->tree[i]);  // Imprime um elemento por linha
    }
    // Exemplo de saída para heap [1, 3, 8, 5]:
    // 1
    // 3
    // 8
    // 5
}

// Função principal com menu interativo para testar a heap
int main(){
    heap heap;
    heap.size = 0;  // Inicializa a heap como vazia - crucial para o funcionamento correto

    int choice = 0;   // Controla a opção do menu selecionada
    bool loop = true; // Controla o loop principal do programa

    // Loop principal - mantém o programa executando até o usuário sair
    while(loop){
        switch (choice)
        {
        case 0:
            // Menu principal - apresenta as opções ao usuário
            printf("\nMenu\n1. Insert\n2.Remove\n3. Print\n4. Exit");
            scanf("%d", &choice);  // Lê a escolha do usuário
            break;
        
        case 1:{
            // Opção 1: Inserir elemento na heap
            int temp;
            printf("\n\nType a number for insert: ");
            scanf("%d", &temp);     // Lê o número a ser inserido
            insere(&heap, temp);    // Chama a função de inserção
            choice = 0;             // Volta para o menu principal
            break;
            }
        
        case 2:{
            // Opção 2: Remover o menor elemento da heap
            int removed = extractMin(&heap);  // Remove e recebe o menor elemento
            if(removed == INT_MAX){
                // Se retornou INT_MAX, significa que a heap está vazia
                printf("\n\nEmpty Tree\n\n");
            } else {
                // Mostra qual número foi removido
                printf("\n\n Number %d removed\n\n", removed);
            }
            choice = 0;  // Volta para o menu principal
            break;
            }
        
        case 3:
            // Opção 3: Imprimir todos os elementos da heap
            print(&heap);   // Chama a função de impressão
            choice = 0;     // Volta para o menu principal
            break;

        default:
            // Qualquer outra opção (como 4) sai do programa
            loop = false;  // Quebra o loop while, terminando o programa
            break;
        }
    }
    return 0;  // Fim do programa
}
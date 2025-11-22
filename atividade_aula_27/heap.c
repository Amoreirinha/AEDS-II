#include <stdio.h> 
#include <stdlib.h> 
#include "heap.h"

struct Heap* heap_inicializa(int max) {
    struct Heap* heap = (struct Heap*)malloc(sizeof(struct Heap));
    heap->max = max;
    heap->pos = 0;
    heap->prioridade = (int *)malloc(max * sizeof(int));
    return heap;
}

void heap_insere(struct Heap* heap, int prioridade) {
    if (heap_cheia(heap)) {
        printf("Heap CHEIO!\n"); 
        return;
    }
    
    heap->prioridade[heap->pos] = prioridade;
    corrige_acima(heap, heap->pos);
    heap->pos++;
}

void troca(int a, int b, int* v) {
    int f = v[a];
    v[a] = v[b];
    v[b] = f;
}

void corrige_acima(struct Heap* heap, int pos) {
    int pai;
    while (pos > 0) {
        pai = (pos - 1) / 2;
        if (heap->prioridade[pai] < heap->prioridade[pos]) {
            troca(pos, pai, heap->prioridade);
        } else { 
            break;
        }
        pos = pai;
    }
}

int heap_remove(struct Heap* heap) {
    if (heap_vazia(heap)) {
        printf("Heap VAZIO!");
        return -1;
    }
    
    int topo = heap->prioridade[0];
    heap->prioridade[0] = heap->prioridade[heap->pos - 1];
    heap->pos--;
    corrige_abaixo(heap->prioridade, 0, heap->pos);
    return topo;
}

void corrige_abaixo(int *prios, int atual, int tam) {
    int pai = atual;
    int filho_esq, filho_dir, filho;
    
    while (2 * pai + 1 < tam) {
        filho_esq = 2 * pai + 1;
        filho_dir = 2 * pai + 2;
        
        if (filho_dir >= tam) {
            filho_dir = filho_esq;
        }
        
        if (prios[filho_esq] > prios[filho_dir]) {
            filho = filho_esq;
        } else {
            filho = filho_dir;
        }
        
        if (prios[pai] < prios[filho]) {
            troca(pai, filho, prios);
        } else {
            break;
        }
        pai = filho;
    }
}

int heap_vazia(struct Heap* heap) {
    return (heap == NULL || heap->pos == 0);
}

int heap_cheia(struct Heap* heap) {
    return (heap != NULL && heap->pos >= heap->max);
}

void heap_libera(struct Heap* heap) {
    if (heap != NULL) {
        free(heap->prioridade);
        free(heap);
    }
}

void heap_imprime(struct Heap* heap) {
    if (heap_vazia(heap)) {
        printf("Heap vazia!\n");
        return;
    }
    
    printf("Heap (max=%d, pos=%d): [", heap->max, heap->pos);
    for (int i = 0; i < heap->pos; i++) {
        printf("%d", heap->prioridade[i]);
        if (i < heap->pos - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    
    int nivel = 0;
    int elementos_nivel = 1;
    int contador = 0;
    
    for (int i = 0; i < heap->pos; i++) {
        printf("%d ", heap->prioridade[i]);
        contador++;
        
        if (contador == elementos_nivel) {
            printf("\n");
            nivel++;
            elementos_nivel *= 2;
            contador = 0;
        }
    }
    printf("\n");
}

int main() {
    printf("=== TESTE DA MAX-HEAP ===\n\n");
    
    struct Heap* heap = heap_inicializa(10);
    
    printf("1. Testando funções ehVazia e ehCheia:\n");
    printf("   Heap vazia? %s\n", heap_vazia(heap) ? "SIM" : "NÃO");
    printf("   Heap cheia? %s\n\n", heap_cheia(heap) ? "SIM" : "NÃO");
    
    printf("2. Inserindo elementos na heap:\n");
    int elementos[] = {10, 20, 15, 30, 5, 25, 35, 40, 8, 12};
    int num_elementos = 10;
    
    for (int i = 0; i < num_elementos; i++) {
        printf("   Inserindo: %d\n", elementos[i]);
        heap_insere(heap, elementos[i]);
        heap_imprime(heap);
        printf("   Heap cheia? %s\n\n", heap_cheia(heap) ? "SIM" : "NÃO");
    }
    
    printf("3. Tentativa de inserir em heap cheia:\n");
    heap_insere(heap, 100);
    printf("\n");
    
    printf("4. Removendo elementos por ordem de prioridade (max-heap):\n");
    while (!heap_vazia(heap)) {
        int removido = heap_remove(heap);
        printf("   Removido: %d (maior prioridade)\n", removido);
        heap_imprime(heap);
        printf("   Heap vazia? %s\n\n", heap_vazia(heap) ? "SIM" : "NÃO");
    }
    
    printf("5. Tentativa de remover de heap vazia:\n");
    int resultado = heap_remove(heap);
    printf("   Resultado: %d\n", resultado);
    
    printf("\n6. Teste de verificação da max-heap:\n");
    
    heap_libera(heap);
    heap = heap_inicializa(8);
    
    int teste[] = {5, 10, 3, 8, 15, 1, 20, 6};
    for (int i = 0; i < 8; i++) {
        heap_insere(heap, teste[i]);
    }
    
    heap_imprime(heap);
    
    printf("   Maior elemento deve estar no topo: %s\n", 
           heap->prioridade[0] == 20 ? "CORRETO" : "ERRO");
    
    printf("   Ordem de remoção (deve ser decrescente): ");
    int anterior = 1000;
    int correto = 1;
    
    while (!heap_vazia(heap)) {
        int atual = heap_remove(heap);
        printf("%d ", atual);
        
        if (atual > anterior) {
            correto = 0;
        }
        anterior = atual;
    }
    
    printf("\n   Ordem correta? %s\n", correto ? "SIM" : "NÃO");
    
    heap_libera(heap);
    
    printf("\n=== FIM DO TESTE ===\n");
    return 0;
}
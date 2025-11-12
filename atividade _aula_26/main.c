#include "heap.h"

// Funções básicas da fila de prioridade
PriorityQueue* create_priority_queue(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (pq == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória para PriorityQueue\n");
        exit(EXIT_FAILURE);
    }
    
    pq->players = (Player*)malloc(capacity * sizeof(Player));
    if (pq->players == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória para players\n");
        free(pq);
        exit(EXIT_FAILURE);
    }
    
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void free_priority_queue(PriorityQueue* pq) {
    if (pq != NULL) {
        free(pq->players);
        free(pq);
    }
}

void swap_players(Player* a, Player* b) {
    Player temp = *a;
    *a = *b;
    *b = temp;
}

// Funções do Heap Binário
BinaryHeap* create_binary_heap(int capacity) {
    BinaryHeap* heap = (BinaryHeap*)malloc(sizeof(BinaryHeap));
    if (heap == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória para BinaryHeap\n");
        exit(EXIT_FAILURE);
    }
    
    heap->pq = *create_priority_queue(capacity);
    return heap;
}

void free_binary_heap(BinaryHeap* heap) {
    if (heap != NULL) {
        free_priority_queue(&heap->pq);
        free(heap);
    }
}

void heapify_up(BinaryHeap* heap, int index) {
    if (index == 0) return;
    
    int parent = (index - 1) / 2;
    if (heap->pq.players[index].age > heap->pq.players[parent].age) {
        swap_players(&heap->pq.players[index], &heap->pq.players[parent]);
        heapify_up(heap, parent);
    }
}

void heapify_down(BinaryHeap* heap, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;
    
    if (left < heap->pq.size && heap->pq.players[left].age > heap->pq.players[largest].age) {
        largest = left;
    }
    
    if (right < heap->pq.size && heap->pq.players[right].age > heap->pq.players[largest].age) {
        largest = right;
    }
    
    if (largest != index) {
        swap_players(&heap->pq.players[index], &heap->pq.players[largest]);
        heapify_down(heap, largest);
    }
}

void binary_heap_insert(BinaryHeap* heap, Player player) {
    if (heap->pq.size >= heap->pq.capacity) {
        fprintf(stderr, "Erro: Heap está cheio\n");
        return;
    }
    
    heap->pq.players[heap->pq.size] = player;
    heapify_up(heap, heap->pq.size);
    heap->pq.size++;
}

Player binary_heap_remove(BinaryHeap* heap) {
    if (heap->pq.size == 0) {
        Player empty = {"", -1};
        fprintf(stderr, "Aviso: Tentativa de remover de heap vazio\n");
        return empty;
    }
    
    Player max_player = heap->pq.players[0];
    heap->pq.players[0] = heap->pq.players[heap->pq.size - 1];
    heap->pq.size--;
    
    if (heap->pq.size > 0) {
        heapify_down(heap, 0);
    }
    
    return max_player;
}

int binary_heap_is_empty(BinaryHeap* heap) {
    return heap->pq.size == 0;
}

int binary_heap_size(BinaryHeap* heap) {
    return heap->pq.size;
}

Player binary_heap_peek(BinaryHeap* heap) {
    if (heap->pq.size == 0) {
        Player empty = {"", -1};
        return empty;
    }
    return heap->pq.players[0];
}

// Funções de utilidade
void print_heap(BinaryHeap* heap) {
    printf("Heap (size: %d, capacity: %d):\n", heap->pq.size, heap->pq.capacity);
    for (int i = 0; i < heap->pq.size; i++) {
        printf("  [%d] %s (idade: %d)\n", i, heap->pq.players[i].name, heap->pq.players[i].age);
    }
    
    // Imprimir representação em árvore (simplificada)
    if (heap->pq.size > 0) {
        printf("\nRepresentação em árvore:\n");
        printf("Raiz: %s (idade: %d)\n", heap->pq.players[0].name, heap->pq.players[0].age);
        
        for (int i = 0; i < heap->pq.size; i++) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            
            if (left < heap->pq.size) {
                printf("  Filho esquerdo de [%d]: %s (idade: %d)\n", 
                       i, heap->pq.players[left].name, heap->pq.players[left].age);
            }
            if (right < heap->pq.size) {
                printf("  Filho direito de [%d]: %s (idade: %d)\n", 
                       i, heap->pq.players[right].name, heap->pq.players[right].age);
            }
        }
    }
    printf("\n");
}

int is_max_heap(BinaryHeap* heap) {
    for (int i = 0; i < heap->pq.size; i++) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < heap->pq.size && heap->pq.players[i].age < heap->pq.players[left].age) {
            return 0;
        }
        if (right < heap->pq.size && heap->pq.players[i].age < heap->pq.players[right].age) {
            return 0;
        }
    }
    return 1;
}
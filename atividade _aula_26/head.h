#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME_LENGTH 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    int age;
} Player;

typedef struct {
    Player* players;
    int size;
    int capacity;
} PriorityQueue;

typedef struct {
    PriorityQueue pq;
} BinaryHeap;

// Funções básicas da fila de prioridade
PriorityQueue* create_priority_queue(int capacity);
void free_priority_queue(PriorityQueue* pq);
void swap_players(Player* a, Player* b);

// Funções do Heap Binário
BinaryHeap* create_binary_heap(int capacity);
void free_binary_heap(BinaryHeap* heap);
void heapify_up(BinaryHeap* heap, int index);
void heapify_down(BinaryHeap* heap, int index);
void binary_heap_insert(BinaryHeap* heap, Player player);
Player binary_heap_remove(BinaryHeap* heap);
int binary_heap_is_empty(BinaryHeap* heap);
int binary_heap_size(BinaryHeap* heap);
Player binary_heap_peek(BinaryHeap* heap);

// Funções de utilidade
void print_heap(BinaryHeap* heap);
int is_max_heap(BinaryHeap* heap);

#endif // HEAP_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define tam 10

typedef struct h{
    int size;
    int tree[tam];
} heap;

int find_parent(int i){
    int father = (i-1)/2;
    return father;
}

void make_swap(heap *heap, int i, int k){
    int temp = heap->tree[i];
    heap->tree[i] = heap->tree[k];
    heap->tree[k] =  temp;
    return;
}

void insere (heap *heap, int k){
    if (heap->size == tam){
        printf("\n\nOverflow\n\n");
        return;
    }

    heap->size++;
    int i = heap->size -1;
    heap->tree[i] = k;

    while (i != 0 && heap->tree[find_parent(i)] > heap->tree[i]){
        make_swap(heap, i, find_parent(i));
        i = find_parent(i);
    }
}

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

int left(int i){
    return (2*i + 1);
}

int right(int i){
    return (2*i + 2);
}

void MinHeapify(heap *heap, int i){
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if(l < heap->size && heap->tree[l] < heap->tree[i])
        smallest = l;
    if (r < heap->size && heap->tree[r] < heap->tree[smallest])
        smallest = r;
    if(smallest != i){
        make_swap(heap, i, smallest);
        MinHeapify(heap, smallest);
    }
}

int extractMin(heap *heap){
    if(heap->size <= 0)
        return INT_MAX;
    if(heap->size == 1){
        heap->size --;
        return heap->tree[0];
    }

    int root = heap->tree[0];
    heap->tree[0] = heap->tree[heap->size - 1];
    heap->size --;
    MinHeapify(heap, 0);

    return root;
}

void print(heap *heap){
    for(int i = 0; i < heap->size;i++){
        printf("\n%d\n", heap->tree[i]);
    }
}

int main(){
    heap heap;
    heap.size = 0;

    int choice = 0;
    bool loop = true;

    while(loop){
        switch (choice)
        {
        case 0:
            printf("\nMenu\n1. Insert\n2.Remove\n3. Print\n4. Exit");
            scanf("%d", &choice);

            break;
        
        case 1:{
            int temp;
            printf("\n\nType a number for insert: ");
            scanf("%d", &temp);
            insere(&heap, temp);
            choice = 0;
            break;
            }
        
        case 2:{
            int removed = extractMin(&heap);
            if(removed == INT_MAX){
                printf("\n\nEmpty Tree\n\n");
            } else {
                printf("\n\n Number %d removed\n\n", removed);
            }
            choice = 0;
            break;
            }
        
        case 3:
            print(&heap);
            choice = 0;
            break;

        default:
            loop = false;
            break;
        }
    }
    return 0;
}
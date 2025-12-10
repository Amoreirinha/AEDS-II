#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Função para Printar um vetor
void print_array(int array[], int tam){
    printf("\n\n");
    for(int i = 0; i < tam; i++){
        printf("%d\n", array[i]);
    }
    printf("\n\n");
}

// Função swap utilizada por bubble sort e quicky sort
void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

/******************************************************************************
 * BUBBLE SORT
 * 
 * FUNCIONAMENTO:
 * O Bubble Sort é um algoritmo de ordenação simples que percorre repetidamente
 * o vetor, comparando elementos adjacentes e trocando-os se estiverem na
 * ordem errada. A cada passagem completa, o maior elemento "flutua" para
 * sua posição correta no final do vetor, como uma bolha subindo à superfície.
 * 
 * LÓGICA:
 * 1. Para cada elemento i do vetor (do primeiro ao penúltimo)
 * 2. Compare cada par de elementos adjacentes (j e j+1)
 * 3. Se estiverem na ordem errada (array[j] > array[j+1]), troque-os
 * 4. Repita até que nenhuma troca seja necessária em uma passagem completa
 * 
 * COMPLEXIDADE:
 * - Melhor caso (vetor já ordenado): O(n) - com flag de otimização
 * - Caso médio: O(n²)
 * - Pior caso (vetor inversamente ordenado): O(n²)
 * - Complexidade de espaço: O(1) - ordenação in-place
 ******************************************************************************/
void bubble_sort(int array[], int tam){
    bool swapped = false;
    for(int i = 0; i < tam -1; i ++){
        swapped = false;
        for(int j = 0; j < tam - i -1; j++){
            if(array[j] > array[j+1]){
                swap(&array[j], &array[j+1]);
                swapped = true;
            }
        }
        if(!swapped) break;
    }
}

// Função Merge para o Merge Sort
void merge(int *array, int posi_inicio, int meio, int posi_fim){
    int *array_temp, array_p1, array_p2, tamanho, fim1, fim2;
    tamanho = posi_fim - posi_inicio + 1; //calculo do tamanho total das duas subdivisões
    fim1 = 0; //flag de fim da subdivisão 1
    fim2 = 0; //flag de fim da subdivisão 2
    array_p1 = posi_inicio; // inicio da subdivisão 1
    array_p2 = meio +1; // inicio da subdivisão 2
    array_temp = malloc(tamanho *sizeof(int)); //criação de um vetor temporário para a união entre as subdivisões do vetor inicial
    if(array_temp != NULL){
        // loop para preencher vetor temporário
        for(int i = 0; i < tamanho; i++){
            //verifica se as subdivisões não estão já no final. Final delas é quando são diferentes de 0.
            if(fim1 == 0 && fim2 == 0){ // pode-se usar também (!fim1 && !fim2), ambos são iguais.
                //faz a comparação de qual é o maior entre os valores das subdiviões e já ordena no vetor temporário
                if(array[array_p1] < array[array_p2]){
                    array_temp[i] = array[array_p1];
                    array_p1 ++;
                    //este campo poderia ser substituído por array_temp[i] =  array[array_p1 ++], ambos são iguais.
                } else {
                    array_temp[i] = array[array_p2];
                    array_p2 ++;
                    //este campo poderia ser substituído por array_temp[i] =  array[array_p2 ++], ambos são iguais.
                }
                // verifica se as subdivisões chegaram no fim e, em caso positivo, atualiza as flags
                if(array_p1 > meio) fim1 = 1;
                if(array_p2 > posi_fim) fim2 = 1;
            } else {
                //caso uma das subdiviões esteja no final, preenche o resto do vetor com a subdivisão que ainda não atingiu o final
                if(fim1 == 0){ // pode-se usar também (!fim), ambos são iguais
                    array_temp[i] = array[array_p1];
                    array_p1 ++;
                    //este campo poderia ser substituído por array_temp[i] =  array[array_p1 ++], ambos são iguais.
                } else {
                    array_temp[i] = array[array_p2];
                    array_p2 ++;
                    //este campo poderia ser substituído por array_temp[i] =  array[array_p2 ++], ambos são iguais.
                }
            }
        }
        //atualiza os elementos do vetor inicial pelo vetor temporário ordenado
        for(int i = 0, k = posi_inicio; i < tamanho; i ++, k ++){
            array[k]=array_temp[i];
        }
    }
    // libera vetor temporário
    free(array_temp);
}

/******************************************************************************
 * MERGE SORT
 * 
 * FUNCIONAMENTO:
 * O Merge Sort é um algoritmo de ordenação baseado na técnica "Dividir para
 * Conquistar". Ele divide recursivamente o vetor em duas metades, ordena cada
 * metade separadamente e depois mescla (merge) as duas metades ordenadas em
 * um único vetor ordenado.
 * 
 * LÓGICA:
 * 1. DIVIDIR: Divide o vetor em duas metades até que cada subvetor tenha
 *    apenas um elemento (que por definição já está ordenado)
 * 2. CONQUISTAR: Ordena recursivamente cada metade
 * 3. COMBINAR: Mescla (merge) as duas metades ordenadas em um único vetor
 *    ordenado, comparando os elementos de cada metade e colocando o menor
 *    primeiro
 * 
 * COMPLEXIDADE:
 * - Melhor caso: O(n log n)
 * - Caso médio: O(n log n)
 * - Pior caso: O(n log n)
 * - Complexidade de espaço: O(n) - requer vetor auxiliar para o merge
 * 
 * OBSERVAÇÃO:
 * É um algoritmo estável (mantém a ordem relativa de elementos iguais)
 * e funciona bem com grandes conjuntos de dados, mas requer memória auxiliar.
 ******************************************************************************/
void merge_sort(int array[], int posi_inicio, int posi_fim){
    int meio;
    if(posi_inicio < posi_fim){
        meio = (int)((posi_inicio + posi_fim)/2);
        merge_sort(array, posi_inicio, meio);
        merge_sort(array, meio+1, posi_fim);
        merge(array, posi_inicio, meio, posi_fim);
    }
}

// Função Quicky Partition para o Quicky Sort
int quicky_partition(int array[], int posi_inicio, int posi_fim) {
    
    // Escolha um pivo (por padrão o último elemento do array não ordenado)
    int pivot = array[posi_fim];
    
    // Índice do menor elemento e indica a posição correta do pivô encontrada até agora
    // i é um valor sentinela do pivo representando o último elemento menor do que o pivo
    int i = posi_inicio - 1;

    // Percorre array[posi_inicio..posi_fim] e move todos os elementos menores para o lado esquerdo.
    // Elementos de posi_inicio até i são menores a cada iteração
    // Realiza os swaps entre elementos menores do que o pivo e incrementa i quando um elemento menor que o pivo é encontrado
    for (int j = posi_inicio; j <= posi_fim - 1; j++) {
        if (array[j] < pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    
    // Move o pivô para depois dos elementos menores e retorna sua posição
    swap(&array[i + 1], &array[posi_fim]);  
    return i + 1; // retorna a posição do pivo
}

/******************************************************************************
 * QUICK SORT
 * 
 * FUNCIONAMENTO:
 * O Quick Sort é um algoritmo de ordenação eficiente baseado na técnica
 * "Dividir para Conquistar". Ele escolhe um elemento como pivô e particiona
 * o vetor de forma que todos os elementos menores que o pivô fiquem à sua
 * esquerda e todos os maiores à sua direita. Em seguida, ordena recursivamente
 * as duas partições.
 * 
 * LÓGICA:
 * 1. Escolhe um elemento como pivô (geralmente o último, primeiro ou do meio)
 * 2. Particiona o vetor: rearranja os elementos de forma que:
 *    - Elementos menores que o pivô vão para a esquerda
 *    - Elementos maiores que o pivô vão para a direita
 *    - O pivô fica em sua posição final ordenada
 * 3. Ordena recursivamente as duas partições (esquerda e direita do pivô)
 * 
 * COMPLEXIDADE:
 * - Melhor caso: O(n log n) - quando o pivô divide o vetor em partes iguais
 * - Caso médio: O(n log n)
 * - Pior caso: O(n²) - quando o pivô é sempre o menor ou maior elemento
 * - Complexidade de espaço: O(log n) - devido à pilha de recursão
 * 
 * OBSERVAÇÃO:
 * É geralmente mais rápido que o Merge Sort na prática devido a constantes
 * menores, mas não é estável. O desempenho depende da escolha do pivô.
 ******************************************************************************/
void quick_sort(int array[], int posi_inicio, int posi_fim) {
    if (posi_inicio < posi_fim) {
        
        // pi é o índice retornado pela partição (posição do pivô)
        int pi = quicky_partition(array, posi_inicio, posi_fim);

        // chamadas recursivas para elementos menores
        // e para elementos maiores ou iguais
        quick_sort(array, posi_inicio, pi - 1);
        quick_sort(array, pi + 1, posi_fim);
    }
}

// Função Heapify para Heap Sort
// Transforma uma subárvore em um heap máximo
// i: índice do nó raiz da subárvore
// TAM: tamanho total do heap
void heapify(int array[], int TAM, int i){

    // Assume que o nó atual é o maior
    int maior = i;

    // Calcula índices dos filhos esquerdo e direito
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    // Verifica se filho esquerdo existe e é maior que o atual maior
    if (esquerda < TAM && array[esquerda] > array[maior])
        maior = esquerda;

    // Verifica se filho direito existe e é maior que o atual maior
    if (direita < TAM && array[direita] > array[maior])
        maior = direita;

    // Se o maior não é mais o nó raiz
    if (maior != i) {
        // Troca os valores
        swap(&array[i],&array[maior]);

        // Recursivamente ajusta a subárvore afetada
        heapify(array, TAM, maior);
    }
}

/******************************************************************************
 * HEAP SORT
 * 
 * FUNCIONAMENTO:
 * O Heap Sort é um algoritmo de ordenação baseado na estrutura de dados
 * Heap (binário). Ele transforma o vetor em um heap máximo (onde o pai é
 * sempre maior que os filhos) e então extrai repetidamente o maior elemento
 * (a raiz do heap) colocando-o no final do vetor.
 * 
 * LÓGICA:
 * FASE 1 - CONSTRUÇÃO DO HEAP MÁXIMO:
 * 1. Transforma o vetor em um heap máximo, começando pelos nós não-folha
 * 2. Para cada nó pai, garante que ele seja maior que seus filhos (heapify)
 * 
 * FASE 2 - EXTRAÇÃO DOS ELEMENTOS ORDENADOS:
 * 1. Troca o maior elemento (raiz do heap) com o último elemento do heap
 * 2. Reduz o tamanho do heap em 1 (excluindo o elemento ordenado)
 * 3. Reconstroi o heap máximo no vetor reduzido
 * 4. Repete até que todo o vetor esteja ordenado
 * 
 * COMPLEXIDADE:
 * - Melhor caso: O(n log n)
 * - Caso médio: O(n log n)
 * - Pior caso: O(n log n)
 * - Complexidade de espaço: O(1) - ordenação in-place
 * 
 * OBSERVAÇÃO:
 * É um algoritmo não estável que tem complexidade O(n log n) garantida em
 * todos os casos. É menos sensível a dados de entrada do que o Quick Sort,
 * mas geralmente tem constantes de tempo maiores na prática.
 ******************************************************************************/
void heap_sort(int array[], int TAM){

    // Fase 1: Construção do heap máximo
    // Começa dos nós não-folha (último pai) até a raiz
    for (int i = TAM / 2 - 1; i >= 0; i--)
        heapify(array, TAM, i);

    // Fase 2: Extração dos elementos ordenados
    for (int i = TAM - 1; i > 0; i--) {

        // Move a raiz (maior elemento) para o final
        swap(&array[0],&array[i]);

        // Reconstroi o heap no vetor reduzido (tamanho i)
        heapify(array, i, 0);
    }
}

// Função Principal
#define TAM 15

int main() {
    // Bubble Sort
    int array1[TAM] = {42, 17, 89, 3, 56, 21, 74, 8, 95, 33, 60, 12, 47, 29, 81};
    printf("Bubble Sort - Array original:\n");
    print_array(array1, TAM);
    bubble_sort(array1, TAM);
    printf("Bubble Sort - Array ordenado:\n");
    print_array(array1, TAM);
    
    // Merge Sort
    int array2[TAM] = {42, 17, 89, 3, 56, 21, 74, 8, 95, 33, 60, 12, 47, 29, 81};
    printf("\nMerge Sort - Array original:\n");
    print_array(array2, TAM);
    merge_sort(array2, 0, TAM - 1);
    printf("Merge Sort - Array ordenado:\n");
    print_array(array2, TAM);
    
    // Quick Sort
    int array3[TAM] = {42, 17, 89, 3, 56, 21, 74, 8, 95, 33, 60, 12, 47, 29, 81};
    printf("\nQuicky Sort - Array original:\n");
    print_array(array3, TAM);
    quick_sort(array3, 0, TAM -1);
    printf("Quicky Sort - Array ordenado:\n");
    print_array(array3, TAM);

    // Heap Sort
    int array4[TAM] = {42, 17, 89, 3, 56, 21, 74, 8, 95, 33, 60, 12, 47, 29, 81};
    printf("\nHeap Sort - Array original:\n");
    print_array(array4, TAM);
    heap_sort(array4, TAM);
    printf("Heap Sort - Array ordenado:\n");
    print_array(array4, TAM);

    return 0;
}
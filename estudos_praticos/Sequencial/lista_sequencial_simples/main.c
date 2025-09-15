#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct v{
    int key;
    int value;
} vector;

const int TAM = 10;

void fill_vector(vector* list, int tam){
    for(int i = 0; i <= tam - 1; i++){
        list[i].key = i + 1;
        list[i].value = (i + 1)*10;
    }
}

/**
 * search - Realiza uma busca sequencial em um vetor de estruturas do tipo 'vector'.
 *
 * @param list Ponteiro para o vetor de estruturas 'vector'.
 * @param value Valor a ser buscado no campo 'value' de cada elemento do vetor.
 * @param tam Tamanho do vetor.
 * @return Retorna a chave ('key') do elemento encontrado, ou -1 se não encontrar.
 *
 * Lógica:
 * 1. Inicializa a variável 'flag' com -1, indicando que o valor não foi encontrado.
 * 2. Percorre o vetor do índice 0 até tam-1.
 * 3. Para cada elemento, verifica se o campo 'value' é igual ao valor buscado.
 * 4. Se encontrar, atualiza 'flag' com o valor da chave ('key') correspondente.
 * 5. Ao final do laço, retorna 'flag', que será -1 se não encontrou ou a chave do último elemento encontrado.
 */

int search(vector* list, int value, int tam){
    int flag = -1;
    for(int i = 0; i <= tam - 1; i++){
        if (list[i].value == value){
            flag = list[i].key;
        }
    }
    return (flag);
}

 /**
 * binare_search - Realiza uma busca binária em um vetor ordenado de estruturas do tipo 'vector'.
 *
 * @param list Ponteiro para o vetor de estruturas 'vector', que deve estar ordenado pelo campo 'value'.
 * @param value Valor a ser buscado no campo 'value' de cada elemento do vetor.
 * @param tam Tamanho do vetor.
 * @return Retorna a chave ('key') do elemento encontrado, ou -1 se não encontrar.
 *
 * Lógica:
 * 1. Inicializa os índices 'low' (início) e 'high' (fim) do vetor.
 * 2. Enquanto 'low' for menor ou igual a 'high':
 *    a. Calcula o índice do meio ('mid').
 *    b. Compara o valor do elemento do meio com o valor buscado.
 *    c. Se for igual, retorna a chave ('key') do elemento encontrado.
 *    d. Se o valor do meio for menor que o buscado, ajusta 'low' para buscar na metade superior.
 *    e. Se o valor do meio for maior, ajusta 'high' para buscar na metade inferior.
 * 3. Se sair do laço sem encontrar, retorna -1 indicando que o valor não está presente.
 */

int binare_search(vector* list, int value, int tam){
    int low = 0;
    int high = tam - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (list[mid].value == value) {
            return list[mid].key;
        } else if (list[mid].value < value) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

int main(){
    vector list[TAM];
    fill_vector(&list, TAM);
    int value;

    printf("Digite o valor a ser pesquisado: ");
    scanf("%d", &value);

    int result_search = search(&list, value, TAM);

    if(result_search != -1)
        printf("\nValor encontrado na chave %d.\n", result_search);

    printf("Digite o valor a ser pesquisado: ");
    scanf("%d", &value);

    result_search = binare_search(&list, value, TAM);

    if(result_search != -1)
        printf("\nValor encontrado na chave %d.\n", result_search);

    return 0;
}
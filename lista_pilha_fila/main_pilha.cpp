#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

struct vetor_ord{
    int key;
    int value;
};

const int TAM = 10;

int insere(vetor_ord ins[], vetor_ord pilha[], int tam, int complet){
    int flag = -1;
    if (complet != tam){
        complet++;
        pilha[complet-1] = ins[0];
        flag = complet; // Retorna a nova posição onde o elemento foi inserido
    }
    return flag; // Corrige o retorno para todos os casos
}

vetor_ord *remove(vetor_ord pilha[], int tam, int complet){
    vetor_ord *flag = NULL;
    if (complet != 0){
        flag = &pilha[complet-1];
    }
    return flag; // Retorna o último elemento removido ou NULL se a pilha estiver vazia
}

int main() {
    vetor_ord pilha[TAM] = {{1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}, {6, 60}, {7, 70}, {8, 80}};
    int complet = 8; // Número de elementos na pilha
    vetor_ord ins[1]; // Elemento a ser inserido
    cout << "Digite a chave e o valor do elemento a ser inserido: ";
    cin >> ins[0].key;
    cin >> ins[0].value;
    int inserido = insere(ins, pilha, TAM, complet);
    if (inserido == -1) {
        cout << "Pilha cheia, não foi possível inserir." << endl;
    } else {
        cout << "Elemento inserido na posição: " << inserido << endl;
        complet = inserido; // Atualiza o número de elementos na pilha
    }
    vetor_ord *removido = remove(pilha, TAM, complet);
    if (removido == NULL) {
        cout << "Pilha vazia, não foi possível remover." << endl;
    } else {
        cout << "Elemento removido: " << removido << endl;
        complet--; // Atualiza o número de elementos na pilha
    }

    return 0;
}
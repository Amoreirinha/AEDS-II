#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

struct vetor_ord{
    int key;
    int value;
};

const int TAM = 10;

int buscabin(int x, vetor_ord L[], int tam) {
    int lim_inf = 0;
    int lim_sup = tam - 1;
    int meio;
    while(lim_inf <= lim_sup) {
        meio = floor((lim_inf + lim_sup) / 2);
        if(L[meio].key == x) {
            return meio; // Retorna a posição do elemento encontrado
        } else if (L[meio].key < x) {
            lim_inf = meio + 1;
        } else {
            lim_sup = meio - 1;
        }
    }
    return -1; // Retorna -1 se o elemento não for encontrado
}

int insere(vetor_ord ins[], vetor_ord L[], int tam, int complet){
    int flag = -2; // quando a lista está cheia
    if (complet < tam){
        flag = -1; // quando o elemento já existe mas tem espaço
        int pos = buscabin(ins[0].key, L, complet);
        if ( pos == -1) {
            L[complet+1] = ins[0];
            flag = complet + 1;
        }
    }
    return flag; // Retorna a posição onde o elemento foi inserido ou -1 se não foi possível inserir
}

int *remove (vetor_ord L[], int tam, int complet, int x){
    int *flag = NULL; // Inicializa o ponteiro como NULL
    if (complet != 0){
        int i =  buscabin(x, L, complet);
        if (i != -1){
            flag = &L[i].key; // Atribui o endereço do elemento encontrado
            for (int j = i; j < complet - 1; j++){
                L[j] = L[j + 1]; // Desloca os elementos para a esquerda
            }
        }
    }
    return flag; // Retorna o endereço do elemento removido ou NULL se não foi encontrado
}

int main() {
    vetor_ord L[TAM] = {{1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}, {6, 60}, {7, 70}, {8, 80}};
    int n = 8; // Número de elementos na lista
    vetor_ord inse[1];
    cout << "Digite a chave do elemento: ";
    cin >> inse[0].key;
    cout << "Digite o valor do elemento: ";
    cin >> inse[0].value;
    int inserido = insere(inse, L, TAM, n);
    if (inserido == -1) {
        cout << "Elemento já existe ." << endl;
    } else if ( inserido == -2) {
        cout << "Lista cheia, não foi possível inserir." << endl;
    } else {
        cout << "Elemento inserido na posição: " << inserido << endl;
        n = inserido; // Atualiza o número de elementos na lista
    }
    cout << "Digite a chave do elemento a ser removido: ";
    int x;
    cin >> x;
    int *removido = remove(L, TAM, n, x);
    if (removido != NULL) {
        cout << "Elemento removido: " << removido << endl;
        n--; // Atualiza o número de elementos na lista
    } else {
        cout << "Elemento não encontrado." << endl;
    }

    return 0;
}
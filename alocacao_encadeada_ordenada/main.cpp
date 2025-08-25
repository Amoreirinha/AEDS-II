#include <iostream>
#include <cstdlib>

using namespace std;

struct no{
    int valor;
    no* prox;
};

// Função de busca na lista encadeada ordenada de nó. Retorna o ponteiro do nó que possui o valor procurado ou nullptr caso não encontre.
no* busca_enc(no* head, int valor){
    no* point = nullptr
    no* ant = head;
    no* ptr = head->prox;
    while(ptr != nullptr){
        if(ptr->valor < valor){
            ant = ptr;
            ptr = ptr->prox;
        }else if(ptr->valor == valor){
            point = ptr;
            ptr = nullptr;
        }
    }
    return point;
}

int insere_enc(no* head, no* novo){
    int flag = -1;
    no* result = busca_enc(head, novo->valor);
    if(result == nullptr){
        
    }

}

int main(){
    no nohead, no1, no2, no3, nonovo;

    nohead.prox = &no1;
    no1.valor = 10;
    no1.prox = &no2;
    no2.valor = 20;
    no2.prox = &no3;
    no3.valor = 30;
    no3.prox = nullptr;

    no* resultado = busca_enc(&nohead, 30);
    if(resultado != nullptr){
        cout << "Valor encontrado: " << resultado->valor << endl;
    }else{
        cout << "Valor não encontrado" << endl;
    }

    cin >> nonovo.valor;
    int resultado_insere = insere_enc(&nohead, &nonovo);

    return 0;

}
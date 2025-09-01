#include <iostream>
#include <cstdlib>

using namespace std;

// Função para limpar a tela do terminal usando códigos ANSI
void limpar_tela()
{
    cout << "\033[2J\033[H";
}

// Estrutura do nó da pilha (lista encadeada)
typedef struct n
{
    int valor; // Valor armazenado no nó
    n *prox;   // Ponteiro para o próximo nó
} no;

// Estrutura para retornar dois ponteiros ao remover da pilha:
// - removed: ponteiro para o nó removido
// - newtop: ponteiro para o novo topo da pilha após remoção
typedef struct nduplo{
    no *removed; // Nó removido da pilha
    no *newtop;  // Novo topo da pilha após remoção
} multireturn;

// Função para inserir um valor no topo da pilha
no *insere_pilha(no *pi, int valor)
{
    no *novo = new no;   // Aloca novo nó
    novo->valor = valor; // Define valor
    novo->prox = pi;     // Aponta para o antigo topo
    return novo;         // Retorna novo topo
}

// Função para remover o topo da pilha
/*
 *
 * Esta função recebe um ponteiro para o topo da pilha (pi) e remove o nó do topo,
 * retornando tanto o nó removido quanto o novo topo da pilha através de uma struct multireturn.
 *
 * Passo a passo:
 * 1. Inicializa um ponteiro 'remove' como nullptr para armazenar o nó a ser removido.
 * 2. Inicializa uma variável 'ret' do tipo multireturn para armazenar os resultados.
 * 3. Verifica se o ponteiro 'pi' não é nulo (ou seja, se a pilha não está vazia).
 *    - Se não estiver vazia:
 *      a. Atribui o topo da pilha ('pi') ao ponteiro 'remove', guardando o nó a ser removido.
 *      b. Atualiza 'pi' para apontar para o próximo nó da pilha ('pi->prox'), efetivamente removendo o topo.
 * 4. Atribui o nó removido ('remove') e o novo topo ('pi') aos campos correspondentes da struct 'ret'.
 * 5. Retorna a struct 'ret' contendo o nó removido e o novo topo da pilha.
 */
multireturn remove_pilha(no *pi)
{
    no *remove = nullptr;
    multireturn ret;
    if (pi != nullptr)
    {
        remove = pi;      // Guarda o nó a ser removido
        pi = pi->prox; // Atualiza topo para o próximo nó
    }
    ret.removed = remove;
    ret.newtop = pi;
    return ret; // Retorna o nó removido e o novo topo
}

int main()
{
    int choice = 0;
    bool running = true;
    // Ponteiro para o topo da pilha
    no *pilha = nullptr;

    // Loop principal do menu
    while (running)
    {
        switch (choice)
        {
        case 0:
            // Exibe menu principal
            limpar_tela();
            cout << "Menu:\n1. Imprimir pilha\n2. Inserir Valor\n3. Remover valor\n4. Exit\nEscolha uma opção: ";
            cin >> choice;
            break;
        case 1:
        {
            // Imprime a pilha
            limpar_tela();
            if (pilha == nullptr)
            {
                cout << "Pilha vazia" << endl;
            }
            else
            {
                cout << "Pilha atual: ";
                no *atual = pilha;
                while (atual != nullptr)
                {
                    cout << atual->valor << " "; // Mostra cada valor
                    atual = atual->prox;
                }
                cout << endl;
            }
            cout << "Pressione Enter para continuar...";
            cin.ignore();
            cin.get();
            choice = 0; // Volta ao menu
        }
        break;
        case 2:
        {
            // Insere valor na pilha
            limpar_tela();
            int valor_inserir;
            cout << "Digite um valor para inserir na pilha: ";
            cin >> valor_inserir;
            pilha = insere_pilha(pilha, valor_inserir);
            cout << "Valor inserido com sucesso" << endl;
            cout << "Pilha atual: ";
            no *atual = pilha;
        }
            cout << "Pressione Enter para continuar...";
            cin.ignore();
            cin.get();
            choice = 0;
            break;
        case 3:
        {
            // Remove valor do topo da pilha
            limpar_tela();
            if (pilha == nullptr)
            {
                cout << "Pilha vazia, nada a remover" << endl;
            }
            else
            {
                multireturn ret = remove_pilha(pilha);
                no *removido = ret.removed;
                pilha = ret.newtop;
                cout << "Valor removido: " << removido->valor << endl;
                delete removido; // Libera memória do nó removido
                cout << "Pressione Enter para continuar...";
                cin.ignore();
                cin.get();
                cout << "Valor removido com sucesso" << endl;
                if (pilha == nullptr)
                {
                    cout << "Pilha agora está vazia" << endl;
                }
                else
                {
                    choice = 1; // Mostra pilha atualizada
                    break;
                }
            }
        }
            cout << "Pressione Enter para continuar...";
            cin.ignore();
            cin.get();
            choice = 0;
            break;
        case 4:
            // Sai do programa
            running = false;
            break;
        }
    }

    // Libera toda a memória alocada pela pilha antes de encerrar
    cout << "Encerrando o programa. Liberando memória..." << endl;
    while (pilha != nullptr)
    {
        no *temp = pilha;
        pilha = pilha->prox;
        delete temp;
    }

    cout << "Memória liberada. Até mais!" << endl;

    return 0;
}
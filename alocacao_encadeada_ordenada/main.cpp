#include <iostream>
#include <cstdlib>

using namespace std;

struct no
{
    int valor;
    no *prox;
};

// Função de busca corrigida
no *busca_enc(no *head, int valor)
{
    no *ptr = head->prox;
    while (ptr != nullptr)
    {
        if (ptr->valor == valor)
        {
            return ptr; // Valor encontrado
        }
        else if (ptr->valor > valor)
        {
            return nullptr; // Passou da posição onde estaria
        }
        ptr = ptr->prox;
    }
    return nullptr; // Chegou ao final
}

int insere_enc(no *head, no *novo)
{
    int flag = -1;
    no *result = busca_enc(head, novo->valor);
    if (result == nullptr)
    {
        no *ant = head;
        no *ptr = head->prox;
        while (ptr != nullptr && ptr->valor < novo->valor)
        {
            ant = ptr;
            ptr = ptr->prox;
        }
        novo->prox = ant->prox;
        ant->prox = novo;
        flag = 0;
    }
    return flag;
}

// Função remove simplificada
int remove_enc(no *head, int valor)
{
    no *ant = head;
    no *ptr = head->prox;

    while (ptr != nullptr && ptr->valor < valor)
    {
        ant = ptr;
        ptr = ptr->prox;
    }

    if (ptr != nullptr && ptr->valor == valor)
    {
        ant->prox = ptr->prox;
        delete ptr;
        return 0; // Sucesso
    }
    return -1; // Não encontrado
}

int main()
{
    no nohead;
    nohead.prox = nullptr;
    bool loop = true;
    int choice = 0;

    // Cria nós dinamicamente
    int valores_iniciais[] = {10, 30, 40, 60, 80, 85, 99};
    for (int i = 0; i < sizeof(valores_iniciais) / sizeof(valores_iniciais[0]); i++)
    {
        no *novo = new no;
        novo->valor = valores_iniciais[i];
        novo->prox = nullptr;
        insere_enc(&nohead, novo);
    }

    while (loop)
    {
        switch (choice)
        {
        case 0:
            cout << "Menu:\n1. Buscar valor\n2. Inserir valor\n3. Remover valor\n4. Sair\nEscolha uma opção: ";
            cin >> choice;
            break;

        case 1:
        {
            cout << "Digite um valor a ser buscado: ";
            int valor_buscar;
            cin >> valor_buscar;
            no *resultado = busca_enc(&nohead, valor_buscar);
            if (resultado != nullptr)
            {
                cout << "Valor encontrado: " << resultado->valor << endl;
            }
            else
            {
                cout << "Valor não encontrado" << endl;
            }
            choice = 0;
            break;
        }

        case 2:
        {
            cout << "Digite um valor para inserir na lista: ";
            int valor_inserir;
            cin >> valor_inserir;

            no *nonovo = new no;
            nonovo->valor = valor_inserir;
            nonovo->prox = nullptr;

            int resultado_insere = insere_enc(&nohead, nonovo);
            if (resultado_insere == 0)
            {
                cout << "Valor inserido com sucesso" << endl;
                cout << "Lista atualizada: ";
                no *atual = nohead.prox;
                while (atual != nullptr)
                {
                    cout << atual->valor << " ";
                    atual = atual->prox;
                }
                cout << endl;
            }
            else
            {
                cout << "Valor já existe na lista" << endl;
                delete nonovo; // Libera memória se não foi inserido
            }
            choice = 0;
            break;
        }

        case 3:
        {
            cout << "Digite o valor a ser removido da lista: ";
            int valor_remover;
            cin >> valor_remover;

            int resultado_remove = remove_enc(&nohead, valor_remover);
            if (resultado_remove == 0)
            {
                cout << "Valor removido com sucesso" << endl;
                cout << "Lista atualizada: ";
                no *atual = nohead.prox;
                while (atual != nullptr)
                {
                    cout << atual->valor << " ";
                    atual = atual->prox;
                }
                cout << endl;
            }
            else
            {
                cout << "Valor não encontrado na lista" << endl;
            }
            choice = 0;
            break;
        }

        case 4:
            cout << "Saindo do programa..." << endl;
            loop = false;
            break;

        default:
            cout << "Opção inválida. Tente novamente." << endl;
            choice = 0;
            break;
        }
    }

    // Libera memória alocada
    no *atual = nohead.prox;
    while (atual != nullptr)
    {
        no *temp = atual;
        atual = atual->prox;
        delete temp;
    }

    return 0;
}
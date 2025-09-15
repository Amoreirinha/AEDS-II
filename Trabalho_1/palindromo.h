#ifndef _H_PALINDROMO
#define _H_PALINDROMO

typedef struct word
{
    char str[1];
    struct word *prox;
    struct word *ant;
} palindromo;

bool ler_linha(FILE *arquivo, palindromo **fim)
{
    int caractere;

    while ((caractere = fgetc(arquivo)) != '\n' && caractere != EOF)
    {
        if (caractere != ' ' && caractere >= 65 && (caractere <= 90 || caractere >= 97) && caractere <= 122)
        {
            palindromo *novo = (palindromo *)malloc(sizeof(palindromo));
            if (caractere > 90)
            {
                caractere -= 32;
            }
            novo->str[0] = caractere;
            novo->str[1] = '\0';
            novo->prox = NULL;
            novo->ant = *fim;
            (*fim)->prox = novo;
            *fim = novo;
        }
    }

    return true;
}

bool verifica_palindromo(palindromo *inicio, palindromo *fim)
{
    palindromo *esquerda = inicio->prox;
    palindromo *direita = fim;
    bool eh_palindromo = true;
    while (esquerda != NULL && direita != NULL && esquerda != direita && esquerda->ant != direita)
    {
        if (esquerda->str[0] != direita->str[0])
        {
            eh_palindromo = false;
            break;
        }
        esquerda = esquerda->prox;
        direita = direita->ant;
    }
    return eh_palindromo;
}

void liberar_lista(palindromo *inicio)
{
    palindromo *atual = inicio;
    while (atual != NULL)
    {
        palindromo *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}

#endif // _H_PALINDROMO
#ifndef _H_PALINDROMO
#define _H_PALINDROMO

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct word
{
    char caractere;
    struct word *prox;
    struct word *ant;
} palindromo;

char converter_acento(unsigned char c1, unsigned char c2, int *bytes_consumidos)
{
    *bytes_consumidos = 1;

    if (c1 == 0xC3)
    {
        *bytes_consumidos = 2;
        switch (c2)
        {
        case 0xA1:
        case 0xA0:
        case 0xA2:
        case 0xA3:
            return 'a';
        case 0xA9:
        case 0xA8:
        case 0xAA:
            return 'e';
        case 0xAD:
        case 0xAC:
        case 0xAE:
            return 'i';
        case 0xB3:
        case 0xB2:
        case 0xB4:
        case 0xB5:
            return 'o';
        case 0xBA:
        case 0xB9:
        case 0xBB:
            return 'u';
        case 0xA7:
            return 'c';
        case 0x81:
        case 0x80:
        case 0x82:
        case 0x83:
            return 'A';
        case 0x89:
        case 0x88:
        case 0x8A:
            return 'E';
        case 0x8D:
        case 0x8C:
        case 0x8E:
            return 'I';
        case 0x93:
        case 0x92:
        case 0x94:
        case 0x95:
            return 'O';
        case 0x9A:
        case 0x99:
        case 0x9B:
            return 'U';
        case 0x87:
            return 'C';
        }
    }

    if (isalpha(c1))
    {
        return toupper(c1);
    }

    return '\0';
}

bool ler_linha(FILE *arquivo, palindromo **fim)
{
    int byte1, byte2;

    while ((byte1 = fgetc(arquivo)) != '\n' && byte1 != EOF)
    {
        char caractere_normalizado;
        int bytes_consumidos;

        if ((byte1 & 0xE0) == 0xC0)
        {
            byte2 = fgetc(arquivo);
            if (byte2 == EOF)
                break;

            caractere_normalizado = converter_acento((unsigned char)byte1, (unsigned char)byte2, &bytes_consumidos);
        }
        else
        {
            caractere_normalizado = converter_acento((unsigned char)byte1, 0, &bytes_consumidos);
        }
        if (caractere_normalizado > 90)
        {
            caractere_normalizado -= 32;
        }

        if (caractere_normalizado != '\0')
        {
            palindromo *novo = (palindromo *)malloc(sizeof(palindromo));
            novo->caractere = caractere_normalizado;
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

    while (esquerda != NULL && direita != NULL &&
           esquerda != direita && esquerda->ant != direita)
    {
        if (esquerda->caractere != direita->caractere)
        {
            return false;
        }
        esquerda = esquerda->prox;
        direita = direita->ant;
    }
    return true;
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

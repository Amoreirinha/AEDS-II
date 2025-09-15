#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "palindromo.h"

bool ler_linha(FILE *arquivo, palindromo **fim)
{
    int caractere;

    while ((caractere = fgetc(arquivo)) != '\n' && caractere != EOF)
    {
        if (caractere != ' ')
        {
            palindromo *novo = (palindromo *)malloc(sizeof(palindromo));
            if (caractere > 90)
            {
                caractere -= 32;
            }
            if (caractere >= 224 && caractere <= 255)
            {
                // Converte caracteres acentuados para não acentuados
                switch (caractere)
                {
                case 224:
                case 225:
                case 226:
                case 227:
                case 228:
                case 229: // à á â ã ä å
                    caractere = 'A';
                    break;
                case 232:
                case 233:
                case 234:
                case 235: // è é ê ë
                    caractere = 'E';
                    break;
                case 236:
                case 237:
                case 238:
                case 239: // ì í î ï
                    caractere = 'I';
                    break;
                case 242:
                case 243:
                case 244:
                case 245:
                case 246: // ò ó ô õ ö
                    caractere = 'O';
                    break;
                case 249:
                case 250:
                case 251:
                case 252: // ù ú û ü
                    caractere = 'U';
                    break;
                case 231: // ç
                    caractere = 'C';
                    break;
                case 241: // ñ
                    caractere = 'N';
                    break;
                }
                novo->str[0] = caractere;
                novo->str[1] = '\0';
                novo->prox = NULL;
                novo->ant = *fim;
                (*fim)->prox = novo;
                *fim = novo;
                // printf("%s\n", novo->str); // tirar depois
            }
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

int main()
{
    FILE *arquivo;
    arquivo = fopen("palindromo.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return false;
    }
    palindromo palavra;
    palavra.ant = NULL;
    palavra.prox = NULL;
    palindromo *inicio = &palavra;
    palindromo *fim = &palavra;
    bool sucesso;

    while (!feof(arquivo))
    {

        sucesso = ler_linha(arquivo, &fim);

        if (!sucesso)
        {
            printf("Erro ao ler a linha do arquivo.\n");
            fclose(arquivo);
            return 1;
        }

        if (verifica_palindromo(inicio, fim))
        {
            printf("1\n");
        }
        else
        {
            printf("0\n");
        }
        liberar_lista(inicio->prox);
        inicio->prox = NULL;
        fim = inicio;
    }

    fclose(arquivo);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "palindromo.h"

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
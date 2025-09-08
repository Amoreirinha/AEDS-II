#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "palindromo.h"

int main()
{
    FILE *arquivo;

    arquivo = fopen("palindromos.txt", "r");
    
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    for (sizeof(palindromo); !feof(arquivo);)
    {
        palindromo *novo = (palindromo *)malloc(sizeof(palindromo));
        fscanf(arquivo, "%s", novo->str);
        printf("%s\n", novo->str);
        free(novo);
    }

    fclose(arquivo);
    return 0;
}
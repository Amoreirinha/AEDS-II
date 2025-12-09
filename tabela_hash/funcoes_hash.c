#include <stdio.h>
#include <string.h>
#include "funcoes_hash.h"

int chave_divisao(int chave, int Tabela_size){
    if(chave < 0)
        chave *= -1;
    
    return (int)(chave % Tabela_size);
}

int chave_multiplicacao(int chave, int Tabela_size){
    if(chave < 0)
        chave *= -1;
    double A = 0.74892903475614213;
    double val = chave * A;
    val = val - (int)val;
    return (int)(val * Tabela_size);
}

int chave_dobra(int chave, int Tabela_size){
    if(chave < 0)
        chave *= -1;
    if(chave < Tabela_size)
        return chave;
    
    int numero[10];
    int inicio = 0;
    int fim = 0;
    int div = chave;

    do{
        numero[inicio] = div % 10;
        if(numero[inicio])
            fim = inicio;    
        div = div / 10;
        inicio ++;

    }while(inicio<10);

    inicio = 0;

    while(chave > Tabela_size){
        while(fim > inicio){
            numero[inicio]=(numero[inicio]+numero[fim])%10;
            numero[fim]= 0;
            inicio ++;
            fim --;
        }
        inicio = 0;
        chave = 0;
        int fator = 1;
        while(inicio <= fim){
            chave += numero[inicio] * fator;
            fator *= 10;
            inicio ++;
        }
        inicio = 0;
    }

    return chave;
}

int valor_string(char * str){
	int i, valor = 7;
	int tam = strlen(str);
	for(i = 0; i < tam; i++){
		valor = 31 * valor + (int) str[i];
	}
	return valor;
}
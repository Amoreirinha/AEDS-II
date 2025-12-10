#include <stdio.h>
#include <string.h>
#include "funcoes_hash.h"


// função hashing chave divisão - função que determina o índice de um elemento pelo resto de sua divisão com o tamanho da tabela hash
int chave_divisao(int chave, int Tabela_size){
    // transforma negativo em positivo
    if(chave < 0)
        chave *= -1;
    
    return (int)(chave % Tabela_size);
}

// função hashing chave multiplicação - função que determina o índice de um elemento pelo resultado da multiplicação do tamanho da tabela pela parte decimal da multiplicação de um elemento por uma constante A qualquer
int chave_multiplicacao(int chave, int Tabela_size){
    // transforma negativo em positivo
    if(chave < 0)
        chave *= -1;
    double A = 0.74892903475614213; // constante a
    double val = chave * A;
    val = val - (int)val; // val recebe a parte decimal de val
    return (int)(val * Tabela_size);
}

// função hashing dobra - função que determina o índce de um elemento pelo resultado das soma de seus algarismos, menosprezando as dezenas. Esse processo é feito até que o resultado seja menor do que o tamanho da tabela.
int chave_dobra(int chave, int Tabela_size){
    // transforma negativo em positivo
    if(chave < 0)
        chave *= -1;
    // verifica se a chave/valor inicial já é menor do que o tamanho da tabela, se sim, passa ela como índice
    if(chave < Tabela_size)
        return chave;
    
    // inicialização de variáveis para passar os algorismos da chave 1 por 1 para um vetor
    int numero[10];
    int inicio = 0;
    int fim = 0;
    int div = chave;

    //loop para separar os números da chave em um vetor (esse código escreve os números da chave em ordem descrescente, exemplo: se chave = 1245, numero = {5,4,2,1})
    do{
        numero[inicio] = div % 10; // essa operação faz com que o resto da divisão seja o número da unidade da chave. Exemplo: chave = 1245, resultado = 5.
        if(numero[inicio]) // verifica se numero[inicio] != 0, se sim, atualiza o fim com o índice que possue o último valor não zero do vetor numero.
            fim = inicio;    
        div = div / 10; // elimina a unidade do valor e atualiza o número. Exemplo: div = 1245 -> div = 124
        inicio ++; // incrementa 1

    }while(inicio<10);

    inicio = 0;

    // loop que vai somar os números do vetor número pegando 1 a 1 das extremidades ao centro até que o resultado seja menor que o tamanho da tabel. Exemplo: Se numero = {5,4,2,1}, operações vão ser 5+1, 4+2 que será numero={6,6}
    while(chave > Tabela_size){
        // soma os números 1 a 1 pelas extremidades ao centro incrementando início e decrementando fim
        while(fim > inicio){
            numero[inicio]=(numero[inicio]+numero[fim])%10; // cálculo da soma dos números. só pega a parte da unidade (ignora dezena)
            numero[fim]= 0;
            inicio ++;
            fim --;
        }
        inicio = 0;
        chave = 0;
        int fator = 1;
        // escreve o número formado em numero na chave, multiplicando por um fator (que sempre aumenta nas dezenas) para ajustar as unidades, dezenas e centenas.
        while(inicio <= fim){
            chave += numero[inicio] * fator;
            fator *= 10;
            inicio ++;
        }
        inicio = 0;

        // ao fim verifica se o novo valor da chave é menor que o tamanho da tabela, se não, retorna a soma novamente.
    }

    return chave;
}

// função hashing string - função que determina o índice de um valor string.
int valor_string(char * str){
	int i, valor = 7;
	int tam = strlen(str); // strlen é uma função de C que retorna o tamanho de um vetor string
	for(i = 0; i < tam; i++){
		valor = 31 * valor + (int) str[i]; // converte cada letra da string em um número intiro e soma ele a variável valor multiplicada por uma constante.
	}
	return valor;
}
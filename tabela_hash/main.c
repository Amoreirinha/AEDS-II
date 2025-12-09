#include <stdio.h>
#include <string.h>
#include "funcoes_hash.h"
#include "tabela_hash.h"

int main(){
	hash* tabela_hash = criar_tabela(100);
	estudante * estud = criar_estudante(125, "Flavio Barbieri");
	insere_hash_end_aberto(tabela_hash, estud);
	estud = criar_estudante(1125, "Joao das Couves");
	insere_hash_end_aberto(tabela_hash, estud);
	char * a = busca_hash_end_aberto(tabela_hash, 125);
	if (a != NULL)
		printf("%s\n", a);
	else
		printf("Aluno nao encontrado.\n");

	a = busca_hash_end_aberto(tabela_hash, 1125);
	if (a != NULL)
		printf("%s\n", a);
	else
		printf("Aluno nao encontrado.");

	libera_hash(tabela_hash);
	return 0;
}
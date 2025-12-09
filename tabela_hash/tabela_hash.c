#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes_hash.h"
#include "tabela_hash.h"

hash * criar_tabela(int Tabela_size){
    hash * ha = malloc(sizeof(hash));
    if(ha != NULL){
        ha->estudantes = malloc (Tabela_size * sizeof(estudante *));
        if(ha->estudantes == NULL){
            free(ha);
            return NULL;
        }
        ha->qtd = 0;
        ha->TABELA_SIZE = Tabela_size;
        for(int i = 0; i < Tabela_size; i++){
            ha->estudantes[i]=NULL;
        }
    }
    return ha;
}

estudante * criar_estudante(int matricula, const char *nome){
    estudante * novo = malloc(sizeof(estudante));
    if(novo == NULL) return NULL;
    novo->matricula = matricula;
    strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
    novo->nome[sizeof(novo->nome) - 1] = '\0';
    return novo;
}

void libera_hash(hash *ha){
    if(ha != NULL){
        for(int i = 0; i < ha->TABELA_SIZE; i++){
            if(ha->estudantes[i] != NULL)
                free(ha->estudantes[i]);
        }
        free(ha->estudantes);
        free(ha);
    }
}

int insere_hash_sem_colisao(hash *ha, estudante * estud){
    if(ha == NULL || ha->qtd == ha->TABELA_SIZE)
        return 0;
    
    int posi = chave_divisao(estud->matricula, ha->TABELA_SIZE);
    //int posi = chave_multiplicacao(estud->matricula, ha->TABELA_SIZE);
    //int posi = chave_dobra(estud->matricula, ha->TABELA_SIZE);
    ha->estudantes[posi] = estud;
    ha->qtd ++;
    return 1;
}

char* busca_hash_sem_colisao(hash * ha, int matricula) {

    if(ha == NULL) return NULL;

	int posi = chave_divisao(matricula, ha->TABELA_SIZE);

    if(ha->estudantes[posi] == NULL) return NULL;

	return &(ha->estudantes[posi]->nome[0]);
}

int sondagem_linear(int posi, int i, int Tabela_size){
    return ((posi + i) % Tabela_size);
}

int sondagem_quadratica(int posi, int i, int Tabela_size){
    posi = posi + 5*i + 3*i*i;
    return (posi % Tabela_size);
}

int duplo_hash(int H1, int chave, int i, int TABLE_SIZE) {
	int H2 = chave_divisao(chave, TABLE_SIZE - 1) + 1;
	return ((H1 + i * H2) % TABLE_SIZE);
}

int insere_hash_end_aberto(hash * ha, estudante * estud) {
	if (ha == NULL || ha->qtd == ha->TABELA_SIZE) {
		return 0;
	}
	int posi, i;
    //pos = chave_divisao(estud->matricula, ha->TABELA_SIZE);
	//pos = chave_multiplicacao(estud->matricula, ha->TABELA_SIZE);
	posi = chave_dobra(estud->matricula, ha->TABELA_SIZE);
	for (i = 0; i < ha->TABELA_SIZE; i++) {
		posi = duplo_hash(posi, estud->matricula, i, ha->TABELA_SIZE);
        //posi = sondagem_linear(posi, i, ha->TABELA_SIZE);
        //posi = sondagem_quadratica(posi, i, ha->TABELA_SIZE);
		if (ha->estudantes[posi] == NULL) {
			ha->estudantes[posi] = estud;
			ha->qtd++;
			return 1;
		}
	}
	return 0;
}

char* busca_hash_end_aberto(hash * ha, int matricula) {
	int i, posi;
	posi = chave_dobra(matricula, ha->TABELA_SIZE);
    //posi = chave_divisao(matricula, ha->TABELA_SIZE);
	//posi = chave_multiplicacao(matricula, ha->TABELA_SIZE);
	for (i = 0; i < ha->TABELA_SIZE; i++) {
		posi = duplo_hash(posi, matricula, i, ha->TABELA_SIZE);
        //posi = sondagem_linear(posi, i, ha->TABELA_SIZE);
        //posi = sondagem_quadratica(posi, i, ha->TABELA_SIZE);
		if (ha->estudantes[posi] == NULL) {
			return NULL;
		} else if (ha->estudantes[posi]->matricula == matricula) {
			return &(ha->estudantes[posi]->nome[0]);
		}
	}
	return NULL;
}
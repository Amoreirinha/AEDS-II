#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

typedef struct e{
    int matricula;
    char nome[100];
} estudante;

typedef struct h{
    int qtd, TABELA_SIZE;
    estudante ** estudantes;
} hash;

hash * criar_tabela(int Tabela_size);
estudante * criar_estudante(int matricula, const char *nome);
void libera_hash(hash *ha);
int insere_hash_sem_colisao(hash *ha, estudante * estud);
char* busca_hash_sem_colisao(hash * ha, int matricula);
int sondagem_linear(int posi, int i, int Tabela_size);
int sondagem_quadratica(int posi, int i, int Tabela_size);
int duplo_hash(int H1, int chave, int i, int TABLE_SIZE);
int insere_hash_end_aberto(hash * ha, estudante * estud);
char* busca_hash_end_aberto(hash * ha, int matricula);

#endif
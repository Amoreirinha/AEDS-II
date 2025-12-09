#ifndef HASHING_H
#define HASHING_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

int chave_divisao(int chave, int Tabela_size);
int chave_multiplicacao(int chave, int Tabela_size);
int chave_dobra(int chave, int Tabela_size);
int valor_string(char * str);

#endif
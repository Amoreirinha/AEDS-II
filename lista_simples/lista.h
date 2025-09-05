#ifndef _H_LISTA
#define _H_LISTA

void inserir_fim(int);
void inserir_inicio(int);
void inserirPosicao(int valor, int pos);
void apagar(int);
void apagar_inicio(void);
void apagar_fim(void);
void removerPosicao(int pos);
bool ehVazia(void);
int obter_primeiro(void);
int obter_ultimo(void);
int obterPosicao(int pos);
void imprimir();

#endif // _H_LISTA
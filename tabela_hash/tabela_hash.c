#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes_hash.h"
#include "tabela_hash.h"

// Função criar tabela
hash * criar_tabela(int Tabela_size){
    hash * ha = malloc(sizeof(hash)); //cria um ponteiro de hash que recebe o ponteiro de uma alocação dinâmica da hash a ser utilizada
    // se o ponteiro ha for inicializado corretamente, entra no if
    if(ha != NULL){
        // cria em ha->estudantes um vetor de ponteiros de estudante do tamanho de ha->TABELA_SIZE
        ha->estudantes = malloc (Tabela_size * sizeof(estudante *));
        // caso não seja inicializado corretamente, libera a memória e retorna null
        if(ha->estudantes == NULL){
            free(ha);
            return NULL;
        }
        // inicializa os demais itens da tabela e preenche o vetor de ponteiros com NULL
        ha->qtd = 0;
        ha->TABELA_SIZE = Tabela_size;
        for(int i = 0; i < Tabela_size; i++){
            ha->estudantes[i]=NULL;
        }
    }
    return ha;
}

// Função criar estudante
estudante * criar_estudante(int matricula, const char *nome){
    // cria um ponteiro para um alocação dinâmica do tipo estudante
    estudante * novo = malloc(sizeof(estudante));
    if(novo == NULL) return NULL; // verifica se houve uma inicialização correta e em caso negativo retorna NULL
    // Preenche os campos de estudante corretamente:
    novo->matricula = matricula;
    strncpy(novo->nome, nome, sizeof(novo->nome) - 1); // strncpy copia a string em nome para o destino novo->nome com um tamanho de novo->nome -1 (-1 para reservar espaço para o caracter nulo "\0")
    novo->nome[sizeof(novo->nome) - 1] = '\0'; // garante que o último caracter (índice [sizeof(novo->nome)-1] seja o caracter nulo)
    return novo;
}

// Função libera hash
void libera_hash(hash *ha){
    //verifica primeiro se a hash existe (não é NULL)
    if(ha != NULL){
        // libera cada uma das alocações dinâmicas dos ponteiros no vetor de ponteiros de estudantes
        for(int i = 0; i < ha->TABELA_SIZE; i++){
            if(ha->estudantes[i] != NULL)
                free(ha->estudantes[i]);
        }
        // libera a alocação dinâmica do ponteiro do vetor de ponteiro de estudantes
        free(ha->estudantes);
        // libera a alocação dinâmica da tabela hash
        free(ha);
    }
}

// Função Insere Hash sem considerar a possibilidade de colisões
int insere_hash_sem_colisao(hash *ha, estudante * estud){
    // verifica se hash não existe (ha == NULL) ou se a tabela está completamente cheia. Se sim, retorna 0.
    if(ha == NULL || ha->qtd == ha->TABELA_SIZE)
        return 0;
    
    //ÁREA DAS FUNÇÕES HASHING
    int posi = chave_divisao(estud->matricula, ha->TABELA_SIZE);
    //int posi = chave_multiplicacao(estud->matricula, ha->TABELA_SIZE);
    //int posi = chave_dobra(estud->matricula, ha->TABELA_SIZE);

    //Após o cálculo do índice de um valor por uma função hashing, preenche o campo correspondente no vetor de ponteiros de estudante e incrementa a quantidade ocupada da hash
    ha->estudantes[posi] = estud;
    ha->qtd ++;
    return 1; // retorna 1 em caso de operação bem sucedida 
}

// Função Busca Hash sem considerar a possibilidade de colisões
char* busca_hash_sem_colisao(hash * ha, int matricula) {
    // Verifica se a tabela hash não foi iniciada (ha == NULL). Se sim, retorna NULL
    if(ha == NULL) return NULL;

    // Calcula o índice do valor buscado de acordo com a função hashing utilizada na tabela
	int posi = chave_divisao(matricula, ha->TABELA_SIZE);
    //int posi = chave_multiplicacao(estud->matricula, ha->TABELA_SIZE);
    //int posi = chave_dobra(estud->matricula, ha->TABELA_SIZE);

    // Verifica se a posição está vazia (ha->estudantes[posi] == NULL). Se sim, retorna NULL.
    if(ha->estudantes[posi] == NULL) return NULL;

    // No caso da posição não estar vazia, retorna o endereço string do nom e do estudante que está nesta posição.
	return &(ha->estudantes[posi]->nome[0]);
}

/***************************************
 * CÓDIGOS PARA TRATAMENTO DE COLISÕES
 */

// Tratamento por endereçamento aberto - Sondagem Linear
/**
 * Implementa sondagem linear (linear probing) para tratamento de colisões
 * em tabelas hash de endereçamento aberto.
 * 
 * @param posi   Posição inicial onde ocorreu a colisão (hash original)
 * @param i      Número da tentativa atual (0 = primeira posição, 1 = segunda, etc.)
 * @param Tabela_size Tamanho total da tabela hash
 * 
 * @return       Nova posição para tentar inserir/buscar o elemento
 * 
 * @details A função calcula: (posição_inicial + tentativa_atual) % tamanho_tabela
 *          Isso verifica posições sequencialmente até encontrar um slot vazio
 *          ou percorrer toda a tabela.
 * 
 * @example Se hash("chave") = 3, tabela tamanho 10:
 *          Tentativa 0: (3 + 0) % 10 = 3
 *          Tentativa 1: (3 + 1) % 10 = 4
 *          Tentativa 2: (3 + 2) % 10 = 5
 *          ...
 * 
 * @warning Pode causar "aglomeração primária" (clustering) onde elementos
 *          se acumulam em sequências longas, degradando o desempenho.
 */
int sondagem_linear(int posi, int i, int Tabela_size){
    return ((posi + i) % Tabela_size);
}

// Tratamento por endereçamento aberto - Sondagem Quadrática
/**
 * Implementa sondagem quadrática para tratamento de colisões em tabelas hash.
 * A função tenta posições seguindo um padrão quadrático para evitar
 * o problema de aglomeração primária da sondagem linear.
 * 
 * @param posi         Posição inicial (hash primário) da colisão
 * @param i            Número da tentativa (começa em 0)
 * @param Tabela_size  Tamanho total da tabela hash
 * 
 * @return             Nova posição calculada
 * 
 * @details A fórmula usada: posição = hash_inicial + 5*i + 3*i²
 *          O uso de coeficientes 5 e 3 é arbitrário - poderia ser qualquer
 *          combinação que garanta cobertura completa da tabela.
 * 
 * @example Para hash_inicial = 3, tamanho 10:
 *          i=0: 3 + 0 + 0 = 3
 *          i=1: 3 + 5 + 3 = 11 % 10 = 1
 *          i=2: 3 + 10 + 12 = 25 % 10 = 5
 *          i=3: 3 + 15 + 27 = 45 % 10 = 5 (repete!)
 * 
 * @warning Problema grave: esta implementação pode NÃO cobrir todas as
 *          posições da tabela. Com tamanho primo e coeficientes específicos,
 *          apenas ~50% dos slots podem ser acessados.
 */
int sondagem_quadratica(int posi, int i, int Tabela_size){
    posi = posi + 5*i + 3*i*i;      // Fórmula quadrática específica
    return (posi % Tabela_size);    // Aplica módulo para circular na tabela
}

// Tratamento por endereçamento aberto - Duplo Hash
/**
 * Implementa duplo hash (double hashing) - método mais avançado para
 * tratamento de colisões que minimiza aglomerações primária e secundária.
 * 
 * @param H1          Hash primário (primeira função hash)
 * @param chave       Chave original para calcular segundo hash
 * @param i           Número da tentativa atual
 * @param TABLE_SIZE  Tamanho da tabela hash
 * 
 * @return            Nova posição calculada
 * 
 * @details Usa duas funções hash independentes:
 *          1. H1(k) = hash primário
 *          2. H2(k) = hash secundário, calculado por chave_divisao()
 *          
 *          Fórmula: (H1(k) + i × H2(k)) mod TABLE_SIZE
 * 
 * @nota H2 deve ser relativamente primo com TABLE_SIZE (≠ 0)
 *       Por isso: H2 = chave_divisao(chave, TABLE_SIZE - 1) + 1
 *       Garante: 1 ≤ H2 ≤ TABLE_SIZE-1
 * 
 * @vantagens 
 *   - Distribuição quase uniforme
 *   - Evita padrões de aglomeração
 *   - Requer menos tentativas que métodos anteriores
 */
int duplo_hash(int H1, int chave, int i, int TABLE_SIZE) {
    // Calcula hash secundário usando método da divisão
    // TABLE_SIZE-1: garante que H2 será < TABLE_SIZE
    // +1: garante que H2 ≠ 0 (importante para ser primo relativo)
    int H2 = chave_divisao(chave, TABLE_SIZE - 1) + 1;
    
    // Fórmula do double hashing
    return ((H1 + i * H2) % TABLE_SIZE);
}

//Função Insere Hash com tratamento de colisões por endereçamento aberto
int insere_hash_end_aberto(hash * ha, estudante * estud) {
    // verifica se hash não existe (ha == NULL) ou se a tabela está completamente cheia. Se sim, retorna 0.
	if (ha == NULL || ha->qtd == ha->TABELA_SIZE) {
		return 0;
	}
	int posi, i; // Inteiro do índice (posi) e contador de tentativas por colisão (i)

    //Funções Hashing para cáculo do índice. Valido notar que, para o tratamento de colisões por duplo hash, a função hashing primária deve ser diferente da secundária
    //pos = chave_divisao(estud->matricula, ha->TABELA_SIZE);
	//pos = chave_multiplicacao(estud->matricula, ha->TABELA_SIZE);
	posi = chave_dobra(estud->matricula, ha->TABELA_SIZE);
    
    //Loop para inserção de um valor considerando a possibilidade de colisões
    //Na primeira interação, como i = 0, nenhuma ação de colisão é tomada (como se fosse um sucesso de primeira)
    //Caso não seja um sucesso de primeira, i vai sendo incrementado, "permitindo" a atuação da ação de tratamento de colisão até que se encontre um lugar vazio ou i atinja o tamanho da tabela.
    for (i = 0; i < ha->TABELA_SIZE; i++) {
        // desse jeito o cáculo é acumulativo, o qe não é muito usual/correto
		posi = duplo_hash(posi, estud->matricula, i, ha->TABELA_SIZE); 
        //posi = sondagem_linear(posi, i, ha->TABELA_SIZE);
        //posi = sondagem_quadratica(posi, i, ha->TABELA_SIZE);
		if (ha->estudantes[posi] == NULL) {
			ha->estudantes[posi] = estud;
			ha->qtd++;
			return 1;
		}

        /*preferível a utilização do método abaixo:
        int nova_posi = duplo_hash(posi, estud->matricula, i, ha->TABELA_SIZE); 
        //int nova_posi = sondagem_linear(posi, i, ha->TABELA_SIZE);
        //int nova_posi = sondagem_quadratica(posi, i, ha->TABELA_SIZE);
		if (ha->estudantes[nova_posi] == NULL) {
			ha->estudantes[nova_posi] = estud;
			ha->qtd++;
			return 1;
		}
        */
	}
	return 0;
}

//Função Busca Hash com tratamento de colisões por endereçamento aberto
char* busca_hash_end_aberto(hash * ha, int matricula) {
	int i, posi; // Inteiro do índice (posi) e contador de tentativas por colisão (i)

    //Funções Hashing para cáculo do índice. Valido notar que, para o tratamento de colisões por duplo hash, a função hashing primária deve ser diferente da secundária
	posi = chave_dobra(matricula, ha->TABELA_SIZE);
    //posi = chave_divisao(matricula, ha->TABELA_SIZE);
	//posi = chave_multiplicacao(matricula, ha->TABELA_SIZE);

    //Loop para a busca de um valor considerando a possibilidade de colisões
    //Na primeira interação, como i = 0, nenhuma ação de colisão é tomada (como se fosse um sucesso de primeira).
    // Então é verificado se o há algo naquele índice:
    //      - se não houver (ha->estudantes[posi] == NULL) retorna NULL
    //      - se houver:
    //                  - verifica se é a informação requerida (ha->estudantes[posi]->matricula == matricula):
    //                        - se sim, retorna o endereço do string de nome do aluno
    //                        - se não, incrementa i e continua agora com tratamento de colisões
    //Caso não seja um sucesso de primeira, i vai sendo incrementado, "permitindo" a atuação da ação de tratamento de colisão até que se encontre a informação buscada ou i atinja o tamanho da tabela.
	for (i = 0; i < ha->TABELA_SIZE; i++) {
        // desse jeito o cáculo é acumulativo, o qe não é muito usual/correto
		posi = duplo_hash(posi, matricula, i, ha->TABELA_SIZE);
        //posi = sondagem_linear(posi, i, ha->TABELA_SIZE);
        //posi = sondagem_quadratica(posi, i, ha->TABELA_SIZE);
		if (ha->estudantes[posi] == NULL) {
			return NULL;
		} else if (ha->estudantes[posi]->matricula == matricula) {
			return &(ha->estudantes[posi]->nome[0]);
		}
        /*preferível a utilização do método abaixo:
        int nova_posi = duplo_hash(posi, estud->matricula, i, ha->TABELA_SIZE);
        //int nova_posi = sondagem_linear(posi, i, ha->TABELA_SIZE);
        //int nova_posi = sondagem_quadratica(posi, i, ha->TABELA_SIZE);
		if (ha->estudantes[nova_posi] == NULL) {
			return NULL;
		} else if (ha->estudantes[nova_posi]->matricula == matricula) {
			return &(ha->estudantes[nova_posi]->nome[0]);
		}
        */
	}
	return NULL;
}
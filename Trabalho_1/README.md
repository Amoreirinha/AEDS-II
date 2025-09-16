# Autores:
- **Joaquim Pedro do Nascimento Moreira de Jesus**
- **Isabela Majeste**
- **Victória Almeida Tambasco**

---

# Descrição do Problema 
O objetivo é criar um algoritmo que, ao receber um arquivo de texto com expressões, determine se cada uma é um palíndromo (`1`) ou não (`0`), desconsiderando acentos, diacríticos, pontuação e espaços. 
O algoritmo deve utilizar exclusivamente Listas, Filas e Pilhas, estruturas de dados estudadas em sala, sem utilizar funções de string que invertam a ordem da palavra. 
A saída do algoritmo deve ser padronizada, indicando o caminho entre a entrada e a saída em duas colunas separadas por vírgula. 

---

# Algoritmo

## Estrutura de Dados
**Struct palindromo**

```c

typedef struct word {
    char str[1];
    struct word *prox;
    struct word *ant;
} palindromo;

```

Cada nó da lista contém:

`str[1]` : Armazena um único caractere (mais o terminador nulo)

`prox` : Ponteiro para o próximo nó

`ant` : Ponteiro para o nó anterior

## Funções

``` C
bool ler_linha(FILE *arquivo, palindromo **fim)
```

* **Propósito**: Lê uma linha do arquivo e constrói a lista encadeada

* **Passo a passo**:

    1. Lê caracteres do arquivo até encontrar quebra de linha ou EOF

    2. Filtra apenas letras (A-Z, a-z), ignorando espaços e outros caracteres

    3. Converte todas as letras para maiúsculas (normalização)

    4. Cria um novo nó para cada caractere válido

    5. Adiciona o nó ao final da lista encadeada

    6. Mantém os ponteiros prox e ant consistentes

``` C
bool verifica_palindromo(palindromo *inicio, palindromo *fim)
```

* **Propósito**: Verifica se a sequência de caracteres forma um palíndromo

* **Lógica de verificação**:

    1. Inicia com dois ponteiros: esquerda (início da lista) e direita (final da lista)

    2. Compara os caracteres das extremidades em direção ao centro

    3. Se algum par de caracteres for diferente, retorna false

    4. Condições de parada:

            Ponteiros se encontram (lista ímpar)

            Ponteiros se cruzam (lista par)

            Encontra caracteres diferentes

* **Complexidade**: O(n/2) - percorre apenas metade da lista

``` C
void liberar_lista(palindromo *inicio)
```

* **Propósito**: Libera toda a memória alocada para a lista encadeada

* **Passo a passo**:

    1. Percorre a lista do início ao fim

    2. Libera cada nó individualmente

    3. Mantém referência para o próximo nó antes de liberar o atual

* **Como Funciona**

    * Leitura: O texto é lido caractere por caractere

    * Filtragem: Apenas letras são consideradas (espaços e símbolos ignorados)

    * Normalização: Todas as letras são convertidas para maiúsculas

    * Construção: Lista duplamente encadeada é construída

    * Verificação: Comparação dos extremos em direção ao centro

    * Limpeza: Memória é liberada adequadamente

* **Exemplo de Uso**

    Para a frase "A man, a plan, a canal: Panama":

    1. Filtrado: "AMANAPLANACANALPANAMA"

    2. Verificação: Compara 'A' vs 'A', 'M' vs 'M', 'A' vs 'A', etc.

    3. Resultado: Verdadeiro (é palíndromo)

* **Vantagens da Abordagem**

    * Eficiente em memória (apenas caracteres necessários)

    * Verificação otimizada (O(n/2))

    * Manipulação flexível com lista duplamente encadeada

    * Fácil expansão para textos grandes

## Fluxo Principal (main)

* **Abertura do Arquivo:**

    O programa abre o arquivo "palindromo.txt" para leitura

    Se houver erro na abertura, exibe mensagem e termina a execução

* **Inicialização da Estrutura:**

    Cria um nó sentinela (palavra) que serve como ponto de partida da lista

    Inicializa os ponteiros inicio e fim para apontar para este nó sentinela

* **Processamento das Linhas:**

    Lê o arquivo linha por linha até o final (EOF)

    Para cada linha, chama a função ler_linha para processar os caracteres

    Verifica se é palíndromo usando verifica_palindromo

    Imprime "1" para palíndromo, "0" para não-palíndromo

    Libera a memória da lista (exceto o nó sentinela) para processar a próxima linha

* **Encerramento:**

    Fecha o arquivo após processar todas as linhas

    Retorna 0 indicando execução bem-sucedida
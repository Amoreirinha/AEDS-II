#ifndef _H_PALINDROMO
#define _H_PALINDROMO

typedef struct word {
    char str[1];
    struct word* prox;
    struct word* ant;
} palindromo;

#endif // _H_PALINDROMO
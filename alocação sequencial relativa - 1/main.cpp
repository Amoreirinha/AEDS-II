/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: 2025.1.08.014
 *
 * Created on 22 de maio de 2025, 08:23
 */

#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <string>

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

struct cad_pessoa {
    int key;
    string nome;
};

const int TAM = 10;

int busca1(int x, cad_pessoa BD[]) {
    for (int i = 0; i < TAM; i++) {
        if (BD[i].key == x) {
            return i;  // Retorna o índice onde foi encontrado
        }
    }
    return -1;  // Retorna -1 se não encontrou
}

int busca2(int x, cad_pessoa BD[]) {
    // Usa a última posição (TAM) como sentinela
    BD[TAM].key = x;
    int i = 0;
    while (BD[i].key != x) {
        i++;
    }
    // Se parou antes do sentinela, encontrou
    if (i < TAM) {
        return i;
    }
    // Se parou no sentinela, não encontrou
    return -1;
}

int main() {
    cad_pessoa BD[TAM+1];  // +1 para o sentinela na busca2
    int result = 0;

    // Preenche os dados (apenas até TAM-1)
    for (int i = 0; i < TAM; i++) {
        BD[i].key = i + 1;
        BD[i].nome = "Pessoa " + to_string(i+1);
    }

    // Teste busca1
    result = busca1(5, BD);
    if (result != -1) {
        cout << "Busca1: Chave 5 encontrada na posicao: " << result << endl;
        cout << "Nome: " << BD[result].nome << endl;
    } else {
        cout << "Busca1: Chave 5 nao encontrada" << endl;
    }

    // Teste busca1 com chave inexistente
    result = busca1(15, BD);
    if (result != -1) {
        cout << "Busca1: Chave 15 encontrada na posicao: " << result << endl;
    } else {
        cout << "Busca1: Chave 15 nao encontrada" << endl;
    }

    // Teste busca2
    result = busca2(5, BD);
    if (result != -1) {
        cout << "Busca2: Chave 5 encontrada na posicao: " << result << endl;
        cout << "Nome: " << BD[result].nome << endl;
    } else {
        cout << "Busca2: Chave 5 nao encontrada" << endl;
    }

    // Teste busca2 com chave inexistente
    result = busca2(15, BD);
    if (result != -1) {
        cout << "Busca2: Chave 15 encontrada na posicao: " << result << endl;
    } else {
        cout << "Busca2: Chave 15 nao encontrada" << endl;
    }

    return 0;
}
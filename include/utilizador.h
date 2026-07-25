//
// Created by joel-malacas on 7/25/26.
//

#ifndef BIBLIOTECA_UTILIZADOR_H
#define BIBLIOTECA_UTILIZADOR_H

typedef struct {
    int id;
    char nome[50];
    int idade;
} BIBLIOTECA_UTILIZADOR_H;

void criarUser();
void listarUser();
void atualizarUser();
void removerUser();

#endif //BIBLIOTECA_UTILIZADOR_H

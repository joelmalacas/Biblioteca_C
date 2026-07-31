//
// Created by joel-malacas on 7/25/26.
//

#ifndef BIBLIOTECA_UTILIZADOR_H
#define BIBLIOTECA_UTILIZADOR_H

typedef struct {
    char nome[50];
    char email[100];
    int idade;
} Utilizador;

typedef enum {
    SUCCESS = 0,
    INVALID_DATA = -1,
    DB_ERROR = -2
} Result;

Result criarUser(const char *nome, const char *email, int idade);

int listarUser();
void atualizarUser();
void removerUser();

#endif //BIBLIOTECA_UTILIZADOR_H
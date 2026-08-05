//
// Created by joel-malacas on 7/25/26.
//

#ifndef BIBLIOTECA_UTILIZADOR_H
#define BIBLIOTECA_UTILIZADOR_H
#include <stdbool.h>

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
Result listarUser();
Result atualizarUser(char *emailUpdate, char *nome, int idade);
Result removerUser(char *email);

//=====FUNC AUX=====
bool checkUser(char *email);
int UserID(char *email);
char *getEmail(int id);

#endif //BIBLIOTECA_UTILIZADOR_H
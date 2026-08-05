//
// Created by joel-malacas on 7/25/26.
//

#ifndef BIBLIOTECA_LIVRO_H
#define BIBLIOTECA_LIVRO_H
#include "utilizador.h"

typedef struct {
    int id;
    char titulo[50];
    char autor[50];
    int ano;
} Livro;

Result adicionarLivro(char *titulo, char *autorLivro, int ano);
Result listarLivros();
Result atualizarLivro(char *titulo, char *autor, int ano);
Result procurarLivro(char *titulo);
Result removerLivro(char *titulo);

//=====FUNC AUX=====
bool checkBook(char *titulo);
int bookID(char *titulo);
char *getTitulo(int id);

#endif //BIBLIOTECA_LIVRO_H
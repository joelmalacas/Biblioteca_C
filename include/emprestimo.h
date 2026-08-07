//
// Created by joel-malacas on 7/25/26.
//

#ifndef BIBLIOTECA_EMPRESTIMO_H
#define BIBLIOTECA_EMPRESTIMO_H
#include "utilizador.h"

typedef struct {
    int id_livro;
    int id_utilizador;
    char data_emprestimo[11];
    char data_devolucao[11];
    int devolvido;
} Emprestimo;

typedef struct {
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
    int segundo;
} Data;

Result loanBook(char *email, char *tituloLivro, const Data *data_devolucao);
Result returnBook(char *tituloLivro);
Result loanActive();
Result loanHistory(char *tituloLivro);
//=====FUNC AUX=====
Data HojeAux();
bool verifyReturnBook(char *tituloLivro);

#endif //BIBLIOTECA_EMPRESTIMO_H
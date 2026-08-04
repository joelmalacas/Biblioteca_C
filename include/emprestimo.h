//
// Created by joel-malacas on 7/25/26.
//

#ifndef BIBLIOTECA_EMPRESTIMO_H
#define BIBLIOTECA_EMPRESTIMO_H
#include "utilizador.h"

typedef struct {
    int id;
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

Result loanBook();
Result returnBook();
Result loanActive();
Result loanHistory();
//=====FUNC AUX=====
Data HojeAux();

#endif //BIBLIOTECA_EMPRESTIMO_H
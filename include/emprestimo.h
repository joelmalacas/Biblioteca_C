//
// Created by joel-malacas on 7/25/26.
//

#ifndef BIBLIOTECA_EMPRESTIMO_H
#define BIBLIOTECA_EMPRESTIMO_H

typedef struct {
    int id;
    int id_livro;
    int id_utilizador;
    char data_emprestimo[11];
    char data_devolucao[11];
    int devolvido;
} BIBLIOTECA_EMPRESTIMO_H;

#endif //BIBLIOTECA_EMPRESTIMO_H
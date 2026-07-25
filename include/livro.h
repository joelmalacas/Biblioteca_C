//
// Created by joel-malacas on 7/25/26.
//

#ifndef BIBLIOTECA_LIVRO_H
#define BIBLIOTECA_LIVRO_H

typedef struct {
    int id;
    char titulo[50];
    char autor[50];
    int ano;
} BIBLIOTECA_LIVRO_H;

void adicionarLivro();
void listarLivros();
void atualizarLivro();
void removerLivro();

#endif //BIBLIOTECA_EMPRESTIMO_H
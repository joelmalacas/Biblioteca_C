//
// Created by joel-malacas on 7/25/26.
//

#include <stdio.h>
#include "menu.h"

void showMainMenu() {
    printf("\n=====Sistema Biblioteca=====\n");
    printf("1. Livros \n");
    printf("2. Utilizadores \n");
    printf("3. Empréstimos \n");
    printf("0. Sair \n>");
}

void booksMenu() {
    printf("\n=====Livros Menu=====\n");
    printf("1. Adicionar Livro \n");
    printf("2. Listar Livros \n");
    printf("3. Procurar Livro \n");
    printf("4. Atualizar Livro \n");
    printf("5. Apagar Livro \n");
    printf("0. Voltar \n>");
}

void loansMenu() {
    printf("\n=====Empréstimos Menu=====\n");
    printf("1. Emprestar Livro");
    printf("2. Devolver Livro");
    printf("3. Empréstimos ativos");
    printf("4. Histórico empréstimos");
    printf("0. Voltar \n>");
}

int getOption() {
    int option;

    printf("\nOpção: ");
    scanf("%d", &option);

    return option;
}
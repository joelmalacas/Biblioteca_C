//
// Created by joel-malacas on 7/25/26.
//

#include <stdio.h>
#include <ctype.h>
#include "menu.h"
#include "livro.h"
#include "utilizador.h"
#include "emprestimo.h"

void showMainMenu() {
    printf("\n=====Sistema Biblioteca=====\n");
    printf("1. Livros \n");
    printf("2. Utilizadores \n");
    printf("3. Empréstimos \n");
    printf("0. Sair \n>");
}

void usersMenu() {
    printf("\n=====Utilizadores Menu=====\n");
    printf("1. Adicionar Utilizador \n");
    printf("2. Listar Utilizador \n");
    printf("3. Atualizar Utilizador \n");
    printf("4. Apagar Utilizador \n");
    printf("0. Voltar \n>");
}

void booksMenu() {
    printf("\n=====Livros Menu=====\n");
    printf("1. Adicionar Livro \n");
    printf("2. Listar Livros \n");
    printf("3. Atualizar Livro \n");
    printf("4. Procurar Livro \n");
    printf("5. Apagar Livro \n");
    printf("0. Voltar \n>");
}

void loansMenu() {
    printf("\n=====Empréstimos Menu=====\n");
    printf("1. Emprestar Livro \n");
    printf("2. Devolver Livro \n");
    printf("3. Empréstimos ativos \n");
    printf("4. Histórico empréstimos \n");
    printf("0. Voltar \n>");
}

void booksMenuLoop() {
    int option;

    do {
        booksMenu();
        option = getOption();

        char titulo[50], autor[30], escolha;
        int ano;

        switch (option) {
            case 1:
                printf("Introduz o titulo: \n>");
                scanf("%49s", titulo);

                printf("Introduz o autor livro: \n>");
                scanf(" %s", autor);

                printf("Introduz o ano do livro: \n>");
                scanf(" %d", &ano);

                const int resAdd = adicionarLivro(titulo, autor, ano);

                if (resAdd == INVALID_DATA || resAdd == DB_ERROR)
                    printf("Erro ao tentar criar livro\n");
                else
                    printf("Livro criado com sucesso");
                break;
            case 2:
                listarLivros();
                break;
            case 3:
                printf("Introduz o titulo a atualizar: \n>");
                scanf("%49s", titulo);

                const bool check = checkBook(titulo);

                if (!check)
                    break;

                printf("O que deseja alterar?\nAutor (a) ou Ano (i): ");
                scanf(" %c", &escolha);

                escolha=tolower(escolha); //LowerCase Char

                switch (escolha) {
                    case 'a':
                        printf("Introduz o autor: \n>");
                        scanf(" %s", autor);

                        const int resUpdateAuto = atualizarLivro(titulo, autor, 0);

                        if (resUpdateAuto == INVALID_DATA || resUpdateAuto == DB_ERROR)
                            printf("Erro ao tentar atualizar o livro");
                        else
                            printf("livro atualizado com sucesso");
                        break;
                    case 'i':
                        printf("Introduz o ano do livro: \n>");
                        scanf("%d", &ano);

                        const int resUpdateAno = atualizarLivro(titulo, NULL, ano);

                        if (resUpdateAno == INVALID_DATA || resUpdateAno == DB_ERROR)
                            printf("Erro ao tentar atualizar o livro");
                        else
                            printf("livro atualizado com sucesso");
                        break;
                    default:
                        break;
                }
                break;
            case 4:
                printf("Introduz o titulo a procurar: \n>");
                scanf("%49s", titulo);

                const int resSearch = procurarLivro(titulo);

                if (resSearch == INVALID_DATA || resSearch == DB_ERROR)
                    printf("Erro ao tentar procurar livro");
                break;
            case 5:
                printf("Introduz o titulo a remover: \n>");
                scanf("%49s", titulo);

                const bool checkbook = checkBook(titulo);

                if (!checkbook)
                    break;

                printf("Tem a certeza que quer mesmo apagar o livro? (s) || (n)\n> ");
                scanf(" %c", &escolha);

                escolha=tolower(escolha); //LowerCase Char

                switch (escolha) {
                    case 's':
                        int remBook = removerLivro(titulo);

                        if (remBook == INVALID_DATA || remBook == DB_ERROR)
                            printf("Erro ao tentar apagar livro");
                        else
                            printf("Livro apagado com sucesso");
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    } while(option != 0);

    showMainMenu();
}

void usersMenuLoop() {
    int option;

    do {
        usersMenu();

        option = getOption();

        switch (option) {
            case 1:
                //ENTRY
                char nome[50], email[100];
                int idade;

                printf("\n\nInsira o nome: ");
                scanf("%49s", nome);
                printf("\nInsira o email: ");
                scanf("%s", email);
                printf("\nInsira idade: ");
                scanf("%d", &idade);

                const int res = criarUser(nome, email, idade);

                if (res == INVALID_DATA || res == DB_ERROR)
                    printf("Erro ao tentar criar user");
                else
                    printf("Utilizador criado com sucesso");
                break;
            case 2:
                int resList = listarUser();

                if (resList == INVALID_DATA || resList == DB_ERROR)
                    printf("Erro ao tentar listar user");
                break;
            case 3:
                char escolha;

                printf("Insira o email a atualizar: ");
                scanf("%s", email);

                //TODO VERIFICA USER
                const bool resCheck = checkUser(email);

                if (!resCheck)
                    break;

                printf("O que deseja alterar?\nNome (n) ou Idade (i): ");
                scanf(" %c", &escolha);

                escolha=tolower(escolha); //LowerCase Char

                switch (escolha) {
                    case 'n':
                        printf("Introduz o novo nome: ");
                        scanf("%s", nome);
                        const int updateNome = atualizarUser(email, nome, 0);

                        if (updateNome == INVALID_DATA || updateNome == DB_ERROR)
                            printf("Erro ao tentar atualizar user");
                        else
                            printf("Atualizado com sucesso");
                        break;
                    case 'i':
                        printf("Introduz a nova idade: ");
                        scanf("%d", &idade);
                        const int updateIdade = atualizarUser(email, NULL, idade);

                        if (updateIdade == INVALID_DATA || updateIdade == DB_ERROR)
                            printf("Erro ao tentar atualizar user");
                        else
                            printf("Atualizado com sucesso");
                        break;
                    default:
                        break;
                }
                break;
            case 4:
                printf("Insira o email a apagar: ");
                scanf("%s", email);

                //TODO VERIFICA USER
                const bool resCheckDel = checkUser(email);

                if (!resCheckDel)
                    break;

                printf("Tem a certeza que quer mesmo apagar o utilizador? (s) || (n)\n> ");
                scanf(" %c", &escolha);

                escolha=tolower(escolha); //LowerCase Char

                switch (escolha) {
                    case 's':
                        int delUser = removerUser(email);

                        if (delUser == INVALID_DATA || delUser == DB_ERROR)
                            printf("Erro ao tentar apagar utilizador");
                        else
                            printf("Utilizador apagado com sucesso");
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    } while (option != 0);

    showMainMenu();
}

void loansMenuLoop() {
    int option;

    do {
        loansMenu();

        char email[50];
        char titulo[50];
        int dia, mes, ano;

        option = getOption();

        switch (option) {
            case 1:
                printf("Introduz o email do utilizador: \n>");
                scanf(" %s", email);

                printf("Introduz o título do livro: \n>");
                scanf(" %s", titulo);

                printf("Introduz o dia para devolver livro: \n>");
                scanf(" %d", &dia);

                printf("Introduz o mes devolucao: \n>");
                scanf(" %d",&mes);

                printf("Introduz o ano devolucao: \n>");
                scanf(" %d", &ano);

                Data devolucao = {.dia = dia, .mes = mes, .ano = ano};

                const int resLoan = loanBook(email, titulo, &devolucao);

                if (resLoan == INVALID_DATA || resLoan == DB_ERROR)
                    printf("Erro ao tentar atualizar empréstimo");
                else
                    printf("Empréstimo criado com sucesso");
                break;
            case 2:
                returnBook();
                break;
            case 3:
                int resActive = loanActive();
                if (resActive == INVALID_DATA || resActive == DB_ERROR)
                    printf("Erro ao tentar listar empréstimo");
                break;
            case 4:
                printf("Introduz o titulo: \n>");
                scanf(" %s", titulo);

                const int resHistory = loanHistory(titulo);

                if (resHistory == INVALID_DATA || resHistory == DB_ERROR)
                    printf("Erro ao listar histórico");
                break;
            default:
                break;
        }
    } while (option != 0);

    showMainMenu();
}

int getOption() {
    int option;

    if (scanf("%d", &option) != 1) {

        //Limpar buffer para remover entrada inválida
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}

        return -1;
    }

    return option;
}
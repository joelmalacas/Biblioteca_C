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
    printf("3. Procurar Livro \n");
    printf("4. Atualizar Livro \n");
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

    char *nomeLivro, autor;
    int ano;

    do {
        booksMenu();
        option = getOption();

        switch (option) {
            case 1:
                printf("Introduz o nome livro: \n>");
                scanf("%s", nomeLivro);

                printf("Introduz o autor livro: \n>");
                scanf(" %s", autor);

                printf("Introduz o ano do livro: \n>");
                scanf(" %d", &ano);

                adicionarLivro();
                break;
            case 2:
                listarLivros();
                break;
            case 3:
                atualizarLivro();
                break;
            case 4:
                procurarLivro();
                break;
            case 5:
                removerLivro();
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

                if (res == -1 || res == -2)
                    printf("Erro ao tentar criar user");
                else
                    printf("User criado com sucesso");
                break;
            case 2:
                int resList = listarUser();

                if (resList == -1 || resList == -2)
                    printf("Erro ao tentar listar user");
                break;
            case 3:
                char escolha;

                printf("Insira o email a atualizar: ");
                scanf("%s", email);

                //TODO VERIFICA USER
                const bool resCheck = checkUser(email);

                if (!resCheck)
                    break; //Não existe

                printf("O que deseja alterar?\nNome (n) ou Idade (i): ");
                scanf(" %c", &escolha);

                escolha=tolower(escolha); //LowerCase Char

                switch (escolha) {
                    case 'n':
                        printf("Introduz o novo nome: ");
                        scanf("%s", nome);
                        const int updateNome = atualizarUser(email, nome, 0);

                        if (updateNome == -1 || updateNome == -2)
                            printf("Erro ao tentar atualizar user");
                        else
                            printf("Atualizado com sucesso");
                        break;
                    case 'i':
                        printf("Introduz a nova idade: ");
                        scanf("%d", &idade);
                        const int updateIdade = atualizarUser(email, NULL, idade);

                        if (updateIdade == -1 || updateIdade == -2)
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

                        if (delUser == -1 || delUser == -2)
                            printf("Erro ao tentar apagar utilizador");
                        else
                            printf("Utilizador apagado com sucesso");
                        break;
                    case 'n':
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

        option = getOption();

        switch (option) {
            case 1:
                loanBook();
                break;
            case 2:
                returnBook();
                break;
            case 3:
                loanActive();
                break;
            case 4:
                loanHistory();
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
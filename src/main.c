#include <stdio.h>
#include "menu.h"

int main(void) {
    showMainMenu();

    int option;

    do {
        option = getOption();

        switch (option) {
            case 1:
                booksMenuLoop();
                break;
            case 2:
                usersMenuLoop();
                break;
            case 3:
                loansMenuLoop();
                break;
            case 0:
                showMainMenu();
                break;
            case -1:
                printf("Opção Inválida!! \n");
                showMainMenu();
                break;
            default:
                printf("Opção Inválida!! \n");
                showMainMenu();
        }
    } while (option != 0);

    return 0;
}
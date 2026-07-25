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
                loansMenu();
                break;
            case 0:
                showMainMenu();
                break;
            default:
                printf("Invalid Option!! \n");
        }

    } while (option != 0);

    return 0;
}

//
// Created by joel-malacas on 7/27/26.
//
#include <stdio.h>
#include <string.h>

int isValidName(const char *nome) {
    return nome != NULL && strlen(nome) > 0;
}

int isValidAge(int idade) {
    return idade > 0;
}

int isValidEmail(const char *email) {
    if (email == NULL)
        return 0;

    int atCount = 0;
    int dotAfterAt = 0;

    size_t len = strlen(email);

    // Tamanho mínimo: a@b.c
    if (len < 5)
        return 0;

    // Não pode começar nem terminar com @ ou .
    if (email[0] == '@' || email[0] == '.')
        return 0;

    if (email[len - 1] == '@' || email[len - 1] == '.')
        return 0;

    int foundAt = 0;

    for (size_t i = 0; i < len; i++)
    {
        if (email[i] == '@')
        {
            atCount++;
            foundAt = 1;
        }

        if (foundAt && email[i] == '.')
        {
            dotAfterAt = 1;
        }
    }

    if (atCount != 1)
        return 0;

    if (!dotAfterAt)
        return 0;

    return 1;
}
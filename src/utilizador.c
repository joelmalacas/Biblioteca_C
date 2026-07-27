//
// Created by joel-malacas on 7/27/26.
//

#include <stdio.h>
#include "utilizador.h"

#include <string.h>

#include "validation.h"
#include "database.h"

/**
 *
 * @param nome
 * @param email
 * @param idade
 * @return
 */
Result criarUser(const char *nome, const char *email, int idade) {
    if (!isValidName(nome) || !isValidEmail(email) || !isValidAge(idade))
        return INVALID_DATA;

    MYSQL *conn = dbConnect();

    if (conn == NULL)
        return DB_ERROR;

    const char *query =
        "INSERT INTO utilizador (nome, email, idade) VALUES (?, ?, ?)";

    MYSQL_STMT *stmt = mysql_stmt_init(conn);

    if (stmt == NULL) {
        dbDisconnect(conn);
        return DB_ERROR;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        printf("Prepare failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        dbDisconnect(conn);
        return DB_ERROR;
    }

    MYSQL_BIND bind[3] = {0};

    unsigned long nomeLen = strlen(nome);
    unsigned long emailLen = strlen(email);

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)nome;
    bind[0].buffer_length = nomeLen;
    bind[0].length = &nomeLen;

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)email;
    bind[1].buffer_length = emailLen;
    bind[1].length = &emailLen;

    bind[2].buffer_type = MYSQL_TYPE_LONG;
    bind[2].buffer = &idade;

    if (mysql_stmt_bind_param(stmt, bind)) {
        printf("Bind failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        dbDisconnect(conn);
        return DB_ERROR;
    }

    if (mysql_stmt_execute(stmt)) {
        printf("Execute failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        dbDisconnect(conn);
        return DB_ERROR;
    }

    mysql_stmt_close(stmt);
    dbDisconnect(conn);

    return SUCCESS;
}

void listarUser() {
    //TODO LIST USER
}

void atualizarUser() {
    //TODO UPDATE USER
}

void removerUser() {
    //TODO DEL USER
}
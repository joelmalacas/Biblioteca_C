//
// Created by joel-malacas on 7/27/26.
//

#include <stdio.h>
#include "utilizador.h"
#include <string.h>
#include "validation.h"
#include "database.h"

#define TABELA_UTILIZADOR "utilizador"

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

    if (!conn)
        return DB_ERROR;

    const char *query =
        "INSERT INTO " TABELA_UTILIZADOR " (nome, email, idade) VALUES (?, ?, ?)";

    MYSQL_STMT *stmt = mysql_stmt_init(conn);

    if (!stmt) {
        dbDisconnect(conn);
        return DB_ERROR;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
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

Result listarUser() {
    //TODO LIST USER
    MYSQL *conn = dbConnect();

    char query[256];

    snprintf(query, sizeof(query),
        "SELECT nome, email, idade, created_at FROM " TABELA_UTILIZADOR);

    if (!conn)
        return DB_ERROR;

    if (mysql_query(conn, query)) {
        printf("Erro %s\n", mysql_error(conn));
        dbDisconnect(conn);
        return DB_ERROR;
    }

    MYSQL_RES *res = mysql_store_result(conn);

    if (!res)
        return DB_ERROR;

    MYSQL_ROW row;

    printf("+--------------------------------+--------------------------------------+--------+---------------------+\n");
    printf("| %-30s | %-36s | %-6s | %-19s |\n",
           "Nome", "Email", "Idade", "Criado");
    printf("+--------------------------------+--------------------------------------+--------+---------------------+\n");

    while ((row = mysql_fetch_row(res))) {
        printf("| %-30.30s | %-36.36s | %-6s | %-19.19s |\n",
               row[0],
               row[1],
               row[2],
               row[3]);
    }

    printf("+--------------------------------+--------------------------------------+--------+---------------------+\n");
    mysql_free_result(res);
    dbDisconnect(conn);

    return SUCCESS;
}

Result atualizarUser(char *emailUpdate, char *nome, int idade) {
    //TODO UPDATE USER
    MYSQL *conn = dbConnect();

    if (!isValidEmail(emailUpdate))
        return INVALID_DATA;

    if (!checkUser(emailUpdate))
        return INVALID_DATA;

    //Obter ID User (email)
    const int id = UserID(emailUpdate);

    char query[256];

    if (isValidName(nome) && idade == 0) {
        snprintf(query, sizeof(query),
            "UPDATE " TABELA_UTILIZADOR " SET nome = \"%s\" WHERE id = %d", nome, id);
    } else if (isValidAge(idade) && nome == NULL) {
        snprintf(query, sizeof(query),
            "UPDATE " TABELA_UTILIZADOR " SET idade = \"%d\" WHERE id = %d", idade, id);
    }

    if (mysql_query(conn, query)) {
        dbDisconnect(conn);
        return DB_ERROR;
    }

    dbDisconnect(conn);
    return SUCCESS;
}

Result removerUser(char *email) {
    //TODO DEL USER
    MYSQL *conn = dbConnect();

    if (!isValidEmail(email))
        return INVALID_DATA;

    if (!checkUser(email))
        return INVALID_DATA;

    const int id = UserID(email);

    char query[256];

    snprintf(query, sizeof(query),
        "DELETE FROM " TABELA_UTILIZADOR " WHERE id = \"%d\"", id);

    if (mysql_query(conn, query)) {
        dbDisconnect(conn);
        return DB_ERROR;
    }

    dbDisconnect(conn);
    return SUCCESS;
}

//===========FUNC AUX===========

bool checkUser(char *email) {
    //TODO FUNC Bool CHECK USER EXISTS DB
    MYSQL *conn = dbConnect();

    char query[256];

    snprintf(query, sizeof(query), "SELECT email FROM " TABELA_UTILIZADOR " WHERE email = \"%s\" ", email);

    if (mysql_query(conn, query)) {
        dbDisconnect(conn);
        return false;
    }

    const MYSQL_RES *res = mysql_store_result(conn);

    if (!res) {
        dbDisconnect(conn);
        return false;
    }

    //Verificar se query encontrou result
    my_ulonglong num_rows = mysql_num_rows(res);

    const bool exists = (num_rows > 0) ? true : false;

    mysql_free_result(res);
    dbDisconnect(conn);

    return exists;
}

int UserID(char *email) {
    //TODO FUNC return ID USER (Email)
    MYSQL *conn = dbConnect();

    char query[256];
    int id = 0;

    snprintf(query, sizeof(query), "SELECT id FROM " TABELA_UTILIZADOR " WHERE email = \"%s\" LIMIT 1", email);

    if (mysql_query(conn, query)) {
        dbDisconnect(conn);
        return DB_ERROR;
    }

    const MYSQL_RES *res = mysql_store_result(conn);

    if (!res) {
        dbDisconnect(conn);
        return DB_ERROR;
    }

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(res)))
        id = atoi(row[0]);
    dbDisconnect(conn);
    return id;
}
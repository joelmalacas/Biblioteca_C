//
// Created by joel-malacas on 7/27/26.
//

#include <stdio.h>
#include "livro.h"
#include <mysql.h>
#include <string.h>

#include "database.h"
#include "validation.h"

#define TABELA_LIVRO "livro"

Result adicionarLivro(char *titulo, char *autorLivro, int ano) {

    if (!isValidName(titulo) || !isValidName(autorLivro) || ano <= 0)
        return INVALID_DATA;

    MYSQL *conn = dbConnect();

    if (!conn)
        return DB_ERROR;

    char query[256];
    snprintf(query, sizeof(query),
        "INSERT INTO " TABELA_LIVRO " (titulo, autor, ano) VALUES (?, ?, ?)");

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

    MYSQL_BIND bind[3];
    memset(bind, 0, sizeof(bind)); // Limpar a estrutura de dados

    unsigned long tituloLen = strlen(titulo);
    unsigned long autorLen = strlen(autorLivro);

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = titulo;
    bind[0].buffer_length = tituloLen;
    bind[0].length = &tituloLen;

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = autorLivro;
    bind[1].buffer_length = autorLen;
    bind[1].length = &autorLen;

    bind[2].buffer_type = MYSQL_TYPE_LONG;
    bind[2].buffer = &ano;
    bind[2].is_null = 0;
    bind[2].length = 0;

    if (mysql_stmt_bind_param(stmt, bind)) {
        mysql_stmt_close(stmt);
        dbDisconnect(conn);
        return DB_ERROR;
    }

    if (mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt);
        dbDisconnect(conn);
        return DB_ERROR;
    }

    mysql_stmt_close(stmt);
    dbDisconnect(conn);

    return SUCCESS;
}

Result listarLivros() {
    //TODO LIST LIVROS
    MYSQL *conn = dbConnect();

    if (!conn)
        return DB_ERROR;

    char query[256];

    snprintf(query, sizeof(query),
        "SELECT titulo, autor, ano, created_at, updated_at FROM " TABELA_LIVRO);

    if (mysql_query(conn, query)) {
        dbDisconnect(conn);
        return DB_ERROR;
    }

    MYSQL_RES *res = mysql_store_result(conn);

    if (!res)
        return DB_ERROR;

    my_ulonglong num_rows = mysql_num_rows(res);

    if (num_rows == 0) {
        dbDisconnect(conn);
        printf("Não tem livro para mostrar");
        return SUCCESS;
    }

    MYSQL_ROW row;

    printf("\n+--------------------------------+------------------------+------+---------------------+");
    printf("\n| TÍTULO                         | AUTOR                  | ANO  | CRIADO EM           |");
    printf("\n+--------------------------------+------------------------+------+---------------------+");

    while ((row = mysql_fetch_row(res))) {
        printf("\n| %-30.30s | %-22.22s | %-4s | %-19s |",
               row[0],
               row[1],
               row[2],
               row[3]
        );
    }

    printf("\n+--------------------------------+------------------------+------+---------------------+");
    printf("\nTotal livros: %llu\n\n", num_rows);

    dbDisconnect(conn);
    return SUCCESS;
}

Result atualizarLivro(char *titulo, char *autor, int ano) {
    //TODO UPDATE LIVRO
    MYSQL *conn = dbConnect();

    if (!isValidName(titulo))
        return INVALID_DATA;

    if (!checkBook(titulo))
        return INVALID_DATA;

    const int id = bookID(titulo);

    char query[256];

    if (isValidName(autor) && ano == 0) {
        snprintf(query, sizeof(query),
            "UPDATE " TABELA_LIVRO  " SET autor = \"%s\" WHERE id = %d", autor, id);
    } else if (isValidAge(ano) && autor == NULL) {
        snprintf(query, sizeof(query),
            "UPDATE " TABELA_LIVRO " SET ano = \"%d\" WHERE id = %d", ano, id);
    }

    if (mysql_query(conn, query)) {
        dbDisconnect(conn);
        return DB_ERROR;
    }

    dbDisconnect(conn);
    return SUCCESS;
}

Result procurarLivro(char *titulo) {
    //TODO SEARCH LIVROS
    MYSQL *conn = dbConnect();

    if (!conn)
        return DB_ERROR;

    char query[256];

    snprintf(query, sizeof(query),
    "SELECT titulo, autor, ano, created_at, updated_at FROM " TABELA_LIVRO " WHERE titulo = \"%s\"", titulo);

    if (mysql_query(conn, query)) {
        dbDisconnect(conn);
        return DB_ERROR;
    }

    MYSQL_RES *res = mysql_store_result(conn);

    if (!res)
        return DB_ERROR;

    my_ulonglong num_rows = mysql_num_rows(res);

    if (num_rows == 0) {
        dbDisconnect(conn);
        printf("Não tem livro para mostrar");
        return SUCCESS;
    }

    MYSQL_ROW row;

    printf("\n+--------------------------------+------------------------+------+---------------------+");
    printf("\n| TÍTULO                         | AUTOR                  | ANO  | CRIADO EM           |");
    printf("\n+--------------------------------+------------------------+------+---------------------+");

    while ((row = mysql_fetch_row(res))) {
        printf("\n| %-30.30s | %-22.22s | %-4s | %-19s |",
               row[0],
               row[1],
               row[2],
               row[3]
        );
    }

    printf("\n+--------------------------------+------------------------+------+---------------------+");
    printf("\nTotal livros: %llu\n\n", num_rows);

    dbDisconnect(conn);
    return SUCCESS;
}

Result removerLivro(char *titulo) {
    //TODO DEL LIVRO
    MYSQL *conn = dbConnect();

    if (!isValidName(titulo))
        return INVALID_DATA;

    if (!checkBook(titulo))
        return INVALID_DATA;

    const int id = bookID(titulo);

    char query[256];

    snprintf(query, sizeof(query),
        "DELETE FROM " TABELA_LIVRO " WHERE id = \"%d\"", id);

    if (mysql_query(conn, query)) {
        dbDisconnect(conn);
        return DB_ERROR;
    }

    dbDisconnect(conn);
    return SUCCESS;
}

bool checkBook(char *titulo) {
    //TODO FUNC Bool CHECK BOOK EXISTS DB
    MYSQL *conn = dbConnect();

    char query[256];

    snprintf(query, sizeof(query),
        "SELECT email FROM " TABELA_LIVRO " WHERE titulo = \"%s\" ", titulo);

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

int bookID(char *titulo) {
    //TODO FUNC return ID Book (Titulo)
    MYSQL *conn = dbConnect();

    char query[256];
    int id = 0;

    snprintf(query, sizeof(query),
        "SELECT id FROM " TABELA_LIVRO " WHERE titulo = \"%s\" LIMIT 1", titulo);

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
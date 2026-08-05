//
// Created by joel-malacas on 7/27/26.
//

#include <stdio.h>
#include "emprestimo.h"
#include <mysql.h>
#include <string.h>
#include <time.h>
#include "database.h"
#include "livro.h"
#include "validation.h"

#define TABELA_UTILIZADOR "utilizador"
#define TABELA_LIVRO "livro"
#define TABELA_EMPRESTIMO "emprestimo"

Result loanBook(char *email, char *tituloLivro, const Data *data_devolucao) {
    //TODO EMPRESTAR LIVRO
    if (!isValidEmail(email) || !isValidName(tituloLivro))
        return INVALID_DATA;

    if (!isValidDay(data_devolucao->dia, data_devolucao->mes, data_devolucao->ano))
        return INVALID_DATA;

    if (!checkUser(email) || !checkBook(tituloLivro))
        return INVALID_DATA;

    MYSQL *conn = dbConnect();

    //=====TIME CONFIG=====
    const Data agora = HojeAux();
    MYSQL_TIME mysql_agora = {0};
    MYSQL_TIME mysql_devolucao = {0};

    //data_emprestimo
    mysql_agora.year = agora.ano;
    mysql_agora.month = agora.mes;
    mysql_agora.day = agora.dia;
    mysql_agora.hour = agora.hora;
    mysql_agora.minute = agora.minuto;
    mysql_agora.second = agora.segundo;

    //data_devolucao
    mysql_devolucao.year = data_devolucao->ano;
    mysql_devolucao.month = data_devolucao->mes;
    mysql_devolucao.day = data_devolucao->dia;
    mysql_devolucao.hour = agora.hora;
    mysql_agora.minute = agora.minuto;
    mysql_agora.second = agora.segundo;
    //====================
    //=====PARAM DB=====
    int id_livro = bookID(tituloLivro);
    int id_user = UserID(email);
    int devolvido = 0;

    char query[256];

    snprintf(query, sizeof(query),
        "INSERT INTO " TABELA_EMPRESTIMO " (id_livro, id_utilizador, data_emprestimo, data_devolucao, devolvido) "
        "VALUES (?, ?, ?, ?, ?)");

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

    MYSQL_BIND bind[5] = {0};

    //PARAM ID_LIVRO
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = &id_livro;

    //PARAM ID_USER
    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].buffer = &id_user;

    //PARAM data_emprestimo
    bind[2].buffer_type = MYSQL_TYPE_DATETIME;
    bind[2].buffer = (char *)&mysql_agora;

    //PARAM data_devolucao
    bind[3].buffer_type = MYSQL_TYPE_DATETIME;
    bind[3].buffer = (char *)&mysql_devolucao;

    bind[4].buffer_type = MYSQL_TYPE_LONG;
    bind[4].buffer = &devolvido;

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

Result returnBook() {
    //TODO DEVOLVER LIVRO
    return SUCCESS;
}

Result loanActive() {
    //TODO EMPRESTIMO ATIVO
    return SUCCESS;
}

Result loanHistory() {
    //TODO HISTORICO EMPRESTIMO
    return SUCCESS;
}

//=====FUNC AUX=====
Data HojeAux() {
    const time_t t = time(NULL);
    const struct tm *info_tempo = localtime(&t);

    const Data hoje = {
        .dia = info_tempo->tm_mday,
        .mes = info_tempo->tm_mon + 1,
        .ano = info_tempo->tm_year + 1900,
        .hora = info_tempo->tm_hour,
        .minuto = info_tempo->tm_min,
        .segundo = info_tempo->tm_sec,
    };

    return hoje;
}
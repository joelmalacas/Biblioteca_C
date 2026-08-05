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
    //======PARAM DB======
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

Result returnBook(char *tituloLivro) {
    //TODO DEVOLVER LIVRO
    MYSQL *conn = dbConnect();

    if (!conn)
        return DB_ERROR;

    const bool resCheckBook = checkBook(tituloLivro);
    if (!resCheckBook)
        return INVALID_DATA;

    const bool resVerifyBook = verifyReturnBook(tituloLivro);
    if (!resVerifyBook)
        return INVALID_DATA;

    const int id_livro = bookID(tituloLivro);

    char query[256];
    snprintf(query, sizeof(query),
        "UPDATE " TABELA_EMPRESTIMO " SET devolvido = 1 WHERE id_livro = %d", id_livro);

    if (mysql_query(conn, query)) {
        dbDisconnect(conn);
        return DB_ERROR;
    }

    dbDisconnect(conn);
    return SUCCESS;
}

Result loanActive() {
    //TODO EMPRESTIMO ATIVO
    MYSQL *conn = dbConnect();

    if (!conn)
        return DB_ERROR;

    char query[256];

    snprintf(query, sizeof(query),
        "SELECT id_livro, id_utilizador, data_emprestimo, data_devolucao FROM "
        TABELA_EMPRESTIMO " WHERE devolvido = 0 ORDER BY data_emprestimo DESC");

    if (mysql_query(conn, query)) {
        dbDisconnect(conn);
        return DB_ERROR;
    }

    MYSQL_RES *res = mysql_store_result(conn);

    if (!res)
        return DB_ERROR;

    MYSQL_ROW row;

    my_ulonglong num_rows = mysql_num_rows(res);

    printf("\n+--------------------------------+------------------------+------------------+--------------------------+");
    printf("\n| LIVRO                          | UTILIZADOR             | DATA_EMPRESTIMO  | DATA_DEVOLUCAO           |");
    printf("\n+--------------------------------+------------------------+------------------+--------------------------+");

    while ((row = mysql_fetch_row(res))) {
        const int id_liv = atoi(row[0]);
        const int id_user = atoi(row[1]);

        // Obter o email do utilizador & titulo livro usando o ID único
        char *email = getEmail(id_user);
        char *titulo = getTitulo(id_liv);

        const char *data_emp = row[2];
        const char *data_dev = row[3];

        printf("\n| %-30.30s | %-22.22s | %-16.16s | %-24.24s |",
           titulo,
           email,
           data_emp,
           data_dev
        );

        //Libertar Memória alocada
        if (email) free(email);
        if (titulo) free(titulo);
    }

    printf("\n+--------------------------------+------------------------+------------------+--------------------------+");
    printf("\n%llu Empréstimos Ativos", num_rows);

    dbDisconnect(conn);
    return SUCCESS;
}

Result loanHistory(char *tituloLivro) {
    //TODO HISTORICO EMPRESTIMO
    MYSQL *conn = dbConnect();

    if (!conn)
        return DB_ERROR;

    const bool check = checkBook(tituloLivro);

    if (!check)
        return DB_ERROR;

    char query[256];

    const int id_livro = bookID(tituloLivro);

    snprintf(query, sizeof(query),
        "SELECT id_livro, id_utilizador, data_emprestimo, data_devolucao, devolvido FROM "
        TABELA_EMPRESTIMO " WHERE id_livro = %d",
        id_livro);

    if (mysql_query(conn, query)) {
        dbDisconnect(conn);
        return DB_ERROR;
    }

    MYSQL_RES *res = mysql_store_result(conn);

    if (!res)
        return DB_ERROR;

    MYSQL_ROW row;

    my_ulonglong num_rows = mysql_num_rows(res);

    printf("\n+------------------------------+----------------------+------------------+------------------+-----------+");
    printf("\n| LIVRO                        | UTILIZADOR           | DATA_EMPRESTIMO  | DATA_DEVOLUCAO   | DEVOLVIDO |");
    printf("\n+------------------------------+----------------------+------------------+------------------+-----------+");

    while ((row = mysql_fetch_row(res))) {
        const int id_liv = atoi(row[0]);
        const int id_user = atoi(row[1]);

        // Obter o email do utilizador & titulo livro usando o ID único
        char *email = getEmail(id_user);
        char *titulo = getTitulo(id_liv);

        const char *data_emp = row[2];
        const char *data_dev = row[3];
        const int foi_devolvido = atoi(row[4]);

        char *str_devolvido = foi_devolvido ? "SIM" : "NÃO";

        printf("\n| %-28.28s | %-20.20s | %-16.16s | %-16.16s | %-9s |",
           titulo,
           email,
           data_emp,
           data_dev,
           str_devolvido
    );

        //Libertar Memória alocada
        if (email) free(email);
        if (titulo) free(titulo);
    }

    printf("\n+--------------------------------+------------------------+------------------+--------------------------+");
    printf("\nEmpréstimos --> %llu\n", num_rows);

    dbDisconnect(conn);
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

bool verifyReturnBook(char *tituloLivro) {
    //TODO FUNC AUX PARA VERIFICAR SE O LIVRO PODE SER EMPRESTADO/DEVOLVIDO
    MYSQL *conn = dbConnect();

    if (!conn)
        return DB_ERROR;

    const int id_livro = bookID(tituloLivro);
    int devolvido = 0;

    char query[256];

    snprintf(query, sizeof(query),
        "SELECT devolvido FROM " TABELA_EMPRESTIMO " WHERE id_livro = %d",id_livro);

    if (mysql_query(conn, query)) {
        dbDisconnect(conn);
        return false;
    }

    const MYSQL_RES *res = mysql_store_result(conn);

    if (!res) {
        dbDisconnect(conn);
        return false;
    }

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(res))) {
        devolvido = atoi(row[0]);
    }

    if (devolvido != 0) {
        dbDisconnect(conn);
        return false;
    }

    dbDisconnect(conn);
    return true;
}
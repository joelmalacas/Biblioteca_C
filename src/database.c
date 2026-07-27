//
// Created by joel-malacas on 7/27/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "database.h"

MYSQL *dbConnect(void) {
    const char *host = getenv("DB_HOST");
    const char *user = getenv("DB_USER");
    const char *password = getenv("DB_PASSWORD");
    const int port = atoi(getenv("DB_PORT"));
    const char *database = getenv("DB_NAME");

    MYSQL *conn = mysql_init(NULL);

    if (conn == NULL) {
        printf("mysql_init() failed\n");
        return NULL;
    }

    if (!host || !user || !password || !port || !database) {
        printf("ERRO: Env var");
        mysql_close(conn);
        return NULL;
    }

    if (mysql_real_connect(
        conn,
        host,
        user,
        password,
        database,
        port,
        NULL,
        0) == NULL) {
        printf("%s\n", mysql_error(conn)); //DEBUG
        mysql_close(conn);
        return NULL;
    }

    return conn;
}

void dbDisconnect(MYSQL *conn) {
    if (conn != NULL) {
        mysql_close(conn);
    }
}
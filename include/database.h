//
// Created by joel-malacas on 7/27/26.
//

#ifndef BIBLIOTECA_DATABASE_H
#define BIBLIOTECA_DATABASE_H

#include <mysql/mysql.h>

MYSQL *dbConnect(void);
void dbDisconnect(MYSQL *conn);

#endif //BIBLIOTECA_DATABASE_H

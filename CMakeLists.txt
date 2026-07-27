cmake_minimum_required(VERSION 3.16)

project(Biblioteca C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(MYSQL REQUIRED mysqlclient)

add_executable(Biblioteca
        src/main.c
        src/menu.c
        src/livro.c
        src/utilizador.c
        src/emprestimo.c
        src/database.c
        src/validation.c
        include/validation.h
)

target_include_directories(Biblioteca PRIVATE
        include
        ${MYSQL_INCLUDE_DIRS}
)

target_link_libraries(Biblioteca PRIVATE
        ${MYSQL_LIBRARIES}
)
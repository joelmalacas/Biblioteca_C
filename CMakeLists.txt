cmake_minimum_required(VERSION 4.3)

project(Biblioteca C)

set(CMAKE_C_STANDARD 11)

add_executable(Biblioteca
        src/main.c
        src/menu.c
        include/menu.h
        src/livro.c
        src/utilizador.c
        src/emprestimo.c
)

target_include_directories(Biblioteca PRIVATE include)
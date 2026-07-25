# 📚 Library Management System (C + MySQL)

A console-based **Library Management System** developed in **C**, using **MySQL** as the database for persistent storage.

This project was created to improve my knowledge of C programming, modular software architecture, and relational database integration.

---

## Features

- 📖 Manage books
  - Add books
  - Update books
  - Delete books
  - Search books
  - List all books

- 👤 Manage users
  - Register users
  - Update user information
  - Remove users
  - List users

- 🔄 Book loans
  - Borrow books
  - Return books
  - View active loans
  - View loan history

- 🗄 Database
  - MySQL integration
  - Persistent data storage
  - Foreign key relationships
  - SQL CRUD operations

---

## Project Structure

```
library-management/
│
├── include/
│   ├── database.h
│   ├── livro.h
│   ├── utilizador.h
│   ├── emprestimo.h
│   └── menu.h
│
├── src/
│   ├── database.c
│   ├── livro.c
│   ├── utilizador.c
│   ├── emprestimo.c
│   ├── menu.c
│   └── main.c
│
├── sql/
│   └── library.sql
│
├── Makefile
└── README.md
```

---

## Technologies

- C (C99)
- MySQL
- MySQL C API (libmysqlclient)
- GCC
- Make

---

## Database

The project uses a MySQL database with the following main tables:

- Books
- Users
- Loans

Relationships are implemented using foreign keys.

---

## Learning Goals

This project focuses on:

- Modular programming in C
- Header and source file organization
- Dynamic memory management
- File and database operations
- SQL integration from C
- Clean project architecture
- Error handling
- Git version control

---

## Build

Compile the project with:

```bash
make
```

Or manually:

```bash
gcc src/*.c -Iinclude -lmysqlclient -o library
```

---

## Run

```bash
./library
```

---

## Future Improvements

- User authentication
- Admin and librarian roles
- Search by multiple filters
- Pagination
- Fine calculation for overdue books
- Logging system
- Unit tests
- Configuration file
- Docker support
- SQLite support

---

## License

This project is for educational purposes.

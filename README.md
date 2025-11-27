SAPID=590026688
# Library Management System (C)

Simple console-based Library Management System in C.

## Features
- Add book (title, author, copies)
- Display all books
- Search by ID or by title (prefix match)
- Issue / Return book (updates issued count)
- Delete a book
- Data persisted in `library.dat` (binary)

## Build
```bash
make
```

## Run
```bash
./main
```

## Notes
- Project follows a small modular structure with `src/` and `include/`.
- Data file `library.dat` will be created automatically in the current directory.

# Project Report - Library Management System

## Abstract
A simple console-based library management system implemented in C. Supports CRUD operations and persistent storage.

## Problem Definition
Maintain a small library database of books: add, list, search, issue and return books.

## System Design
- Language: C
- Storage: Binary file `library.dat`
- Modules: book operations (include/book.h, src/book.c) and main (src/main.c)

## Implementation
Each `Book` record is stored in binary. Operations scan/update the file as needed.

## Testing & Results
Manual testing: Add multiple books, issue them, return, delete, and display.

## Future Work
- Add student records and due dates.
- Replace binary file with a text/CSV or sqlite DB.

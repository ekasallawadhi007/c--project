#ifndef BOOK_H
#define BOOK_H

#define TITLE_LEN 100
#define AUTHOR_LEN 100

typedef struct {
    int id;
    char title[TITLE_LEN];
    char author[AUTHOR_LEN];
    int copies;   
    int issued;   
} Book;

void add_book();
void display_books();
void search_book_by_id();
void search_book_by_title();
void issue_book();
void return_book();
void delete_book();

#endif 

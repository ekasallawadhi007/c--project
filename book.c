#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/book.h"

static const char *DBFILE = "library.dat";

static FILE* open_db(const char *mode) {
    FILE *fp = fopen(DBFILE, mode);
    if (!fp) {
        perror("Unable to open data file");
        return NULL;
    }
    return fp;
}

static int get_next_id() {
    FILE *fp = fopen(DBFILE, "rb");
    if (!fp) return 1;
    Book b;
    int last = 0;
    while (fread(&b, sizeof(Book), 1, fp) == 1) {
        if (b.id > last) last = b.id;
    }
    fclose(fp);
    return last + 1;
}

void add_book() {
    Book b;
    b.id = get_next_id();
    printf("Enter title: ");
    getchar(); 
    fgets(b.title, TITLE_LEN, stdin);
    b.title[strcspn(b.title, "\n")] = '\0';
    printf("Enter author: ");
    fgets(b.author, AUTHOR_LEN, stdin);
    b.author[strcspn(b.author, "\n")] = '\0';
    printf("Enter number of copies: ");
    if (scanf("%d", &b.copies) != 1) { printf("Invalid input\n"); return; }
    b.issued = 0;

    FILE *fp = open_db("ab");
    if (!fp) return;
    fwrite(&b, sizeof(Book), 1, fp);
    fclose(fp);
    printf("Book added with ID %d\n", b.id);
}

void display_books() {
    FILE *fp = open_db("rb");
    if (!fp) return;
    Book b;
    printf("\n%-5s %-30s %-20s %-8s %-8s\n", "ID", "Title", "Author", "Copies", "Issued");
    printf("----------------------------------------------------------------------------\n");
    while (fread(&b, sizeof(Book), 1, fp) == 1) {
        printf("%-5d %-30s %-20s %-8d %-8d\n", b.id, b.title, b.author, b.copies, b.issued);
    }
    fclose(fp);
}

void search_book_by_id() {
    int id;
    printf("Enter book ID: ");
    if (scanf("%d", &id) != 1) { printf("Invalid input\n"); return; }
    FILE *fp = open_db("rb");
    if (!fp) return;
    Book b;
    int found = 0;
    while (fread(&b, sizeof(Book), 1, fp) == 1) {
        if (b.id == id) {
            printf("Found: ID=%d, Title=%s, Author=%s, Copies=%d, Issued=%d\n", b.id, b.title, b.author, b.copies, b.issued);
            found = 1;
            break;
        }
    }
    if (!found) printf("Book with ID %d not found.\n", id);
    fclose(fp);
}

void search_book_by_title() {
    char q[TITLE_LEN];
    printf("Enter title (or prefix): ");
    getchar();
    fgets(q, TITLE_LEN, stdin);
    q[strcspn(q, "\n")] = '\0';
    FILE *fp = open_db("rb");
    if (!fp) return;
    Book b;
    int found = 0;
    while (fread(&b, sizeof(Book), 1, fp) == 1) {
        if (strncasecmp(b.title, q, strlen(q)) == 0) {
            printf("Found: ID=%d, Title=%s, Author=%s, Copies=%d, Issued=%d\n", b.id, b.title, b.author, b.copies, b.issued);
            found = 1;
        }
    }
    if (!found) printf("No book with title starting '%s' found.\n", q);
    fclose(fp);
}

void issue_book() {
    int id;
    printf("Enter book ID to issue: ");
    if (scanf("%d", &id) != 1) { printf("Invalid input\n"); return; }
    FILE *fp = open_db("rb+");
    if (!fp) return;
    Book b;
    int found = 0;
    while (fread(&b, sizeof(Book), 1, fp) == 1) {
        if (b.id == id) {
            found = 1;
            if (b.issued < b.copies) {
                b.issued++;
                fseek(fp, -((long)sizeof(Book)), SEEK_CUR);
                fwrite(&b, sizeof(Book), 1, fp);
                printf("Book issued successfully. Now issued: %d\n", b.issued);
            } else {
                printf("All copies are already issued.\n");
            }
            break;
        }
    }
    if (!found) printf("Book with ID %d not found.\n", id);
    fclose(fp);
}

void return_book() {
    int id;
    printf("Enter book ID to return: ");
    if (scanf("%d", &id) != 1) { printf("Invalid input\n"); return; }
    FILE *fp = open_db("rb+");
    if (!fp) return;
    Book b;
    int found = 0;
    while (fread(&b, sizeof(Book), 1, fp) == 1) {
        if (b.id == id) {
            found = 1;
            if (b.issued > 0) {
                b.issued--;
                fseek(fp, -((long)sizeof(Book)), SEEK_CUR);
                fwrite(&b, sizeof(Book), 1, fp);
                printf("Book returned successfully. Now issued: %d\n", b.issued);
            } else {
                printf("No copies of this book are currently issued.\n");
            }
            break;
        }
    }
    if (!found) printf("Book with ID %d not found.\n", id);
    fclose(fp);
}

void delete_book() {
    int id;
    printf("Enter book ID to delete: ");
    if (scanf("%d", &id) != 1) { printf("Invalid input\n"); return; }
    FILE *fp = open_db("rb");
    if (!fp) return;
    FILE *tf = fopen("temp.dat", "wb");
    if (!tf) { fclose(fp); perror("temp file"); return; }
    Book b;
    int found = 0;
    while (fread(&b, sizeof(Book), 1, fp) == 1) {
        if (b.id == id) {
            found = 1;
            continue; 
        }
        fwrite(&b, sizeof(Book), 1, tf);
    }
    fclose(fp);
    fclose(tf);
    if (found) {
        remove(DBFILE);
        rename("temp.dat", DBFILE);
        printf("Book with ID %d deleted.\n", id);
    } else {
        remove("temp.dat");
        printf("Book with ID %d not found.\n", id);
    }
}
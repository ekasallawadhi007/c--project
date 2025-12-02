#include <stdio.h>
#include <stdlib.h>
#include "../include/book.h"

void display_menu() {
    printf("\nLibrary Management System\n");
    printf("1. Add Book\n");
    printf("2. Display Books\n");
    printf("3. Search Book by ID\n");
    printf("4. Search Book by Title\n");
    printf("5. Issue Book\n");
    printf("6. Return Book\n");
    printf("7. Delete Book\n");
    printf("8. Exit\n");
    printf("Choose an option: ");
}

int main() {
    int choice;

    while (1) {
        display_menu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n'); // clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                add_book();
                break;
            case 2:
                display_books();
                break;
            case 3:
                search_book_by_id();
                break;
            case 4:
                search_book_by_title();
                break;
            case 5:
                issue_book();
                break;
            case 6:
                return_book();
                break;
            case 7:
                delete_book();
                break;
            case 8:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
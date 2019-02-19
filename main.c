#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Book {
    char title[50];
    char author[50];
    int isbn_nr;
    int nob;
};

typedef struct Book book;

struct Lib {
    book **Books
};

typedef struct Lib lib;


book *newBook() {
    book newBook;

    printf("\n Wie ist der Titel?\n");
    scanf("%s", newBook.title);
    printf("\nWer ist der Author?\n");
    scanf("%s", newBook.author);
    printf("\nWas ist die ISBN?\n");
    scanf("%d",&newBook.isbn_nr);
    printf("\nWie viele Exemplare?\n");
    scanf("%d",&newBook.nob);

    book *bookPtr = malloc(sizeof(book));
    strcpy(bookPtr->title, newBook.title);
    strcpy(bookPtr->author, newBook.author);
    bookPtr->isbn_nr = newBook.isbn_nr;
    bookPtr->nob = newBook.nob;

    return bookPtr;
}

//void addBook(lib lib1) {
//    newBook();
//
//}
//
//void saveBooks
//
//void printBook(struct Books *book) {
//
//    printf( "Book title : %s\n", book->title);
//    printf( "Book author : %s\n", book->author);
//    printf( "Book isbn number : %d\n", book->isbn_nr);
//    printf( "Number of Books available : %d\n", book->nob);
//}

void mainmenu() {
    printf("Willkommen");
    printf("Was wollen Sie tun ? \n"
           "(1) : Buch hnizufügen\n");

    int i;
    scanf("%d", &i);
    switch(i)
    {
        case 1:
            break;
    }
}


int main() {

    mainmenu();
    lib lib1;
    book *book1 = newBook();
    printf("Titel : %s",book1->title);

//    FILE *fp;
//    int c;
//    fp = fopen("test.txt", "w+");
//    fwrite(&book1,sizeof(struct Books),1,fp);
//    fread(&book1, sizeof(struct Books),1,fp);
//    fclose(fp);
//
//    fp = fopen("test.txt", "r+");
//    if(fp == NULL) {
//        perror("Problem with opening file");
//    }
//    else {
//        while (1) {
//            c = fgetc(fp);
//            if (feof(fp))
//                break;
//            printf("%c", c);
//        }
//    }
//    fclose(fp);
    return 0;
}


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/main.h"

book *newBook() {
    book newBook;
    int buffersize = 50;
    char buffer[buffersize];

    printf("\n Wie ist der Titel?\n");
//    while (buffer[strlen(fgets(buffer,buffersize,stdin)) - 1] != '\n') {
//    }
//    strcpy(newBook.title, buffer);
    gets(buffer);
    newBook.title = malloc(sizeof(buffer));
    strcpy(newBook.title,buffer);

    printf("\nWer ist der Author?\n");
    gets(buffer);
    newBook.author = malloc(sizeof(buffer));
    strcpy(newBook.author,buffer);

    printf("\nWas ist die ISBN?\n");
    scanf("%d",&newBook.isbn_nr);

    printf("\nWie viele Exemplare?\n");
    scanf("%d",&newBook.nob);
    printf("---1---");
    book *bookPtr = malloc(sizeof(book));
    bookPtr->title = malloc(sizeof(newBook.title));
    strcpy(bookPtr->title, newBook.title);
    bookPtr->author = malloc(sizeof(newBook.author));
    strcpy(bookPtr->author, newBook.author);
    bookPtr->isbn_nr = newBook.isbn_nr;
    bookPtr->nob = newBook.nob;
    printf("---2---");
    return bookPtr;
}

void addBook() {
    lib1.registered++;
    printf("%d\n",lib1.registered);
    lib1.Books = realloc(lib1.Books, sizeof(book*) * lib1.registered);
    lib1.Books[lib1.registered - 1] = newBook();
    printf("---F---");
}

void saveBooks() {
    FILE *save;
    size_t length=0;
    save = fopen("saves.b", "wb");
    fwrite(&lib1.registered, sizeof(int),1,save);
    printf("---1---");
    for(int i=0; i < lib1.registered; i++) {
        //save title
        length = strlen(lib1.Books[i]->title)+1;
        fwrite(&length,sizeof(size_t),1,save);
        fwrite(lib1.Books[i]->title,length,1, save);
        printf("---title---");
        //save author
        length = strlen(lib1.Books[i]->author)+1;
        fwrite(&length,sizeof(size_t),1,save);
        fwrite(lib1.Books[i]->author,length,1, save);
        printf("---author---");
        //save isbn_nr
        fwrite(&lib1.Books[i]->isbn_nr,sizeof(int),1, save);
        printf("---isbn---");
        //save number of books
        fwrite(&lib1.Books[i]->nob,sizeof(int),1, save);
        printf("---nob---");
    }
    fclose(save);

};

void loadBooks() {
    FILE *load;
    size_t length;
    load = fopen("saves.b","rb");
    if(load == NULL) {
        fclose(load);
        printf("Nothing to load from file\n");
    }
    else {
        fseek(load, 0, SEEK_SET);
        fread(&lib1.registered, sizeof(int), 1, load);
        lib1.Books = calloc(lib1.registered, sizeof(book *));
        for (int i = 0; i < lib1.registered; i++) {
            lib1.Books[ i ] = malloc(sizeof(book));
            //load title
            fread(&length, sizeof(size_t), 1, load);
            lib1.Books[ i ]->title = malloc(length);
            //load author
            fread(&length, sizeof(size_t), 1, load);
            lib1.Books[ i ]->author = malloc(length);
            fread(&lib1.Books[ i ]->author, length, 1, load);
            //load isbn_nr
            fread(&lib1.Books[ i ]->isbn_nr, sizeof(int), 1, load);
            //load number of books
            fread(&lib1.Books[ i ]->nob, sizeof(int), 1, load);
        }
        fclose(load);
    }
}

void show() {
    size_t length;
    FILE *fptr;
    printf("---1---");
    if ((fptr = fopen("saves.b", "rb")) == NULL) {
        printf("Error! opening file");

        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    fseek(fptr, 0, SEEK_SET);
    fread(&lib1.registered, sizeof(int), 1, fptr);
    printf("\nAnzahl Bücher: \t%d",lib1.registered);
    lib1.Books = calloc(lib1.registered, sizeof(book *));
    printf("---2---");
    for (int i = 0; i < lib1.registered; i++) {
        //Speicherallokation
        lib1.Books[ i ] = malloc(sizeof(book));
        printf("---s---");
        //Titel
        fread(&length, sizeof(size_t), 1, fptr);
        printf("\nLänge des Titel:\t%d",(int)length);
        lib1.Books[ i ]->title = malloc(length);
        fread(&lib1.Books[i]->title,length,1,fptr);
        printf("\nTitel:\t%s",lib1.Books[i]->title);
        printf("---t---");
        //Author
        fread(&length, sizeof(size_t), 1, fptr);
        printf("\nLänge des Authors:\t%d",(int) length);
        lib1.Books[ i ]->author = malloc(length);
        fread(&lib1.Books[i]->author,length,1,fptr);
        printf("\nAuthor:\t%s",lib1.Books[i]->author);
        printf("---a---");
        //ISBN
        fread(&lib1.Books[ i ]->isbn_nr, sizeof(int), 1, fptr);
        printf("\nISBN:\t%d", lib1.Books[i]->isbn_nr);
        printf("---i---");
        //Number of Books
        fread(&lib1.Books[ i ]->nob, sizeof(int), 1, fptr);
        printf("\nExemplare:\t%d", lib1.Books[i]->nob);
        printf("---n---");
        fclose(fptr);
    }
}

//void mainmenu() {
//    printf("Willkommen");
//    printf("Was wollen Sie tun ? \n"
//           "(1) : Buch hnizufügen\n");
//
//    int i;
//    scanf("%d", &i);
//    switch(i)
//    {
//        case 1:
//            break;
//    }
//}



int main() {
    //loadBooks als gegensatz zu saveBooks
    loadBooks();
    printf("--1/4--");
//    char a;
//    a = lib1.Books[0]->title;
//    printf("%s",a);
    addBook();//fügt ein Buch hinzu
    printf("--2/4--");
    saveBooks();    //speichert alle Bücher in einer binärdatei -> beim exit
    printf("--3/4--");
    show();
    printf("--4/4--");
    return 0;
}


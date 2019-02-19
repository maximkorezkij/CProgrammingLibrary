#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

book *newBook() {
    book newBook;

    printf("\n Wie ist der Titel?\n");  //Titel und Author können nicht mit Leerzeichen eingegeben werden
    scanf("%s", newBook.title);         // besser mit fgets( , , stdin) -> evtl funktion für string
    printf("\nWer ist der Author?\n");  //Prüfen auf Fehleingabe fehlt
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

void addBook() {
    lib1.registered++;
    printf("%d",lib1.registered);
    lib1.Books = realloc(lib1.Books, sizeof(book*) * lib1.registered);
    lib1.Books[lib1.registered - 1] = newBook();
}

void saveBooks() {
    FILE *fp;
    fp = fopen("test.txt", "wb");
    fwrite(&lib1.registered, sizeof(int),1,fp);
    for(int i=0; i < lib1.registered; i++) {
        fwrite(&lib1.Books[i]->title,strlen(lib1.Books[i]->title),1, fp);
        fwrite(&lib1.Books[i]->author,strlen(lib1.Books[i]->author),1, fp);
        fwrite(&lib1.Books[i]->isbn_nr,sizeof(int),1, fp);
        fwrite(&lib1.Books[i]->nob,sizeof(int),1, fp);
    }
    fclose(fp);

};


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

    addBook(lib1);      //fügt ein Buch hinzu
    saveBooks(lib1);    //speichert alle Bücher in einer binärdatei -> beim exit

    return 0;
}


#ifndef PROJECTS_FUNC_C
#define PROJECTS_FUNC_C
#include "../inc/main.h"
#include "../inc/func.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define Max 100
#endif


book *newBook(char *newtitle, char *newauthor, char *newisbn, int newnob) {
    book newBook;
    //rückgabe als pointer
    book *bookPtr = malloc(sizeof(book));
    //title
    bookPtr->title = malloc(strlen(newtitle) + 1);
    strcpy(bookPtr->title, newtitle);
    //author
    bookPtr->author = malloc(strlen(newauthor) + 1);
    strcpy(bookPtr->author, newauthor);
    //isbn nr
    bookPtr->isbn_nr = malloc(strlen(newisbn) + 1);
    strcpy(bookPtr->isbn_nr, newisbn);
    //number of books
    bookPtr->nob = newnob;
    //bookPtr->r_list;
    return bookPtr;
}

void saveBooks() {
    FILE *ptr;
    ptr = fopen("saves.b","wb");
    size_t length = 0;
    fseek(ptr, 0, SEEK_SET);
    fwrite(&lib1.registered, sizeof(int), 1, ptr);
    for ( int i = 0; i < lib1.registered; i++ ) {
        //save number of books
        fwrite(&lib1.Books[ i ]->nob, sizeof(int), 1, ptr);
        //save isbn_nr
        length = strlen(lib1.Books[ i ]->isbn_nr) + 1;
        fwrite(&length, sizeof(size_t), 1, ptr);
        fwrite(lib1.Books[ i ]->isbn_nr, length, 1, ptr);
        //save title
        length = strlen(lib1.Books[ i ]->title) + 1;
        fwrite(&length, sizeof(size_t), 1, ptr);
        fwrite(lib1.Books[ i ]->title, length, 1, ptr);
        //save author
        length = strlen(lib1.Books[ i ]->author) + 1;
        fwrite(&length, sizeof(size_t), 1, ptr);
        fwrite(lib1.Books[ i ]->author, length, 1, ptr);
    }
    fclose(ptr);
}

void loadBooks() {
    FILE *ptr;
    ptr = fopen("saves.b","rb");
    size_t length;
    if ( ptr == NULL || !fsize("saves.b")) {
        fclose(ptr);
        printf("Keine Datei zum Laden einer vorhandenen Bibliothek.\n");
    }else {
        fseek(ptr, 0, SEEK_SET);
        fread(&lib1.registered, sizeof(int), 1, ptr);
        lib1.Books = calloc(lib1.registered, sizeof(book *));
        for ( int i = 0; i < lib1.registered; i++ ) {

            lib1.Books[ i ] = malloc(sizeof(book));
            //load number of books
            fread(&lib1.Books[ i ]->nob, sizeof(int), 1, ptr);
            //load isbn_nr
            fread(&length, sizeof(size_t), 1, ptr);
            lib1.Books[ i ]->isbn_nr = malloc(length);
            fread(lib1.Books[ i ]->isbn_nr, length, 1, ptr);
            //load title
            fread(&length, sizeof(size_t), 1, ptr);
            lib1.Books[ i ]->title = malloc(length);
            fread(lib1.Books[ i ]->title, length, 1, ptr);
            //load author
            fread(&length, sizeof(size_t), 1, ptr);
            lib1.Books[ i ]->author = malloc(length);
            fread(lib1.Books[ i ]->author, length, 1, ptr);
        }
        fclose(ptr);
    }
}

void show(lib help) {
    printf("\nAnzahl Bücher : \t%d\n", help.registered);
    printf("- - - - - - - - - - -");
    for ( int i = 0; i < help.registered; i++ ) {
        //Titel
        printf("\nTitel :\t\t%s", help.Books[ i ]->title);
        //Author
        printf("\nAuthor :\t%s", help.Books[ i ]->author);
        //ISBN
        printf("\nISBN :\t\t%s", help.Books[ i ]->isbn_nr);
        //Number of Books
        printf("\nExemplare :\t%d\n", help.Books[ i ]->nob);
        printf("- - - - - - - - - - -");
    }
}

void showByIsbn(lib help) {
    char filter[10] = {};
    int count = 0;      //zeigt an wie viele Treffer es gab
    printf("\n\nFiltern nach ISBN:\n\n");
    isString(filter);   //filter wird durch isString ein valider String mitgegeben -> möglich : ein ISBN filter
    stringCut(filter);  //entfernt '\n' vom String damit der compare richtig läuft
    printf("- - - - - - - - - - -");
    for ( int i = 0; i < help.registered; i++ ) {
        if (strncasecmp(filter,help.Books[i]->isbn_nr,strlen(filter)) == 0) {
            //Titel
            printf("\nTitel :\t\t%s", help.Books[ i ]->title);
            //Author
            printf("\nAuthor :\t%s", help.Books[ i ]->author);
            //ISBN
            printf("\nISBN :\t\t%s", help.Books[ i ]->isbn_nr);
            //Number of Books
            printf("\nExemplare :\t%d\n", help.Books[ i ]->nob);
            printf("- - - - - - - - - - -");
            count += 1;
        }
    }
    if( count > 0 )
        printf("\nAnzahl der Treffer : %d\n",count);
    else
        printf("\nEs gibt kein Buch mit dieser ISBN-NR.\n");
}

void showByTitle(lib help) {
    char filter[Max] = {};
    int count = 0;      //zeigt an wie viele Treffer es gab
    printf("\n\nFiltern nach Titel:\n\n");
    isString(filter);   //filter wird durch isString ein valider String mitgegeben -> möglich : ein ISBN filter
    stringCut(filter);  //entfernt '\n' vom String damit der compare richtig läuft
    printf("- - - - - - - - - - -");
    for ( int i = 0; i < help.registered; i++ ) {
        if (strncasecmp(filter,help.Books[i]->title,strlen(filter)) == 0) {
            //Titel
            printf("\nTitel :\t\t%s", help.Books[ i ]->title);
            //Author
            printf("\nAuthor :\t%s", help.Books[ i ]->author);
            //ISBN
            printf("\nISBN :\t\t%s", help.Books[ i ]->isbn_nr);
            //Number of Books
            printf("\nExemplare :\t%d\n", help.Books[ i ]->nob);
            printf("- - - - - - - - - - -");
            count += 1;
        }
    }
    if( count > 0 )
        printf("\nAnzahl der Treffer : %d\n",count);
    else
        printf("\nEs gibt kein Buch mit diesem Titel.\n");
}

void moveBooks(int i) {
    book *bookPtr1; //hilfspointer
    book *bookPtr2; //hilfspointer
    if ( lib1.registered == 2 ) {   //bei 2 Büchern muss man nur 1 element schieben
        bookPtr1 = lib1.Books[ 0 ];
        lib1.Books[ 1 ] = bookPtr1;
    }
    if ( lib1.registered > 2 ) {    //bei mehr als 2 Büchern muss man die weiteren schieben
        if ( i < lib1.registered - 1 ) {    //wenn dass Buch nicht an die letzte stelle musst, schiebt er
            bookPtr1 = lib1.Books[ i ];
            for ( int j = i; j < lib1.registered - 2; j ++ ) {
                bookPtr2 = lib1.Books[ j +1]; //bookptr2 ist ein hilfsplatz für das nächste zu haltende element
                lib1.Books[ j + 1 ] = bookPtr1; //bookptr1 ist das verschobene element
                bookPtr1 = bookPtr2;
            }
            lib1.Books[ lib1.registered - 1 ] = bookPtr1;   //belegt noch den letzten Platz, der in der schleife nicht belegt wird
        }
    }
}

void addBookSorted() {
    lib1.registered ++;
    lib1.Books = realloc(lib1.Books, sizeof(book *) * lib1.registered);
    //titel
    printf("\nWie ist der Titel des Buches ?\n(max.100 Zeichen)\n");
    char title[Max] = {};
    isString(title);    //returns title string if valid
    //author
    printf("\nWer ist der Author des Buches ?\n(max.100 Zeichen)\n");
    char author[Max] = {};
    isString(author);   //return author string if valid
    //isbn
    printf("\nWas ist die ISBN-Nr ?\n(muss gueltig sein)\n");
    char isbn[Max] = {};
    isbnNumber(isbn);
    //number of books
    printf("\nWie viele Exemplare gibt es?\n(Nur Zahlen)\n");
    int nob = isNumber();
    //remove \n from strings
    stringCut(author);
    stringCut(title);

    int i = 0;      //enthält die richtige Stelle für das neue Buch
    if ( lib1.registered == 1 ) {                 //bei einem Buch muss man nicht sortieren
        lib1.Books[ i ] = newBook(title, author, isbn, nob);
    }
    if ( lib1.registered > 1 ) {        //bei mehreren Büchern vergleicht man
        for ( int j = i; j < lib1.registered - 1; j ++ ) {
            if ( strncasecmp(title, lib1.Books[ j ]->title, Max) == 0 ) {       //eingegebener Titel = titel aus einem Buch
                if ( strncasecmp(author, lib1.Books[ j ]->author, Max) == 0 ) {    //eingegebener Author = author aus einem buch
                    if ( strcasecmp(isbn, lib1.Books[ j ]->isbn_nr) == 0 ) {            //eingegebene isbn = isbn aus einem Buch
                        printf("Dieses Buch existiert schon. Probieren Sie es erneut:\n");  //fehler weil 2 identische bücher
                        lib1.registered --;
                        addBookSorted();
                    }
                    if ( strcasecmp(isbn, lib1.Books[ j ]->isbn_nr) > 0 ) {         //schauen ob eingegebene isbn nach(alphabetisch) vorhandener isbn kommt
                        if ( i == lib1.registered - 1 )
                            break;
                        else
                            i ++;
                    }
                    if ( strcasecmp(isbn, lib1.Books[ j ]->isbn_nr) < 0 ) {         //schauen ob eingegebene isbn vor vorhanderer isbn kommt
                        break;
                    }
                }
                if ( strncasecmp(author, lib1.Books[ j ]->author,Max) > 0 ) {
                    if ( i == lib1.registered - 1 )
                        break;
                    else
                        i ++;
                }
                if ( strncasecmp(author, lib1.Books[ j ]->author, Max) < 0 ) {
                    break;
                }
            }
            if ( strncasecmp(title, lib1.Books[ j ]->title, Max) > 0 ) {
                if ( i == lib1.registered - 1 )
                    break;
                else
                    i ++;
            }
            if ( strncasecmp(title, lib1.Books[ j ]->title, Max) < 0 ) {
                break;
            }
        }
        moveBooks(i);       //schiebt alle Bücher weiter, sodass das neue buch seinen richtig sortierten Platz einnehmen kann
        lib1.Books[ i ] = newBook(title, author, isbn, nob);    //belegt den richtigen Platz mit dem Buch
    }
    printf("\n Das Buch wurde hinzugefügt.");
}

void rentBook(book *helpPtr) {
    //Buch aufgerufen und angezeigt
    char var; //Antwortsvariable
    int h = 0; //Hilfsvariable
    bool b = true; //Hilfsvariable
    printf("\nBuch ausleihen? \nJa[1] \nNein[2]");
    var = (char) getchar(); //Einlesen von antwort
    if ( var == '1' ) {
        printf("\n Verfügbarkeit wird geprüft.");
        if ( helpPtr->nob > 0 ) {
            printf("\nBuch verfügbar. ");
            printf("\nName eingeben (Nachname, Vorname)");
            char name[Max] = {};
            isString(name);
            helpPtr->nob -= 1; //Exemplarzahl um 1 reduziert
            while ( b ) {
                if ( helpPtr->r_list[ h ][ 0 ] == ' ' || helpPtr->r_list[ h ][ 0 ] == '\0' ) {
                    helpPtr->r_list[ h ][ 0 ] = name; //Name wird in Liste eingetragen
                    printf("\nName wurde in Ausleihliste eingetragen. Vielen Dank.");
                    b = false;
                }
                h ++;
            }
            bookMenu(); //zurück zum Menü
        }
    }
}

void deleteBook(book *helpPtr){
    lib tmplib = {};
    printf("\nSind Sie sicher, dass sie dieses Buch loeschen wollen? \nJa[1] \nNein[2]");
    char e = (char) getchar();
    if(e == '1'){
        for(int i = 0; i<lib1.registered; i++){
            if(lib1.Books[i]->isbn_nr == helpPtr->isbn_nr) continue; //alle bücher außer des zu löschende
            tmplib.Books[i] = lib1.Books[i];                        //werden in eine temporäre bibliothek gespeichert
            tmplib.registered++;
        }
        for(int i = 0; i<lib1.registered; i++){         //speicherplatz in haupt bibliothek wird freigegeben
            free(lib1.Books[i]);
        }
        lib1 = tmplib;      //der Hauptbib wird die temporäre übergeben
        saveBooks();
        for(int i = 0; i<lib1.registered; i++){
            //Titel
            printf("\nTitel :\t\t%s", lib1.Books[ i ]->title);
            //Author
            printf("\nAuthor :\t%s", lib1.Books[ i ]->author);
            //ISBN
            printf("\nISBN :\t\t%s", lib1.Books[ i ]->isbn_nr);
            //Number of Books
            printf("\nExemplare :\t%d\n", lib1.Books[ i ]->nob);
            printf("- - - - - - - - - - -");
        }
    }
}

void searchByTitle(lib help) {
    char filter[Max] = {};
    int count = 0;      //zeigt an wie viele Treffer es gab
    lib tmplib = {};
    book *tmpPtr = malloc(sizeof(book));
    printf("\n\nFiltern nach Titel:\n\n");
    isString(filter);   //filter wird durch isString ein valider String mitgegeben -> möglich : ein ISBN filter
    stringCut(filter);  //entfernt '\n' vom String damit der compare richtig läuft
    printf("- - - - - - - - - - -");
    //bei zu vielen ergebnissen -> keine ausgabe
    for (int i = 0;i < help.registered;i++ ) {                                  //Bücher mit gleichen Titel rausfiltern
        if(strncasecmp(filter, help.Books[i]->title,strlen(filter)) == 0) {
        //title
        tmpPtr->title = malloc(strlen(help.Books[ i ]->title) + 1);             //alle bücher werden in temporären Pointer
        strcpy(tmpPtr->title, help.Books[i]->title);                            //gespeichert und später in die temporäre
        //author                                                                //library eingefügt
        tmpPtr->author = malloc(strlen(help.Books[ i ]->author) + 1);
        strcpy(tmpPtr->author, help.Books[i]->author);
        //isbn nr
        tmpPtr->isbn_nr = malloc(strlen(help.Books[ i ]->isbn_nr) + 1);
        strcpy(tmpPtr->isbn_nr, help.Books[i]->isbn_nr);
        //number of books
        tmpPtr->nob = help.Books[ i ]->nob;
        //tmpPtr->r_list;
        tmplib.registered++;
        tmplib.Books = realloc(tmplib.Books, sizeof(book *) * tmplib.registered);
        tmplib.Books[i] = tmpPtr;
        count++;
        }
    }
    if (count == 0) {
        printf("Dieses Buch haben wir nicht.\n");
        printf("Wollen Sie ein anderes suchen?\n");
        printf("\t(1) Ja\n");
        printf("\t(2) Nein\n");
        int e;
        e = isNumber();
        while(1) {
            switch(e) {
                case 1:
                    searchByTitle(lib1);
                    break;
                case 2:
                    return;
                default:
                    printf("Eingabe ungültig\n");
                    break;
            }
        }
    }
    if( count > 0 ) {
        for ( int j = 0; j < tmplib.registered; j ++ ) {                 //print alle zutreffenden Bücher
            printf("\nBuch Nr. %d ", j+1);
            //Titel
            printf("\nTitel :\t\t%s", tmplib.Books[ j ]->title);
            //Author
            printf("\nAuthor :\t%s", tmplib.Books[ j ]->author);
            //ISBN
            printf("\nISBN :\t\t%s", tmplib.Books[ j ]->isbn_nr);
            //Number of Books
            printf("\nExemplare :\t%d\n", tmplib.Books[ j ]->nob);
            printf("- - - - - - - - - - -");
        }
        printf("Welches Buch wollen Sie auswählen?\n");             //welches der passenden Bücher wird ausgewählt
        int h;
        h = isNumber();
        book *helpPtr = malloc(sizeof(book));                       //helpPtr in dem das ausgewählte Buch kommt
        //title
        helpPtr->title = malloc(strlen(help.Books[ h - 1 ]->title) + 1);
        strcpy(helpPtr->title, help.Books[ h - 1 ]->title);
        //author
        helpPtr->author = malloc(strlen(help.Books[ h - 1 ]->author) + 1);
        strcpy(helpPtr->author, help.Books[ h - 1 ]->author);
        //isbn nr
        helpPtr->isbn_nr = malloc(strlen(help.Books[ h - 1 ]->isbn_nr) + 1);
        strcpy(helpPtr->isbn_nr, help.Books[ h - 1 ]->isbn_nr);
        //number of books
        helpPtr->nob = help.Books[ h - 1 ]->nob;
        //tmpPtr->r_list;
        bookMenu(helpPtr);                  //helpptr sollte in ein Menü übergeben werden
    }
}

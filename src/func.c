#ifndef PROJECTS_FUNC_C
#define PROJECTS_FUNC_C
#include "../include/main.h"
#include "../include/func.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define Max 100
#endif


book *newBook(char *newtitle, char *newauthor, char *newisbn, int newnob) {
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
        //save id
        fwrite(&i,sizeof(int),1,ptr);
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
        //save r_list
    }
    fclose(ptr);
}

void loadBooks() {
    FILE *ptr;
    ptr = fopen("saves.b","rb");            //kein fclose auf nen null pointer
    size_t length;
    if ( ptr == NULL || !fsize("saves.b")) {
        fclose(ptr);
        printf("Keine Datei zum Laden einer vorhandenen Bibliothek.\n");
    }else {
        fseek(ptr, 0, SEEK_SET);
        fread(&lib1.registered, sizeof(int), 1, ptr);
        lib1.Books = calloc((size_t) lib1.registered, sizeof(book *));
        for ( int i = 0; i < lib1.registered; i++ ) {
            lib1.Books[ i ] = malloc(sizeof(book));
            //load id
            fread(&lib1.Books[i]->id, sizeof(int),1,ptr);
            //load number of books
            fread(&lib1.Books[ i ]->nob, sizeof(int), 1, ptr);
            //load isbn_nr
            fread(&length, sizeof(size_t), 1, ptr);
            lib1.Books[ i ]->isbn_nr = malloc(length);
            fread(lib1.Books[ i ]->isbn_nr, length, 1, ptr);
            //load title
            fread(&length, sizeof(size_t), 1, ptr);
            lib1.Books[ i ]->title = malloc(length);
            fread(lib1.Books[ i ]->title, length, 1, ptr); // if fread ... != length -> auf die fresse
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
//
//void showByIsbn(lib help) {
//    char filter[10] = {};
//    int count = 0;      //zeigt an wie viele Treffer es gab
//    printf("\n\nFiltern nach ISBN:\n\n");
//    isString(filter);   //filter wird durch isString ein valider String mitgegeben -> möglich : ein ISBN filter
//    stringCut(filter);  //entfernt '\n' vom String damit der compare richtig läuft
//    printf("- - - - - - - - - - -");
//    for ( int i = 0; i < help.registered; i++ ) {
//        if (strncasecmp(filter,help.Books[i]->isbn_nr,strlen(filter)) == 0) {
//            //Titel
//            printf("\nTitel :\t\t%s", help.Books[ i ]->title);
//            //Author
//            printf("\nAuthor :\t%s", help.Books[ i ]->author);
//            //ISBN
//            printf("\nISBN :\t\t%s", help.Books[ i ]->isbn_nr);
//            //Number of Books
//            printf("\nExemplare :\t%d\n", help.Books[ i ]->nob);
//            printf("- - - - - - - - - - -");
//            count += 1;
//        }
//    }
//    if( count > 0 )
//        printf("\nAnzahl der Treffer : %d\n",count);
//    else
//        printf("\nEs gibt kein Buch mit dieser ISBN-NR.\n");
//}
//
//void showByTitle(lib help) {
//    char filter[Max] = {};
//    int count = 0;      //zeigt an wie viele Treffer es gab
//    printf("\n\nFiltern nach Titel:\n\n");
//    isString(filter);   //filter wird durch isString ein valider String mitgegeben -> möglich : ein ISBN filter
//    stringCut(filter);  //entfernt '\n' vom String damit der compare richtig läuft
//    printf("- - - - - - - - - - -");
//    for ( int i = 0; i < help.registered; i++ ) {
//        if (strncasecmp(filter,help.Books[i]->title,strlen(filter)) == 0) {
//            //Titel
//            printf("\nTitel :\t\t%s", help.Books[ i ]->title);
//            //Author
//            printf("\nAuthor :\t%s", help.Books[ i ]->author);
//            //ISBN
//            printf("\nISBN :\t\t%s", help.Books[ i ]->isbn_nr);
//            //Number of Books
//            printf("\nExemplare :\t%d\n", help.Books[ i ]->nob);
//            printf("- - - - - - - - - - -");
//            count += 1;
//        }
//    }
//    if( count > 0 )
//        printf("\nAnzahl der Treffer : %d\n",count);
//    else
//        printf("\nEs gibt kein Buch mit diesem Titel.\n");
//}

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
    char title[Max] = {};
    char author[Max] = {};
    char isbn[Max] = {};
    int nob;
    lib1.registered ++;
    lib1.Books = realloc(lib1.Books, sizeof(book *) * lib1.registered);
    askForBook(title, author, isbn, &nob);

    int i = 0;      //enthält die richtige Stelle für das neue Buch
    if( lib1.registered == 1 ) {                 //bei einem Buch muss man nicht sortieren
        lib1.Books[ i ] = newBook(title, author, isbn, nob);
    }
    if( lib1.registered > 1 ) {        //bei mehreren Büchern vergleicht man
        for ( int j = i; j < lib1.registered - 1; j ++ ) {
            if( strncasecmp(title, lib1.Books[ j ]->title, Max) ==
                    0 ) {       //eingegebener Titel = titel aus einem Buch
                if( strncasecmp(author, lib1.Books[ j ]->author, Max) ==
                        0 ) {    //eingegebener Author = author aus einem buch
                    if( strcasecmp(isbn, lib1.Books[ j ]->isbn_nr) ==
                            0 ) {            //eingegebene isbn = isbn aus einem Buch
                        printf("Dieses Buch existiert schon. Probieren Sie es erneut:\n");  //fehler weil 2 identische bücher
                        lib1.registered --;
                        addBookSorted();
                    }
                    if( strcasecmp(isbn, lib1.Books[ j ]->isbn_nr) >
                            0 ) {         //schauen ob eingegebene isbn nach(alphabetisch) vorhandener isbn kommt
                        if( i == lib1.registered - 1 )
                            break;
                        else
                            i ++;
                    }
                    if( strcasecmp(isbn, lib1.Books[ j ]->isbn_nr) <
                            0 ) {         //schauen ob eingegebene isbn vor vorhanderer isbn kommt
                        break;
                    }
                }
                if( strncasecmp(author, lib1.Books[ j ]->author, Max) > 0 ) {
                    if( i == lib1.registered - 1 )
                        break;
                    else
                        i ++;
                }
                if( strncasecmp(author, lib1.Books[ j ]->author, Max) < 0 ) {
                    break;
                }
            }
            if( strncasecmp(title, lib1.Books[ j ]->title, Max) > 0 ) {
                if( i == lib1.registered - 1 )
                    break;
                else
                    i ++;
            }
            if( strncasecmp(title, lib1.Books[ j ]->title, Max) < 0 ) {
                break;
            }
        }
        moveBooks(
                i);       //schiebt alle Bücher weiter, sodass das neue buch seinen richtig sortierten Platz einnehmen kann
        lib1.Books[ i ] = newBook(title, author, isbn, nob);    //belegt den richtigen Platz mit dem Buch
    }
    printf("\n Das Buch wurde hinzugefügt.");
}

void rentBook(book *helpPtr) {
    //Buch bereits aufgerufen und angezeigt
    char var; //Antwortsvariable
    int h = 0; //Hilfsvariable
    bool b = true; //Hilfsvariable
    char name[Max] = {};
    printf("\nBuch ausleihen? \n\t(1) Ja  \n\t(2) Nein");
    var = (char) getchar();       //isNumber braucht 10 digits für eine korrekte Eingabe
    switch(var) {
        case '1':
            printf("\n Verfügbarkeit wird geprüft.");
            if (helpPtr->nob > 0) {       //wenn Exemplare vorhanden sind
                printf("\nBuch verfügbar. ");
                printf("\nName eingeben (Nachname, Vorname)");
                isString(name);
                helpPtr->nob -= 1; //Exemplarzahl um 1 reduziert
                while (b) {           //klappert liste ab bis der name hinzugefügt worden ist
                    if (helpPtr->r_list[h][0] == ' ' || helpPtr->r_list[h][0] == '\0') {
                        for (int i = 0; i < sizeof(name); i++) {
                            helpPtr->r_list[h][i] = name[i];  //Name wird in Liste eingetragen
                        }
                        printf("\nName wurde in Ausleihliste eingetragen. Vielen Dank.");
                        b = false; //name wurde eingetragen und die schleife wird verlassen
                    }
                    h++;
                }
                printf("\nAusleiherliste :\t\t%s", helpPtr->r_list);  //liste muss noch ordnungsgemäß abgespeichert werden
                bookMenu(helpPtr); //zurück zum Menü -> lieber ins main menu aber das können wir ändern
            }
            else{
                printf("\nKeine Exemplare momentan vorhanden.\n");
                bookMenu(helpPtr);
            }
            break;
        case '2':
            mainMenu();
            break;
        default:
            printf("Ungültige Eingabe");
            rentBook(helpPtr);
    }
}

void returnBook(book *helpPtr){
    if(helpPtr->r_list[0][0] == ' ' || helpPtr->r_list[0][0] == '\0'){ //Überprüft, ob überhaupt was in der Ausleiherliste ist
        printf("\nKein Exemplar momentan verliehen.");
    }
    else{
        char h_list[][Max] = {}; //Hilfsliste
        int length = 0; //Hilfsvariable, die Länge der ursprünglichen Liste speichert
        while(true){
            if(helpPtr->r_list[length][0] == ' ' || helpPtr->r_list[length][0] == '\0')break;
            length++;
        }
        printf("\nNamen des Ausleihers eingeben (Nachname, Vorname)\n");
        char e = (char) getchar();
        printf("\nListe wird durchsucht...");
        for(int i = 0; i<length; i++){      //Untersucht jeden eingetragenen in der liste
            if(strcasecmp(e, helpPtr->r_list[i]) == 0){         //String wird rausgefiltert
                continue;
            }
            for(int j = 0; j < sizeof(helpPtr->r_list[i]); j++){         //Listenelemente, die nicht übereinstimmen werden in eine Hilfsliste gelegt
                h_list[i][j] = helpPtr->r_list[i][j];
            }
        }
        int h_length = 0; //Hilfsvariable, die Länge der Hilfsliste speichert
        while(true){
            if(h_list[h_length][0] == ' ' || h_list[length][0] == '\0')break;
            h_length++;
        }
        if(h_length != length-1){
            printf("\nKein Eintrag zu eingegebenen Ausleiher gefunden");
        }
        else{
            printf("\nBuch erfolgreich zuruekgegeben");
            for(int i = 0; i<sizeof(h_list); i++){
                for(int j = 0; j < sizeof(helpPtr->r_list[i]); j++){         //Listenelemente aus der Hilfslliste wieder in die ursprüngliche übertragen
                    h_list[i][j] = helpPtr->r_list[i][j];
                }
            }
            mainMenu(); //zurück zum Menü
        }
    }
}

void searchByTitle(lib help) {
    char filter[Max] = {};
    int count = 0;      //zeigt an wie viele Treffer es gab
    int j = 0;
    lib tmplib = {};
    printf("\n\nFiltern nach Titel:\n");
    printf("Auswahl: \n");
    isString(filter);   //filter wird durch isString ein valider String mitgegeben -> möglich : ein ISBN filter
    stringCut(filter);  //entfernt '\n' vom String damit der compare richtig läuft
    printf("- - - - - - - - - - -\n");
    //bei zu vielen ergebnissen -> keine ausgabe
    for (int i = 0;i < help.registered;i++ ) {                                  //Bücher mit gleichen Titel rausfiltern
        if(strncasecmp(filter, help.Books[i]->title,strlen(filter)) == 0) {
        tmplib.registered++;
        tmplib.Books = realloc(tmplib.Books, sizeof(book *) * tmplib.registered);
        tmplib.Books[j] = help.Books[i];
        count++;
        j++;
        }
    }
    if (count == 0) {
        searchAgain();
    }
    if( count > 0 ) {
        for ( int k = 0; k < tmplib.registered; k ++ ) {                 //print alle zutreffenden Bücher
            printf("Buch Nr. (%d) \n", k+1);
            //Titel
            printf("Titel :\t\t%s\n", tmplib.Books[k]->title);
            //Author
            printf("Author :\t%s\n", tmplib.Books[k]->author);
            //ISBN
            printf("ISBN :\t\t%s\n", tmplib.Books[k]->isbn_nr);
            //Number of Books
            printf("Exemplare :\t%d\n", tmplib.Books[k]->nob);
            printf("- - - - - - - - - - -\n");
        }
        printf("Welches Buch wollen Sie auswählen?\nAuswahl: \n");             //welches der passenden Bücher wird ausgewählt
        int h;
        h = isNumber();
        bookMenu(tmplib.Books[h-1]);
    }
}

void searchByIsbn(lib help) {
    char filter[Max] = {};
    int count = 0;      //zeigt an wie viele Treffer es gab
    int j = 0;
    lib tmplib = {};
    printf("\n\nFiltern nach ISBN-Nr:\n");
    printf("Auswahl: \n");
    isString(filter);   //filter wird durch isString ein valider String mitgegeben -> möglich : ein ISBN filter
    stringCut(filter);  //entfernt '\n' vom String damit der compare richtig läuft
    printf("- - - - - - - - - - -\n");
    //bei zu vielen ergebnissen -> keine ausgabe
    for (int i = 0;i < help.registered;i++ ) {                                  //Bücher mit gleichen Titel rausfiltern
        if(strncasecmp(filter, help.Books[i]->isbn_nr,strlen(filter)) == 0) {
            tmplib.registered++;
            tmplib.Books = realloc(tmplib.Books, sizeof(book *) * tmplib.registered);
            tmplib.Books[j] = help.Books[i];
            count++;
            j++;
        }
    }
    if (count == 0) {
        searchAgain();
    }
    if( count > 0 ) {
        for ( int k = 0; k < tmplib.registered; k ++ ) {                 //print alle zutreffenden Bücher
            printf("Buch Nr. (%d) \n", k+1);
            //Titel
            printf("Titel :\t\t%s\n", tmplib.Books[k]->title);
            //Author
            printf("Author :\t%s\n", tmplib.Books[k]->author);
            //ISBN
            printf("ISBN :\t\t%s\n", tmplib.Books[k]->isbn_nr);
            //Number of Books
            printf("Exemplare :\t%d\n", tmplib.Books[k]->nob);
            printf("- - - - - - - - - - -\n");
        }
        printf("Welches Buch wollen Sie auswählen?\nAuswahl: \n");             //welches der passenden Bücher wird ausgewählt
        int h;
        h = isNumber();
        bookMenu(tmplib.Books[h-1]);
    }
}

void askForBook(char *title,char *author,char *isbn, int *nob) {
    //titel
    printf("\nWie ist der Titel des Buches ?\n(max.100 Zeichen)\n");
    isString(title);    //returns title string if valid
    //author
    printf("\nWer ist der Author des Buches ?\n(max.100 Zeichen)\n");
    isString(author);   //return author string if valid
    //isbn
    printf("\nWas ist die ISBN-Nr ?\n(muss gueltig sein)\n");
    isbnNumber(isbn);
    //number of books
    printf("\nWie viele Exemplare gibt es?\n(Nur Zahlen)\n");
    int i;
    i = isNumber();
    *nob = i;
    //remove \n from strings
    stringCut(author);
    stringCut(title);
}

void deleteBook(book *delete) {
    book *bookPtr1; //hilfspointer
    book *bookPtr2; //hilfspointer
    if( lib1.registered == 1 ) {        //bei einem Buch löscht es das erste
        free(lib1.Books[ 0 ]);
        lib1.registered --;
        lib1.Books = realloc(lib1.Books, 0);
    }
    if( lib1.registered > 1 ) {         //bei mehreren Bücher
        int i = delete->id;
        bookPtr1 = lib1.Books[ i ];     //bookPtr1 = das Element das gelöscht werden soll
        for ( int j = i; j < lib1.registered - 2; j ++ ) {      //die Pointer von den Büchern wandern vor
            bookPtr2 = lib1.Books[ j + 1 ];                     //bis sie das letzte in das vorletzte feld
            lib1.Books[ j ] = bookPtr2;                         //schieben
        }
        bookPtr2 = lib1.Books[lib1.registered-1];
        lib1.Books[lib1.registered-2] = bookPtr2;
        free(bookPtr1);                     //das zu löschende Element wird gefreed
        lib1.registered--;                      // Ein buch weniger
        lib1.Books = realloc(lib1.Books, sizeof(book *) * lib1.registered);     //Speicher der lib anpassen
    }
    printf("Das Buch wurde erfolgreich gelöscht.\n\n");
}

void searchAgain() {
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
                printf("Eingabe ungueltig.\n");
                break;
        }
    }
}
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
    book *bookPtr = safeMalloc(sizeof(book));
    //title
    bookPtr->title = safeMalloc(strlen(newtitle) + 1);
    strcpy(bookPtr->title, newtitle);
    //author
    bookPtr->author = safeMalloc(strlen(newauthor) + 1);
    strcpy(bookPtr->author, newauthor);
    //isbn_nr
    bookPtr->isbn_nr = safeMalloc(strlen(newisbn) + 1);
    strcpy(bookPtr->isbn_nr, newisbn);
    //number of books
    bookPtr->nob = newnob;
    //r_count
    bookPtr->r_count = 0;
    //r_list
    bookPtr->r_list = NULL;
    return bookPtr;
}

void saveBooks() {
    FILE *ptr;
    ptr = fopen(data ,"wb");
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
        //save r_count
        fwrite(&lib1.Books[i]->r_count, sizeof(int), 1, ptr);
        //save r_list
        for(int j = 0; j< lib1.Books[i]->r_count; j++){
            length = strlen(lib1.Books[i]->r_list[j]+1);
            fwrite(&length, sizeof(size_t), 1, ptr);
            fwrite(lib1.Books[i]->r_list[j], length, 1 ,ptr);
        }
    }
    fclose(ptr);
}

void loadBooks() {
    FILE *ptr;
    ptr = fopen(data,"rb");
    size_t length;
    if(!fsize("saves.b")) {
        printf("Keine Datei zum Laden einer vorhandenen Bibliothek.\n");
    }
    if ( ptr == NULL ) {
        fclose(ptr);
        printf("Keine Datei zum Laden einer vorhandenen Bibliothek.\n");
    }else {
        fseek(ptr, 0, SEEK_SET);
        fread(&lib1.registered, sizeof(int), 1, ptr);
        lib1.Books = safeCalloc((size_t) lib1.registered, sizeof(book *));
        for ( int i = 0; i < lib1.registered; i++ ) {
            lib1.Books[ i ] = safeMalloc(sizeof(book));
            //load id
            fread(&lib1.Books[i]->id, sizeof(int),1,ptr);
            //load number of books
            fread(&lib1.Books[ i ]->nob, sizeof(int), 1, ptr);
            //load isbn_nr
            fread(&length, sizeof(size_t), 1, ptr);
            lib1.Books[ i ]->isbn_nr = safeMalloc(length);
            if(fread(lib1.Books[ i ]->isbn_nr, length, 1, ptr) != 1 ) {
                printf("Es gab ein Problem mit dem Laden der Sicherungsdatei.\nNotfalls muessen sie %s loeschen.\n",data);
                exit(0);
            }
            //load title
            fread(&length, sizeof(size_t), 1, ptr);
            lib1.Books[ i ]->title = safeMalloc(length);
            if (fread(lib1.Books[ i ]->title, length, 1, ptr) != 1 ) {
                printf("Es gab ein Problem mit dem Laden der Sicherungsdatei.\nNotfalls muessen sie %s loeschen.\n",data);
                exit(0);
            }
            //load author
            fread(&length, sizeof(size_t), 1, ptr);
            lib1.Books[ i ]->author = safeMalloc(length);
            if (fread(lib1.Books[ i ]->author, length, 1, ptr)!= 1 ) {
                printf("Es gab ein Problem mit dem Laden der Sicherungsdatei.\nNotfalls muessen sie %s loeschen.\n",data);
                exit(0);
            }
            //load r_count
            fread(&lib1.Books[i]->r_count, sizeof(int), 1, ptr);

            //load r_list
            lib1.Books[i]->r_list = malloc(sizeof(char *) * lib1.Books[i]->r_count);
            lib1.Books[i]->r_list = safeMalloc(sizeof(char *) * lib1.Books[i]->r_count);
            for(int n = 0; n < lib1.Books[i]->r_count; n++){
                fread(&length, sizeof(size_t), 1, ptr);
                lib1.Books[i]->r_list[n] = safeMalloc(length);
                if (fread(lib1.Books[i]->r_list[n], length, 1, ptr)!= 1 ) {
                    printf("Es gab ein Problem mit dem Laden der Sicherungsdatei.\nNotfalls muessen sie %s loeschen.\n",data);
                    exit(0);
                }
            }
        }
    }
    fclose(ptr);
}

void show(lib help) {
    if (lib1.registered == 0) {
        printf("Es gibt keine Bücher zum anzeigen.");
    }
    else {
        printf("\nAnzahl Buecher : \t%d\n", help.registered);
        printf("- - - - - - - - - - -");
        for ( int i = 0; i < help.registered; i ++ ) {
            //title
            printf("\nTitel :\t\t%s", help.Books[ i ]->title);
            //author
            printf("\nAutor :\t\t%s", help.Books[ i ]->author);
            //isbn_nr
            printf("\nISBN :\t\t%s", help.Books[ i ]->isbn_nr);
            //number of books
            printf("\nExemplare :\t%d", help.Books[ i ]->nob);
            printf("\n- - - - - - - - - - -");
        }
    }
}

void moveBooks(int i) {
    book *bookPtr1; //Hilfspointer
    book *bookPtr2; //Hilfspointer
    if ( lib1.registered == 2 ) {   //bei 2 Büchern muss man nur 1 Element schieben
        bookPtr1 = lib1.Books[ 0 ];
        lib1.Books[ 1 ] = bookPtr1;
    }
    if ( lib1.registered > 2 ) {    //bei mehr als 2 Büchern muss man die weiteren schieben
        if ( i < lib1.registered - 1 ) {    //wenn das Buch nicht an die letzte Stelle muss, schiebt er
            bookPtr1 = lib1.Books[ i ];
            for ( int j = i; j < lib1.registered - 2; j ++ ) {
                bookPtr2 = lib1.Books[ j +1]; //bookptr2 ist ein Hilfsplatz für das nächste zu haltende Element
                lib1.Books[ j + 1 ] = bookPtr1; //bookptr1 ist das verschobene Element
                bookPtr1 = bookPtr2;
            }
            lib1.Books[ lib1.registered - 1 ] = bookPtr1;   //belegt noch den letzten Platz, der in der Schleife nicht belegt wird
        }
    }
}

void addBookSorted() {
    char title[Max] = {};
    char author[Max] = {};
    char isbn[Max] = {};
    int nob;
    lib1.registered ++;
    lib1.Books = safeRealloc(lib1.Books, sizeof(book *) * lib1.registered);
    askForBook(title, author, isbn, &nob);

    int i = 0;      //enthält die richtige Stelle für das neue Buch
    if( lib1.registered == 1 ) {                 //bei einem Buch muss man nicht sortieren
        lib1.Books[ i ] = newBook(title, author, isbn, nob);
    }
    if( lib1.registered > 1 ) {        //bei mehreren Büchern vergleicht man
        for ( int j = i; j < lib1.registered - 1; j ++ ) {
            if( strncasecmp(isbn, lib1.Books[ j ]->isbn_nr, Max) == 0 ) {
                printf("Dieses Buch existiert schon. Vorgang wird abgebrochen... \n");
                lib1.registered --;
            }
            if ( strncasecmp(title, lib1.Books[ j ]->title, Max) == 0 ) {       //eingegebener Titel = Titel aus einem Buch
                if( strncasecmp(author, lib1.Books[ j ]->author, Max) ==
                        0 ) {    //eingegebener Autor = Autor aus einem Buch
                    break;
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
        moveBooks(i);       //schiebt alle Bücher weiter, sodass das neue Buch seinen richtig sortierten Platz einnehmen kann
        lib1.Books[ i ] = newBook(title, author, isbn, nob);    //belegt den richtigen Platz mit dem Buch
    }
    printf("\nDas Buch wurde hinzugefuegt.");
}

void rentBook(book *helpPtr) {
    //Buch bereits aufgerufen und angezeigt
    char name[Max];
    printf("\nBuch ausleihen? \n\t(1) Ja  \n\t(2) Nein\n");
    int var;
    var = isNumber();       //isNumber braucht 10 digits für eine korrekte Eingabe
    switch(var) {
        case 1:
            printf("\nVerfuegbarkeit wird geprueft.");
            if (helpPtr->nob > 0) {       //wenn Exemplare vorhanden sind
                printf("\nBuch verfuegbar. ");
                printf("\nName eingeben (Nachname Vorname)\n");
                isString(name);
                stringCut(name);
                for(int i = 0; i < helpPtr->r_count; i++){                    //Überprüft, ob eingegebene Person nicht schon ein Exemplar geliehen hat
                    if(strcasecmp(name, helpPtr->r_list[i]) == 0){                //Eintrag gefunden
                        printf("\n%s hat das Buch bereits einmal ausgeliehen.\n", name);
                        rentBook(helpPtr);
                    }
                }
                helpPtr->nob--; //Exemplarzahl um 1 reduziert
                helpPtr->r_count++;
                helpPtr->r_list = safeRealloc(helpPtr->r_list, sizeof(char *) * helpPtr->r_count);
                helpPtr->r_list[helpPtr->r_count-1] = safeMalloc(strlen(name));
                strcpy(helpPtr->r_list[helpPtr->r_count-1], name);
                printf("Ausleiher wurde hinzugefuegt.");
            }
            else{
                printf("\nKeine Exemplare momentan vorhanden.\n");
            }
            break;
        case 2:
            break;
        default:
            printf("Ungueltige Eingabe");
            break;
    }
}

void returnBook(book *helpPtr) {
    char name[Max];
    int pos = 0;                   //zählt bis zur Position des gesuchten Elements hoch
    if(helpPtr->r_count == 0){      //überprüft, ob Buch überhaupt ausgeliehen wurde
        printf("\nBuch ist momentan nicht verliehen.\n");
    }
    else{
        printf("\nName des Ausleihers angeben (Nachname Vorname)\n"); //Name des Ausleihers wird eingegeben
        isString(name);
        stringCut(name);
        for(int i = 0; i < helpPtr->r_count; i++){                    //Namen werden verglichen
            if(strcasecmp(name, helpPtr->r_list[i]) == 0){                //Eintrag gefunden
                printf("\nEingegebene Person im Verzeichnis gefunden. Buch wird nun zurueckgegeben...\n");
                helpPtr->nob++;
                helpPtr->r_count--;
                pos = i;                                                //pos merkt sich aktuelle Position in der Liste
                for(int j = i+1; j<helpPtr->r_count; j++){                //Name wird aus Liste entfernt und alle folgenden Namen um 1 verschoben
                    helpPtr->r_list[pos] = safeRealloc(helpPtr->r_list[pos], sizeof(helpPtr->r_list[j]));
                    strcpy(helpPtr->r_list[pos], helpPtr->r_list[j]);
                    pos++;
                }
                free(helpPtr->r_list[helpPtr->r_count]);                //letzer platz wird gefreed
                printf("\nVorgang erfolgreich. Name des Entleihers wurde aus der Ausleiherliste entfernt.\n");
                return;
            }
        }
        printf("Kein Eintrag gefunden...");
        return;
    }
}

void searchByTitle(lib help) {
    char filter[Max] = {};
    int count = 0;      //zeigt an wie viele Treffer es gab
    int j = 0;
    lib tmplib = {};
    printf("\n\nFiltern nach Titel:\n");
    printf("Auswahl: \n");
    isString(filter);   //Filter wird durch isString ein valider String mitgegeben -> möglich : ein ISBN Filter
    stringCut(filter);  //entfernt '\n' vom String damit der compare richtig läuft
    printf("- - - - - - - - - - -\n");
    //bei zu vielen Ergebnissen -> keine Ausgabe
    for (int i = 0;i < help.registered;i++ ) {                                  //Bücher mit gleichem Titel rausfiltern
        if(strncasecmp(filter, help.Books[i]->title,strlen(filter)) == 0) {
        tmplib.registered++;
        tmplib.Books = safeRealloc(tmplib.Books, sizeof(book *) * tmplib.registered);
        tmplib.Books[j] = help.Books[i];
        count++;
        j++;
        }
    }
    if (count == 0) {
        printf("Dieses Buch haben wir nicht. Gehe ins Hauptmenue...\n");
    }
    if ( count == 1) {
        printf("Buch Nr. (1) \n");
        //title
        printf("Titel :\t\t%s\n", tmplib.Books[0]->title);
        //author
        printf("Autor :\t\t%s\n", tmplib.Books[0]->author);
        //isbn_nr
        printf("ISBN :\t\t%s\n", tmplib.Books[0]->isbn_nr);
        //number of books
        printf("Exemplare :\t%d\n", tmplib.Books[0]->nob);
        printf("- - - - - - - - - - -\n");
        bookMenu(tmplib.Books[0]);
    }
    if( count > 1 ) {
        for ( int k = 0; k < tmplib.registered; k ++ ) {                 //print alle zutreffenden Bücher
            printf("Buch Nr. (%d) \n", k+1);
            //title
            printf("Titel :\t\t%s\n", tmplib.Books[k]->title);
            //author
            printf("Autor :\t\t%s\n", tmplib.Books[k]->author);
            //isbn_nr
            printf("ISBN :\t\t%s\n", tmplib.Books[k]->isbn_nr);
            //number of books
            printf("Exemplare :\t%d\n", tmplib.Books[k]->nob);
            printf("- - - - - - - - - - -\n");
        }
        printf("Welches Buch wollen Sie auswaehlen?\nAuswahl: \n");             //welches der passenden Bücher wird ausgewählt
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
    isString(filter);   //Filter wird durch isString ein valider String mitgegeben -> möglich : ein ISBN filter
    stringCut(filter);  //entfernt '\n' vom String damit der compare richtig läuft
    printf("- - - - - - - - - - -\n");
    //bei zu vielen Ergebnissen -> keine Ausgabe
    for (int i = 0;i < help.registered;i++ ) {                                  //Bücher mit gleichem Titel rausfiltern
        if(strncasecmp(filter, help.Books[i]->isbn_nr,strlen(filter)) == 0) {
            tmplib.registered++;
            tmplib.Books = safeRealloc(tmplib.Books, sizeof(book *) * tmplib.registered);
            tmplib.Books[j] = help.Books[i];
            count++;
            j++;
        }
    }
    if (count == 0) {
        searchAgain();
    }

    if ( count == 1 ) {
        printf("Buch Nr. (1) \n");
        //title
        printf("Titel :\t\t%s\n", tmplib.Books[0]->title);
        //author
        printf("Autor :\t\t%s\n", tmplib.Books[0]->author);
        //isbn_nr
        printf("ISBN :\t\t%s\n", tmplib.Books[0]->isbn_nr);
        //number of books
        printf("Exemplare :\t%d\n", tmplib.Books[0]->nob);
        printf("- - - - - - - - - - -\n");
        bookMenu(tmplib.Books[0]);
    }
    if( count > 1 ) {
        for ( int k = 0; k < tmplib.registered; k ++ ) {                 //print alle zutreffenden Bücher
            printf("Buch Nr. (%d) \n", k+1);
            //title
            printf("Titel :\t\t%s\n", tmplib.Books[k]->title);
            //author
            printf("Autor :\t\t%s\n", tmplib.Books[k]->author);
            //isbn_nr
            printf("ISBN :\t\t%s\n", tmplib.Books[k]->isbn_nr);
            //number of books
            printf("Exemplare :\t%d\n", tmplib.Books[k]->nob);
            printf("- - - - - - - - - - -\n");
        }
        printf("Welches Buch wollen Sie auswaehlen?\nAuswahl: \n");             //welches der passenden Bücher wird ausgewählt
        int h;
        h = isNumber();
        bookMenu(tmplib.Books[h-1]);
    }
}

void askForBook(char *title,char *author,char *isbn, int *nob) {
    //title
    printf("\nWie ist der Titel des Buches?\n(max.100 Zeichen)\n");
    isString(title);    //returns title string if valid
    //author
    printf("\nWer ist der Autor des Buches?\n(max.100 Zeichen)\n");
    isString(author);   //return author string if valid
    //isbn_nr
    printf("\nWas ist die ISBN-Nr?\n(muss gueltig sein)\n");
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
    book *bookPtr1; //Hilfspointer
    book *bookPtr2; //Hilfspointer
    if( lib1.registered == 1 ) {        //bei einem Buch löscht es das erste
        free(lib1.Books[ 0 ]);
        lib1.registered --;
        lib1.Books = safeRealloc(lib1.Books, 0);
    }
    if (lib1.registered == 2 ) {
        int i = delete->id;
        if ( i == lib1.registered-1 ) {
            lib1.registered--;
            lib1.Books = safeRealloc(lib1.Books, sizeof(book *) * lib1.registered);
        }
        else {
            bookPtr1 = lib1.Books[i];
            bookPtr2 = lib1.Books[i+1];
            lib1.Books[i] = bookPtr2;
            lib1.registered--;
            lib1.Books = safeRealloc(lib1.Books, sizeof(book *) * lib1.registered);
            free(bookPtr1);
        }
    }
    if( lib1.registered > 2 ) {         //bei mehreren Bücher
        int i = delete->id;
        if (i == lib1.registered-1) {
            lib1.registered--;
            lib1.Books = safeRealloc(lib1.Books, sizeof(book *) * lib1.registered);
        }
        else {
            bookPtr1 = lib1.Books[ i ];     //bookPtr1 = das Element, das gelöscht werden soll
            for ( int j = i; j < lib1.registered - 2; j ++ ) {      //die Pointer von den Büchern wandern vor
                bookPtr2 = lib1.Books[ j + 1 ];                     //bis sie das letzte in das vorletzte Feld
                lib1.Books[ j ] = bookPtr2;                         //schieben
            }
            bookPtr2 = lib1.Books[ lib1.registered - 1 ];
            lib1.Books[ lib1.registered - 2 ] = bookPtr2;
            free(bookPtr1);                     //das zu löschende Element wird gefreed
            lib1.registered --;                      // Ein buch weniger
            lib1.Books = safeRealloc(lib1.Books, sizeof(book *) * lib1.registered);     //Speicher der lib anpassen
        }
    }
    printf("Das Buch wurde erfolgreich geloescht.\n\n");
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

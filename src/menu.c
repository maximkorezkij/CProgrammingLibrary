#ifndef PROJECTS_MENU_C
#define PROJECTS_MENU_C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/func.h"
#include "../include/main.h"
#endif

lib lib1 = {};

void showMenu() {
    printf("Was wollen Sie anzeigen ?\n");
    printf("\t(1) Nach dem Titel suchen\n");
    printf("\t(2) Nach der ISBN-Nr suchen\n");
    printf("\t(3) Alle anzeigen\n");
    printf("\t(4) Verlassen\n");
    printf("\nAuswahl: \n");
    int e;
    e = isNumber();
    switch (e) {
        case 1:
            showByTitle(lib1);
            break;
        case 2:
            showByIsbn(lib1);
            break;
        case 3:
            show(lib1);
            break;
        case 4:
            return;
        default:
            printf("Falsche Eingabe\n");
            break;
    }
}
void searchMenu() {
    if( lib1.registered == 0 ) {
        printf("Es gibt aktuell keine Bücher zum suchen.\n");
        return;
    }
    if( lib1.registered > 0 ) {
        printf("\t(1) Nach dem Titel suchen\n");
        printf("\t(2) Nach der ISBN-Nr suchen\n");
        printf("\t(3) Verlassen\n");
        printf("\nAuswahl: \n");
        int e;
        e = isNumber();
        switch (e) {
            case 1:
                searchByTitle(lib1);
                break;
            case 2:
                //searchByIsbn(lib1);
                break;
            case 3:
                return;
            default:
                printf("Falsche Eingabe\n");
                break;
        }
    }
}


void goOn() {
    printf("\n\nZurück ins Hauptmenue?\n");
    printf("\t(1) Ja\n");
    printf("\t(2) Verlassen\n");
    printf("\nAuswahl: \n");
    int e;
    e = isNumber();
    switch (e) {
        case 1:
            return;
        case 2:
            exit(0);
        default:
            printf("Eingabe ungültig\n");
            break;
    }
}
void mainMenu() {
    while ( 1 ) {
        printf("\n\n                                                \n");
        printf("             ________________| ||____               \n");
        printf("            /__/__/__/__/__/__/__/__/\\             \n");
        printf("           /__/__/__/__/__/__/__/__/ \\             \n");
        printf("           #---------------------# _ |              \n");
        printf("           # (1) Buch hinzufügen #|| |              \n");
        printf("           #---------------------#   |              \n");
        printf("           # (2) Buch ausleihen  # _ |              \n");
        printf("           #---------------------#|| |              \n");
        printf("           # (3) Buch löschen    #|| |              \n");
        printf("           #---------------------#   |              \n");
        printf("           # (4) Buch suchen     # _ |              \n");
        printf("           #---------------------#|| |  ( `´`´),    \n");
        printf("           # (5) Bücher anzeigen #   | ( `   ´  )   \n");
        printf("           #---------------------# _ |  ( `, /. )   \n");
        printf("           # (6) Verlassen       #|| |   \   /      \n");
        printf("           #-----------__--------#  /     | |       \n");
        printf("           #  |_|_|   | _|   |_| # /      | |       \n");
        printf("___________#----------|__|-------#/__,,_,// \\_,,,,_\n");
        printf("             Bücher gesamt :  %d                    \n",lib1.registered);
        printf("____________________________________________________\n");

        printf("\n\n\n");

        printf("Auswahl: \n");
        int e;
        e = isNumber();

        switch (e) {
            case 1:
                printf("\n\n");
                printf("Sie wollen ein Buch hinzufügen.\n");
                addBookSorted();
                saveBooks();
                loadBooks();
                goOn();
                break;
            case 2:
                printf("Wie wollen Sie suchen ?\n");
                searchMenu();
                //rentBook -> Mai füg das richtig ein pls
                break;
            case 3:
                printf("Welches Buch wollen Sie loeschen?\n");
                searchMenu();
                break;
            case 4:
                showMenu();
                goOn();
                break;
            case 5:
                show(lib1);
                goOn();
                break;
            case 6:
                bye();
                exit(0);
            default:
                printf("Falsche Eingabe\n");
                break;
        }
    }
}

void bookMenu(book *help) {
    printf("\n");
    printf("    ,   ,  \n");
    printf("   /////|  \n");
    printf("  ///// |  Titel :\t\t%s\n", help->title);
    printf(" |~~~|  |  \n");
    printf(" |===|  |  Author :\t\t%s\n", help->author);
    printf(" |   |  |  \n");
    printf(" |   |  |  ISBN :\t\t%s\n", help->isbn_nr);
    printf(" |   | /   \n");
    printf(" |===|/    Exemplare :\t%d\n", help->nob);
    printf(" '---'     \n");
    printf("- - - - - - - - - - - - - - - -\n");
    printf("Was wollen Sie machen?\n");
    printf("\t(1) Buch ausleihen\n");
    printf("\t(2) Buch zurückgeben\n");
    printf("\t(3) Buch löschen\n");
    printf("\t(4) Zurück zum Hauptmenü\n");
    while (1) {
        int e;
        e = isNumber();

        switch (e) {
            case 1:
                //rentBook
                goOn();
                break;
            case 2:
                //returnBook
                goOn();
                break;
            case 3:
                deleteRequest(help);
                return;
            case 4:
                return;
            default:
                printf("Eingabe ungültig\n");
                break;
        }
    }
}

void deleteRequest(book *delete) {
    printf("\nWollen Sie das Buch wirklich löschen?\n");
    printf("\t(1) Ja\n");
    printf("\t(2) abbrechen\n");
    while(1) {
        int h;
        h = isNumber();
        switch(h) {
            case 1:
                deleteBook(delete);
                printf("Aenderung wird gespeichert.\n Einen Moment bitte...\n");
                saveBooks();
                loadBooks();
                printf("\nEs wurde erfolgreich gespeichert.\n");
                return;
            case 2:
                return;
            default:
                printf("Eingabe ungültig\n");
                break;
        }
    }
}
void bye() {

    printf(" _                    _               \n");
    printf("| |__    ___    ___  | | __ ___       \n");
    printf("|  _ \\  / _ \\  / _ \\ | |/ // __|   \n");
    printf("| |_) || (_) || (_) ||   < \\__ \\    \n");
    printf("|____/  \\___/  \\___/ |_|\\_\\\\___/ \n");
    //Ausgabe "books" in ASCII Art

    printf("\n");
    printf("Danke fuer Ihren Besuch!");
    printf("\n\n");

}
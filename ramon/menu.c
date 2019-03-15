#ifndef PROJECTS_MENU_C
#define PROJECTS_MENU_C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/func.h"
#include "../inc/main.h"
#endif

lib lib1 = {};
void deleteMenu() {
    printf("Welches buch wollen Sie loeschen?\n");
    printf("\t(1) Nach dem Titel suchen\n");
    printf("\t(2) Nach der ISBN-Nr filtern\n");
    printf("\t(3) Verlassen\n");
    printf("\nAuswahl: ");
    int e;
    e = isNumber();
    switch (e) {
        case 1:
            //nach titel suchen
            break;
        case 2:
            //nach isbn filtern
            break;
        case 3:
            return;
        default:
            printf("Falsche Eingabe\n");
            system("cls");              //system cls funktioniert nur auf windows
            break;
    }
}

void showMenu() {
    printf("Wie wollen Sie suchen ?\n");
    printf("\t(1) Nach dem Titel suchen\n");
    printf("\t(2) Nach der ISBN-Nr suchen\n");
    printf("\t(3) Verlassen\n");
    printf("\nAuswahl: ");
    int e;
    e = isNumber();
    switch (e) {
        case 1:
            showByTitle(lib1);
            goOn();
            break;
        case 2:
            showByIsbn(lib1);
            goOn();
            break;
        case 3:
            mainMenu();
            break;
        default:
            printf("Falsche Eingabe\n");
            break;
    }
}
void searchMenu() {
    printf("Wie wollen Sie suchen ?\n");
    printf("\t(1) Nach dem Titel suchen\n");
    printf("\t(2) Nach der ISBN-Nr suchen\n");
    printf("\t(3) Verlassen\n");
    printf("\nAuswahl: ");
    int e;
    e = isNumber();
    switch (e) {
        case 1:
            searchByTitle(lib1);
            goOn();
            break;
        case 2:
            //searchByIsbn(lib1);
            goOn();
            break;
        case 3:
            return;
        default:
            printf("Falsche Eingabe\n");
            break;
    }
}


void goOn() {
    printf("\n\nWollen sie weitermachen?\n");
    printf("\t(1) Ja\n");
    printf("\t(2) Nein\n");
    printf("\nAuswahl: ");
    int e;
    e = isNumber();
    switch (e) {
        case 1:
            return;
            break;
        case 2:
            exit(0);
            break;
        default:
            printf("Eingabe ungueltig\n");
            break;
    }
}
void mainMenu() {
    while ( 1 ) {
        printf("\n\n                                                   \n");
        printf("             ________________| ||____                  \n");
        printf("            /__/__/__/__/__/__/__/__/\\                \n");
        printf("           /__/__/__/__/__/__/__/__/ \\                \n");
        printf("           #----------------------#   |                \n");
        printf("           # (1) Buch hinzufuegen # _ |                \n");
        printf("           #----------------------#|| |                \n");
        printf("           # (2) Buch ausleihen   #   |                \n");
        printf("           #----------------------# _ |                \n");
        printf("           # (3) Buch loeschen    #|| |                \n");
        printf("           #----------------------#   |                \n");
        printf("           # (4) Buch suchen      # _ |                \n");
        printf("           #----------------------#|| |  ( `´`´),      \n");
        printf("           # (5) Buecher anzeigen #   | ( `   ´  )     \n");
        printf("           #----------------------# _ |  ( `, /. )     \n");
        printf("           # (6) Verlassen        #|| |   \\\   /      \n");
        printf("           #-----------__---------#  /     | |         \n");
        printf("           #  |_|_|   | _|   |_|  # /      | |         \n");
        printf("___________#----------|__|--------#/__,,_,// \\\\_,,,,_\n");
        printf("             Buecher gesamt :  %d                      \n",lib1.registered);
        printf("_______________________________________________________\n");

        printf("\n\n\n");

        printf("Auswahl: ");
        int e;
        e = isNumber();

        switch (e) {
            case 1:
                printf("\n\n");
                printf("Sie wollen ein Buch hinzufuegen.\n");
                addBookSorted();
                saveBooks();
                loadBooks();
                goOn();
                break;
            case 2:
                searchMenu();
                //rentBook -> Mai füg das richtig ein pls
                goOn();
                break;
            case 3:
                deleteMenu();
                saveBooks();
                loadBooks();
                goOn();
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
                break;
            default:
                printf("Falsche Eingabe\n");
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

void bookArt(){

                printf("\n");
                printf("    ,   ,  \n");
                printf("   /////|  \n");
                printf("  ///// |  \n");
                printf(" |~~~|  |  \n");
                printf(" |===|  |  \n");
                printf(" |   |  |  \n");
                printf(" |   |  |  \n");
                printf(" |   | /   \n");
                printf(" |===|/    \n");
                printf(" '---'     \n\n");
                //Ausgabe eines Buches in ASCII ART
}

void glasses(){
    printf("        _,--,            _     \n");
    printf("   __,-'____| ___      /' |    \n");
    printf(" /'   `\\,--,/'   `\\  /'   |  \n");
    printf("(       )  (       )'          \n");
    printf(" \\_   _/'  `\\_   _/          \n");
    printf("   '''        '''              \n");
    //displays a glasses in ASCII Art
}

void bookMenu(book *help) {
    //Titel
    printf("\nTitel :\t\t%s", help->title);
    //Author
    printf("\nAuthor :\t%s", help->author);
    //ISBN
    printf("\nISBN :\t\t%s", help->isbn_nr);
    //Number of Books
    printf("\nExemplare :\t%d\n", help->nob);
    printf("- - - - - - - - - - -");
    printf("Was wollen Sie machen?\n");
    printf("\t(1) Buch ausleihen");
    printf("\t(2) Buch loeschen");
    printf("\t(3) Zurueck zum Hauptmenue");
    while (1) {
        char e = (char) getchar();

        switch (e) {
            case 1:
                //rentBook
                goOn();
                break;
            case 2:
                //deleteBook
                goOn();
                break;
            case 3:
                return;
            default:
                printf("Eingabe ungueltig\n");
                break;
        }
    }
}

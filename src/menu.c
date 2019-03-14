#include <stdio.h>
#include <stdlib.h>
#include "../include/func.h"

void deleteMenu() {
    printf("Welches buch wollen Sie löschen?\n");
    printf("\t(1) Nach dem Titel suchen\n");
    printf("\t(2) Nach der ISBN-Nr filtern\n");
    printf("\t(3) Verlassen\n");
    printf("\nAuswahl: ");
    char e = (char) getchar();

    switch (e) {
        case '1':
            //nach titel suchen
            break;
        case '2':
            //nach isbn filtern
            break;
        case '3':
            mainMenu();
            break;
        default:
            printf("Falsche Eingabe\n");
            system("cls");              //system cls funktioniert nur auf windows
            break;
    }
}

void searchMenu() {
    printf("Wie wollen Sie suchen ?\n");
    printf("\t(1) Nach dem Titel suchen\n");
    printf("\t(2) Nach der ISBN-Nr suchen\n");
    printf("\t(3) Verlassen\n");
    printf("\nAuswahl: ");
    char e = (char) getchar();

    switch (e) {
        case '1':
            showByTitle();
            goOn();
            break;
        case '2':
            showByIsbn();
            goOn();
            break;
        case '3':
            mainMenu();
            break;
        default:
            printf("Falsche Eingabe\n");
            system("cls");              //system cls funktioniert nur auf windows
            break;
    }
}

void goOn() {
    printf("\n\nWollen sie weitermachen?\n");
    printf("\t(1) Ja\n");
    printf("\t(2) Nein\n");
    printf("\nAuswahl: ");
    char e = (char) getchar();

    switch (e) {
        case '1':
            mainMenu();
            break;
        case '2':
            break;
        default:
            printf("Falsche Eingabe\n");
            system("cls");              //system cls funktioniert nur auf windows
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
        printf("           # (1) Buch ausleihen  #|| |              \n");
        printf("           #---------------------#   |              \n");
        printf("           # (2) Buch hinzufügen # _ |              \n");
        printf("           #---------------------#|| |  ( `´`´),    \n");
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
        printf("____________________________________________________\n");
        printf(" # Ihre Eingabe bitte: ");

        printf("\n\n\n");

        printf("Auswahl: ");
        char e = (char) getchar();

        switch (e) {
            case '1':
                //rentBook -> Mai füg das richtig ein pls
                break;
            case '2':
                printf("\n\n");
                printf("Sie wollen ein Buch hinzufügen.\n");
                addBookSorted();
                goOn();
                break;
            case '3':
                deleteMenu();
                break;
            case '4':
                searchMenu();
                break;
            case '5':
                show();
                goOn();
                break;
            case '6':
                break;
            default:
                printf("Falsche Eingabe\n");
                system("cls");
                break;
        }
    }
}


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include "../include/main.h"

const char *stringCut(char *buffer) {
    buffer[ strcspn(buffer, "\n") ] = 0;
    return buffer;
}

bool validISBN(char *isbn) {
    // length must be 10
    int n = strlen(isbn);
    if ( n != 10 )
        return false;
    // sum of first 9 digits
    int sum = 0;
    for ( int i = 0; i < 9; i++ ) {
        int digit = isbn[ i ] - '0';
        if ( 0 > digit || 9 < digit )
            return false;
        sum += (digit * (10 - i));
    }
    // Checking last digit
    char last = isbn[ 9 ];
    if ( last != 'X' && (last < '0' || last > '9'))
        return false;
    // If last digit is 'X', add 10 to sum, else add its value.
    sum += ((last == 'X') ? 10 : (last - '0'));
    // Return true if sum is divisible by 11
    return (sum % 11 == 0);
}

book *newBook(char *newtitle, char *newauthor, char *newisbn, int newnob) {
    book newBook;

    newBook.title = malloc(sizeof(newtitle));
    strcpy(newBook.title, newtitle);

    newBook.author = malloc(sizeof(newauthor));
    strcpy(newBook.author, newauthor);

    newBook.isbn_nr = malloc(sizeof(newisbn));
    strcpy(newBook.isbn_nr, newisbn);

    newBook.nob = newnob;

    newBook.r_list;

    //rückgabe als pointer
    book *bookPtr = malloc(sizeof(book));
    //title
    bookPtr->title = malloc(strlen(newBook.title) + 1);
    strcpy(bookPtr->title, newBook.title);
    //author
    bookPtr->author = malloc(strlen(newBook.author) + 1);
    strcpy(bookPtr->author, newBook.author);
    //isbn nr
    bookPtr->isbn_nr = malloc(strlen(newBook.isbn_nr) + 1);
    strcpy(bookPtr->isbn_nr, newBook.isbn_nr);
    //number of books
    bookPtr->nob = newBook.nob;
    //ausleiherliste
    bookPtr->r_list;
    return bookPtr;
}

int isNumber() {
    char var[10];    //our number of books
    int i = 0;       //help
    int varisnum = 0;    //varisnum:  1 for yes, 0 for no -> function from

    fgets(var,10,stdin);    //get string

    if ( strlen(var) > 9 ) {
        printf("Eingabe zu lang. Maximal 10-stellige Zahlen\n");
        return isNumber();
    }
    if ( var[0] == '\n' || var[0] == ' ') {
        printf("Eingabe ist ungültig. Bitte geben Sie eine Zahl ein.\n");
    }
    while ( isalnum(var[ i ]) != 0 ) {    //loop until notnumeric character appears
        if ( isdigit(var[ i ]) != 0 ) {
            varisnum = 1;
        }else {
            varisnum = 0;
            break;    //non-numeric character -> break
        }
        i++;
    }

    if ( varisnum == 0 ) {
        return isNumber();      //start again
    }else {
        int num = atoi(var);    //convert valid number string into int
        return num;             //return int
    }
}

const char *isbnNumber(char *isbn) {
    fgets(isbn, MAX, stdin);    //get ISBN string
    stringCut(isbn);            //cut \n from string
    if ( validISBN(isbn) == false ) {
        printf("Diese ISBN-Nr ist ungueltig. Versuchen Sie es erneut:\n");
        return isbnNumber(isbn);    //start again
    }else {
        return isbn;        //return valid isbn as string
    }
}
const char *isString(char *string) {
    fgets(string, MAX, stdin);  //get string
    if (string[0] == '\n' || string[0] == ' ' || string[0] == '\0') {   //validators
        printf("Eingabe ist ungültig. Versuchen Sie es erneut.\n");
        return isString(string);    //start again
    }
    else {
        return string;      //return valid string
    }
}

void addBook() {
    lib1.registered++;
    lib1.Books = realloc(lib1.Books, sizeof(book *) * lib1.registered);
    //titel
    printf("Wie ist der Titel des Buches ?\n(max.100 Zeichen)\n");
    char title[MAX] = {};
    isString(title);    //returns title string if valid
    //author
    printf("\nWer ist der Author des Buches ?\n(max.100 Zeichen)\n");
    char author[MAX] = {};
    isString(author);   //return author string if valid
    //isbn
    printf("\nWas ist die ISBN-Nr ?\n(muss gueltig sein)\n");
    char isbn[MAX] = {};
    isbnNumber(isbn);
    //number of books
    printf("\nWie viele Exemplare gibt es?\n(Nur Zahlen)\n");
    int nob = isNumber();
    //remove \n from strings
    stringCut(author);
    stringCut(title);

    lib1.Books[ lib1.registered - 1 ] = newBook(title, author, isbn, nob);
}

void saveBooks(FILE *ptr) {
    size_t length = 0;
    ptr = fopen("saves.b", "wb");
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

off_t fsize(const char *filename) {     //funktion die checkt ob ein file leer ist
    struct stat st;

    if ( stat(filename, &st) == 0 )
        return st.st_size;

    return -1;
}

void loadBooks(FILE *ptr) {
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

void show(FILE *ptr) {
//    FILE *fptr;
    loadBooks(ptr);
    printf("\nAnzahl Bücher : \t%d\n", lib1.registered);
    printf("- - - - - - - - - - -");
    for ( int i = 0; i < lib1.registered; i++ ) {
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

//ramón
//void mainMenu(){
//    
//    while (1){
//        
//        printf("(1) Buch anlegen\n");
//        printf("(2) Buch loeschen\n");
//        printf("(3) Buch suchen\n");
//        printf("(4) Exit\n");
//
//        printf("Auswahl: ");
//        char e = getchar();
//
//        switch (e){
//            case '1':
//                addBook();
//                break;
//            case '2':
//                //deleteBook();
//                break;
//            case '3':
//                showByIsbn();
//                break;
//            case '4':
//                saveBooks();
//                return 0;
//            default:
//                printf("Falsche Eingabe\n");
//                system("cls");
//                break;
//        }
//    }
//}

//int main() {
    //mainMenu();
//}

struct Buch{
char Name[200];
};
struct Buch testbuch;

void mainMenu(){
    while(1)
    {
        // Hauptmenue
        printf("\n\n                                                \n");
        printf("             ________________| ||____               \n");
        printf("            /__/__/__/__/__/__/__/__/\\             \n");
        printf("           /__/__/__/__/__/__/__/__/ \\             \n");
        printf("           #---------------------# _ |              \n");
        printf("           # (1) Buch anlegen    #|| |              \n");
        printf("           #---------------------#   |              \n");
        printf("           # (2) Buch loeschen   # _ |              \n");
        printf("           #---------------------#|| |  ( `´`´),    \n");
        printf("           # (3) Buch suchen     #   | ( `   ´  )   \n");
        printf("           #---------------------# _ |  ( `, /. )   \n");
        printf("           # (4) Verlassen       #|| |   \   /      \n");
        printf("           #-----------__--------#  /     | |       \n");
        printf("           #  |_|_|   | _|   |_| # /      | |       \n");
        printf("___________#----------|__|-------#/__,,_,// \\_,,,,_\n");
        printf("____________________________________________________\n");
        printf(" # Ihre Eingabe bitte: ");

        printf("\n\n\n");

//    while (1){
//        system("cls");
//        printf("(1) Buch anlegen\n");
//        printf("(2) Buch loeschen\n");
//        printf("(3) Buch suchen\n");
//        printf("(4) Exit\n");
//
        printf("Auswahl: ");
        char e = getchar();

        switch (e){
            case '1':
                printf("Gebe Name ein: \n");
                char str[80];
                scanf("%s", str);
                strcpy(testbuch.Name,str);
                system("PAUSE");
                break;
            case '2':
                printf("weg damit\n");
                strcpy(testbuch.Name,"");
                system("PAUSE");
                break;
            case '3':
                printf("Hab das buch gefunden\n");
                printf(testbuch.Name);
                printf("\n");
                system("PAUSE");
                break;
            case '4':
                return 0;
            default:
                printf("Falsche Eingabe\n");
                system("cls");
                break;
        }
    }

}

//int main() {
//    mainMenu();
//}


//end-ramón


void showByIsbn() {
    char filter[10] = {};
    int count;
    printf("\nFiltern nach ISBN:\n");
    isString(filter);   //filter with valid string
    for ( int i = 0; i < lib1.registered; i++ ) {
        if (strncasecmp(filter,lib1.Books[i]->isbn_nr,strlen(filter)) == 0) {
            //Titel
            printf("\nTitel :\t\t%s", lib1.Books[ i ]->title);
            //Author
            printf("\nAuthor :\t%s", lib1.Books[ i ]->author);
            //ISBN
            printf("\nISBN :\t\t%s", lib1.Books[ i ]->isbn_nr);
            //Number of Books
            printf("\nExemplare :\t%d\n", lib1.Books[ i ]->nob);
            printf("- - - - - - - - - - -");
            count += 1;
        }
    }
    printf("%d",count);
}

void rentBook() {
    book *bPtr = ;//gesuchtes buch
    //Buch aufgerufen und angezeigt
    char var; //Antwortsvariable
    char name[MAX] = {};
    int h = 0; //Hilfsvariable
    bool b = true; //Hilfsvariable
    printf("\nBuch ausleihen? \nJa[1] \nNein[2]");
    fgets(var, 1, stdin); //Einlesen von antwort
    if (var=='1'){
        printf("\n Verfügbarkeit wird geprüft.");
        if(bPtr->nob > 0){
            printf("\nBuch verfügbar. ");
            printf("\nName eingeben (Nachname, Vorname)");
            isString(name);
            bPtr->nob -= 1; //Exemplarzahl um 1 reduziert
            while(b)
            {
                if(bPtr->r_list[h][0] == ' ' || bPtr->r_list[h][0] =='\0'){
                    bPtr->r_list[h][0] = name; //Name wird in Liste eingetragen
                    printf("\nName wurde in Ausleihliste eingetragen. Vielen Dank.");
                    b = false;
                }
                h++;
            }
            mainMenu(); //zurück zum Menü
        }
        else{
            printf("\n Keine Exemplare mehr vorhanden.");
        }
    }
    else if (var=='2');
    else {
        printf("\nungültige Eingabe.");
        rentBook();
    }
}

void returnBook(){
    
}

int main() {
    //loadBooks als gegensatz zu saveBooks
    FILE *load;
    load = fopen("saves.b", "rb");
    printf("1\n");
    loadBooks(load);
    printf("2\n");
    addBook();//fügt ein Buch hinzu
    printf("3\n");
    saveBooks(load);//speichert alle Bücher in einer binärdatei -> beim exit
    printf("4\n");
    FILE *s;
    s = fopen("saves.b", "rb");
    show(s);
    printf("5");
    showByIsbn();
    return 0;
}


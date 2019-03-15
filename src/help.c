#ifndef PROJECTS_HELP_C
#define PROJECTS_HELP_C
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#define Max 100
#endif
const char *stringCut(char *buffer) {
    buffer[ strcspn(buffer, "\n") ] = 0;
    return buffer;
}

bool validISBN(char *isbn) {
    size_t n = strlen(isbn);
    if ( n != 10 )          //länge einer isbn nr muss 10 sein
        return false;
    int sum = 0;            //summer der ersten 9 ziffern mal 10 minus anzahl der gezählten ziffer
    for ( int i = 0; i < 9; i++ ) {
        int digit = isbn[ i ] - '0';
        if ( 0 > digit || 9 < digit )
            return false;
        sum += (digit * (10 - i));
    }
    char last = isbn[ 9 ];
    if ( last != 'X' && (last < '0' || last > '9'))     //letze Ziffer darf auch 'X' sein
        return false;
    sum += ((last == 'X') ? 10 : (last - '0'));     //addiere für X 10 und sonst die ziffer
    return (sum % 11 == 0);         //valide Isbn wenn alles durch 11 teilbar ist
}

int isNumber() {
    char var[10];    //our number of books
    fgets(var, 10, stdin);    //get string
    //if wrong input strtol returns 0
    if( strtol(var,NULL,10) == 0 ) {
        return isNumber();
    }
    else
        return (int) strtol(var,NULL,10);
}

const char *isbnNumber(char *isbn) {
    fgets(isbn, Max, stdin);    //get ISBN string
    stringCut(isbn);            //cut \n from string
    if ( validISBN(isbn) == false ) {
        printf("Diese ISBN-Nr ist ungueltig. Versuchen Sie es erneut:\n");
        return isbnNumber(isbn);    //start again
    }else {
        return isbn;        //return valid isbn as string
    }
}

const char *isString(char *string) {
    fgets(string, Max, stdin);  //get string
    if (string[0] == '\n' || string[0] == ' ' || string[0] == '\0') {   //validators
        printf("Eingabe ist ungültig. Versuchen Sie es erneut.\n");
        return isString(string);    //start again
    }
    else {
        return string;      //return valid string
    }
}

off_t fsize(const char *filename) {     //funktion die checkt ob ein file leer ist
    struct stat st;

    if ( stat(filename, &st) == 0 )
        return st.st_size;

    return -1;
}
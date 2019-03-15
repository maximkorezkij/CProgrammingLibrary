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
    // length must be 10
    size_t n = strlen(isbn);
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
        return isNumber();
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
        printf("Eingabe ist ungültig. Bitte geben Sie eine Zahl ein.\n");
        return isNumber();      //start again
    }else {
        int num = (int) strtol(var, NULL, 10);    //convert valid number string into int
        return num;             //return int
    }
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
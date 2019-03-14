#ifndef PROJECT_MAIN_H
#define PROJECT_MAIN_H
#define Max 100
typedef struct Book {       //ausleihliste fehlt noch
    char *title;
    char *author;
    char *isbn_nr;
    int nob;
    char r_list[][Max];
}book;

typedef struct Lib {
    book **Books;
    int registered;
}lib;

extern lib lib1;
#endif
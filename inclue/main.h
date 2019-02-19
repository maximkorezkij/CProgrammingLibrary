typedef struct Book {       //ausleihliste fehlt noch
    char title[50];
    char author[50];
    int isbn_nr;
    int nob;
}book;

typedef struct Lib {
    book **Books;
    int registered;
}lib;

lib lib1 = {};

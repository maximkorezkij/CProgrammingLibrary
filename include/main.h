#define MAX 100

typedef struct Book {       //ausleihliste fehlt noch
    char *title;
    char *author;
    char *isbn_nr;
    int nob;
}book;

typedef struct Lib {
    book **Books;
    int registered;
}lib;

lib lib1 = {};
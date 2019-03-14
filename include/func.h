#ifndef PROJECT_FUNC_H
#define PROJECT_FUNC_H
int isNumber();
off_t fsize(const char *filename);
const char *stringCut(char *buffer);
const char *isString(char *string);
const char *isbnNumber(char *isbn);
bool validISBN(char *isbn);
book *newBook(char *newtitle, char *newauthor, char *newisbn, int newnob);
void addBook();
void saveBooks();
void loadBooks();
void show();
void showByIsbn();
void showByTitle();
void rentBook();
void moveBooks(int i);
void addBookSorted();
void mainMenu();
#endif //PROJECT_FUNC_H

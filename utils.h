#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

char strBuffer[501];
char operativeSystem;

void clearInputBuffer();
int* readInt(int *ptr);
int isInt(int *ptr);
void chooseSO();
void clearScreen();

char* readStr(char *ptr);
char* allocStr(char *dest, char *src);
char* concatStr(char *dest, char *src);
char* extendStr(char *str, int i);
char* addCharEnd(char *dest, char chr);
char* addnCharEnd(char *dest, char chr, int i);
char* addChar(char *dest, char chr);
char* addnChar(char *dest, char chr, int i);

#endif /* UTILS_H_INCLUDED */

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED


// I/O
void clearInputBuffer();
void chooseSO();
void clearScreen();

// inteiros
int isUInt(unsigned int n);
int isInt(int n);
int maxInt(int a, int b);
int intcmp(int a, int b);
int uintcmp(unsigned int a, unsigned int b);

// double
int isDouble(double n);

// strings
char* allocStr(char *dest, char *src);
char* concatStr(char *dest, char *src);
char* extendStr(char *str, int i);
char* addCharEnd(char *dest, char chr);
char* addnCharEnd(char *dest, char chr, int i);
char* addChar(char *dest, char chr);
char* addnChar(char *dest, char chr, int i);

#endif /* UTILS_H_INCLUDED */

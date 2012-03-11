#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

char strBuffer[501];
char operativeSystem;

void clearInputBuffer();
char* readStr(char *ptr);
char* allocStr(char *ptr);

void readInt(int *ptr);

void chooseSO();
void clearScreen();

#endif /* UTILS_H_INCLUDED */

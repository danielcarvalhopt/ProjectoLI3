#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

char* menu_Asterisk(char *acum, char *ptacum, int *left);
char* menu_Line(char *acum, char *ptacum, int *left, char *src, int lpos);
char* menu_Header(char *acum, char *ptacum, int *left);
void menu(int *input);

#endif /* MENU_H_INCLUDED */


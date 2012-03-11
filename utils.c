#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void clearInputBuffer(){
	scanf("%*[^\n]");
	scanf("%*c");
}

char* readStr(char *ptr){
	scanf("%500[^\n]", strBuffer); clearInputBuffer();
	return allocStr(ptr, strBuffer);
}

char* allocStr(char *dest, char *src){
	if( (dest = malloc(strlen(src) + 1)) == NULL ){
		printf("Out of memory\n");
		return NULL;
	}
	strcpy(dest, src);
	return dest;
}

void readInt(int *ptr){
	scanf("%d[^\n]",ptr);
	clearInputBuffer();
}

void chooseSO(){
	if( system("cls") ){
		system("clear");
		operativeSystem = 1; // Linux, Unix...
	}else
		operativeSystem = 2; // Windows
}

void clearScreen(){
	if( operativeSystem != 1 && operativeSystem != 2 )
		chooseSO();
	else
		if( operativeSystem == 1 )
			system("clear");
		else
			system("cls");
}

void concatStr(char *dest, char *src){
	dest = realloc( dest, (strlen(dest) + strlen(src) + 1) );
    strcat(dest,src);
}

/*int main ()
{
	char *str = NULL;
	printf("Escreva coisas até 500 caracteres\n>>");
	str = readStr(str);
	printf("\nMuito bem, o que escreveu foi:\n%s",str);

	return 0;
}*/

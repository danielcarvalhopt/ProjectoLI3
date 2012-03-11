#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void clearInputBuffer(){
	scanf("%*[^\n]");
	scanf("%*c");
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

int* readInt(int *ptr){
	scanf("%d[^\n]",ptr);
	clearInputBuffer();
	return ptr;
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

char* concatStr(char *dest, char *src){
	if( (dest = realloc( dest, (strlen(dest) + strlen(src) + 1) )) == NULL ){
		printf("Out of memory");
		return NULL;
	}
    strcat(dest,src);
    return dest;
}

char* extendStr(char *str, int i){
	if( (str = realloc( str, (strlen(str) + i + 1) )) == NULL ){
		printf("Out of memory");
		return NULL;
	}
	return str;
}

char* addCharEnd(char *dest, char *chr){
	while(dest != '\0') dest++;
	*(dest) = *chr;
	*(dest+1) = '\0';
	return (dest+1);
}

char* addnCharEnd(char *dest, char *chr, int i){
	if( i > 0 ){
		while(dest != '\0') dest++;
		for(;i>0;i--){
			*dest = *chr;
			dest++;
		}
		*dest = '\0';
	}
	return dest;
}

char* addChar(char *dest, char *chr){
	*(dest+1) = *chr;
	*(dest+2) = '\0';
	return (dest+2);
}

char* addnChar(char *dest, char *chr, int i){
	for(;i>0;i--){
		*dest = *chr;
		dest++;
	}
	*dest = '\0';
	return dest;
}

/*int main ()
{
	char *str = NULL;
	printf("Escreva coisas até 500 caracteres\n>>");
	str = readStr(str);
	printf("\nMuito bem, o que escreveu foi:\n%s",str);

	return 0;
}*/

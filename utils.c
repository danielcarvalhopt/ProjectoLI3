#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "utils.h"

void clearInputBuffer(){
	char c;
	while( (c=getchar()) != '\n' );
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

int readInt(){
	char c;
	int sinal=1, res=0;
	c=getchar();
	switch(c){
		case '-': sinal = -1;
		case '+': c=getchar();
			  break;
	}
	while( c != '\n' && res != INT_MIN){
		if( c >= '0' && c <= '9' ){
			res = res*10 + c - '0';
			c = getchar();
		}else{
			res = INT_MIN;
			clearInputBuffer();
		}
	}
	if( res != INT_MIN )
		res *= sinal;
	return res;
}

int isInt(int n){
	return (n != INT_MIN) ? 1 : 0;
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

char* addCharEnd(char *dest, char chr){
	while(dest != '\0') dest++;
	*(dest) = chr;
	*(dest+1) = '\0';
	return (dest+1);
}

char* addnCharEnd(char *dest, char chr, int i){
	if( i > 0 ){
		while(dest != '\0') dest++;
		for(;i>0;i--){
			*dest = chr;
			dest++;
		}
		*dest = '\0';
	}
	return dest;
}

char* addChar(char *dest, char chr){
	*(dest) = chr;
	*(dest+1) = '\0';
	return (dest+1);
}

char* addnChar(char *dest, char chr, int i){
	for(;i>0;i--){
		*dest = chr;
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

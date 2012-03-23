#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#include "utils.h"

static char operativeSystem;

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



int isDouble(double n){
    if( isinf(n) || isnan(n) ) //verifica se n não é um número ou se representa a infinidade
        return 0;
    return 1;
}



int isUInt(unsigned int n){
	return (n != INT_MAX) ? 1 : 0;
}

int isInt(int n){
	return (n != INT_MAX) ? 1 : 0;
}

int maxInt(int a, int b){
    return a>=b ? a : b;
}

int uintcmp(unsigned int a, unsigned int b){
    if( a < b )
        return -1;
    else if( a > b )
        return 1;
    else
        return 0;
}

int intcmp(int a, int b){
    if( a < b )
        return -1;
    else if( a > b )
        return 1;
    else
        return 0;
}



char* allocStr(char *dest, char *src){
	if( (dest = malloc(strlen(src) + 1)) == NULL ){
		return NULL;
	}
	strcpy(dest, src);
	return dest;
}

char* concatStr(char *dest, char *src){
	if( (dest = realloc( dest, (strlen(dest) + strlen(src) + 1) )) == NULL ){
		//printf("Out of memory");
		return NULL;
	}
    strcat(dest,src);
    return dest;
}

char* extendStr(char *str, int i){
	if( (str = realloc( str, (strlen(str) + i + 1) )) == NULL ){
		//printf("Out of memory");
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


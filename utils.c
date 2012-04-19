/**
 * @file utils.c
 * @brief Definições estáticas do módulo de utilitários
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <time.h>

#include "utils.h"

static char operativeSystem; /**< Toma o valor 1 ou 2 consoante o sistema operativo em que o programa está a correr */

void clearInputBuffer(){
	char c;
	while( (c=getchar()) != '\n' );
}

void chooseSO(){
	if( system("cls") ){
		system("clear");
		operativeSystem = 1; // O programa está a correr em Linux, Unix, ...
	}else
		operativeSystem = 2; // O programa está a correr num sistema Windows
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

int putTime(char **str){
    time_t t;
    if( (*str = (char*)malloc(20*sizeof(char)) ) == NULL ) return 0;
    t = time(NULL);
    
    if( strftime( *str, 20, "%Y-%m-%d %H:%M:%S", localtime(&t) ) == 0 ){
        free(*str);
        return -1;
    }    
    return 1;
}



int isDouble(double n){
    if( isinf(n) || isnan(n) ) // verifica se n não é um número ou se representa a infinidade
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



char* allocStr(char *src){
    char *dest = NULL;
    if( (dest = (char*)malloc(strlen(src) + 1)) == NULL )
        return NULL;
    strcpy(dest, src);
    return dest;
}

char* concatStr(char *dest, char *src){
    if( (dest = (char*)realloc( dest, (strlen(dest) + strlen(src) + 1) )) == NULL )
        return NULL;
    strcat(dest,src);
    return dest;
}

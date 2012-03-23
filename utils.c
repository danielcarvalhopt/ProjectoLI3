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

unsigned int readUInt(){
	char c;
	unsigned int res=0;
	c=getchar();
	switch(c){
            case '+': c=getchar();
                      break;
	}
	while( c != '\n' && res != INT_MAX){
		if( c >= '0' && c <= '9' ){
			res = res*10 + c - '0';
			c = getchar();
		}else{
			res = INT_MAX;
			clearInputBuffer();
		}
	}
	return res;
}

double readDouble(){
    double res;
    char strBuffer[128];
    char strDouble[128];
    char *ps = &strBuffer[0];
    char *pd = &strDouble[0];
    char ponto = 0;

    
    fgets(strBuffer, 127, stdin);
    
    if( *ps == '+' || *ps == '-' ){
        *pd = *ps;
        ps++;pd++;
    }

    while( *ps != '\n' && *ps != '\0' && ponto != 2){
        if( *ps >= '0' && *ps <= '9' ){
            *pd = *ps;
            pd++;ps++;
        }else if( (*ps == ',' || *ps == '.') && ponto == 0 ){
            ponto = 1;
            *pd = '.';
            ps++;pd++;
        }else{
            ponto = 2;
        }
    }

    *pd = '\0'; //terminar a string do double
    
    if( ponto == 2 ) return NAN; //se o que foi lido nao for um numero, faz return NAN.
    
    sscanf(strDouble, "%lf", &res);
    return res;
}

int isDouble(double n){
    if( isinf(n) || isnan(n) ) //verifica se n não é um número ou se representa a infinidade
        return 0;
    return 1;
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
	while( c != '\n' && res != INT_MAX){
		if( c >= '0' && c <= '9' ){
			res = res*10 + c - '0';
			c = getchar();
		}else{
			res = INT_MAX;
			clearInputBuffer();
		}
	}
	if( res != INT_MAX )
		res *= sinal;
	return res;
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

char* readStr(char *ptr){
        char strBuffer[1024];
        fgets(strBuffer, 1023, stdin);
	return allocStr(ptr, strBuffer);
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

/*int main ()
{
	char *str = NULL;
	printf("Escreva coisas até 500 caracteres\n>>");
	str = readStr(str);
	printf("\nMuito bem, o que escreveu foi:\n%s",str);

	return 0;
}*/

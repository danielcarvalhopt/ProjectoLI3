#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cin(){
	scanf("%*[^\n]");
	scanf("%*c");
}


char* alocastring (char *pointer, char aux[])
{
	pointer=(char*)malloc((strlen(aux))*(sizeof(char)));
	strcpy (pointer, aux);
	return pointer;
}
/*
int main ()
{
	char *nome, aux[100];
	printf("Introduza um nome\n");
	scanf("%s", aux);
	nome=alocastring(nome, aux);
	printf("Nome:%s, tamanho: %lu\n",nome,strlen(nome));


	return 0;
}*/
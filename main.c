#include <stdio.h>
#include <string.h>
#include "utils.h"
//#include "menu.h"


char rodape[51] = "Programa iniciado";

int main(/*int argc, char **argv*/){
	
	char abc[50];
	strcpy(abc, "ola");
	printf("%s",abc);
	strcat(abc, "ole");
	printf("%s",abc);
	
	return 0;
}


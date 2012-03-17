#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "menu.h"


char rodape[51] = "Programa iniciado";

int main(/*int argc, char **argv*/){
	int input=0;
	while( input != -1 ){
		input = printMenu(input);
		switch(input){
			default: break;
		}
	}
	return 0;
}


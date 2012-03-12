#include <string.h>
#include <stdio.h>

#include "menu.h"
#include "utils.h"

#define CONSOLE_WIDTH 64
#define MENU_WIDTH 60

char* menu_Asterisk(char *acum, char *ptacum, int *left){
	char linha[CONSOLE_WIDTH+2];
	addChar( addnChar( linha, '*', CONSOLE_WIDTH ) , '\n');
	
	strcat(acum, linha);
	left -= (CONSOLE_WIDTH+1);
	ptacum += (CONSOLE_WIDTH+1);
	
	return ptacum;
}

char* menu_Space(char *acum, char *ptacum, int *left){
	char linha[CONSOLE_WIDTH+2];
	addChar( addnChar( linha, '*', CONSOLE_WIDTH ) , '\n');
	
	strcat(acum, linha);
	left -= (CONSOLE_WIDTH+1);
	ptacum += (CONSOLE_WIDTH+1);
	
	return ptacum;
}

char* menu_Line(char *acum, char *ptacum, int *left, char *src, int lpos){
	
	return ptacum;
}

char* menu_Header(char *acum, char *ptacum, int *left){
	//ptacum = menu_printLine(acum, ptacum, , 1);
	ptacum = menu_Asterisk(acum, ptacum, left);
	
	
	
	//char header[MENU_WIDTH] = "Transportes LEI - Gestão de Transportes";
	
	return ptacum;
}

void menu(int *input){
	/* Mínimos:
	 * 1 linha de asteriscos
	 * 3 linhas para o titulo (2 em branco e no meio o titulo)
	 * 2 linhas para o directorio (1 em branco e outra do directorio)
	 * 1 linha para opção
	 * 1 linha em branco
	 * 1 linha de opção de voltar atrás
	 * 2 linhas em branco
	 * 1 linha de estado
	 * 1 linha de asteriscos
	 * TOTAL: 13 linhas no mínimo
	 * */
	char acum[(CONSOLE_WIDTH+1)*13+1] = {'\0'};
	char *ptacum = acum;
	int left = (CONSOLE_WIDTH+1)*13+1;
	
	ptacum = menu_Header(acum, ptacum, &left);
	
	printf("%s", acum);
}



/*
int menu(){
	clearScreen();
	printf(
		";**************************************************************;\n"
		"|                                                              |\n"
		"| Transportes LEI - Gestão de Transportes                      |\n"
		"|                                                              |\n"
	);
	switch(input){
		case 9:
			printf(
			"|    Menu Principal > Sair                                     |\n"
			"|                                                              |\n"
			"|    1) Guardar e Sair                                         |\n"
			"|    2) Sair                                                   |\n"
			"|                                                              |\n"
			"|    0) Voltar ao Menu Principal                               |\n"
			"|                                                              |\n"
			"|                                                              |\n"
			"|           %50s |\n"
			"****************************************************************\n"
			">> ", rodape );
			readInt(&input);
			if( input == 1 || input == 2 )
				input += 90;
			else if( input != 0 )
				input = 9;
			break;
		case 91:
			strcpy(rodape, "Guardado");
			rodape_reset = 1;
			printf(
			"|    Menu Principal > Sair > Guardar e Sair                    |\n"
			"|                                                              |\n"
			"|                                                              |\n"
			"|                                                              |\n"
			"|                                                              |\n"
			"|           %50s |\n"
			"****************************************************************\n"
			">> ", rodape );
			input = -1;
			break;
		case 92:
			strcpy(rodape, "O programa vai terminar sem guardar dados");
			rodape_reset = 1;
			printf(
			"|    Menu Principal > Sair > Sair sem Guardar                  |\n"
			"|                                                              |\n"
			"|                                                              |\n"
			"|                                                              |\n"
			"|                                                              |\n"
			"|           %50s |\n"
			"****************************************************************\n"
			">> ", rodape );
			input = -1;
			break;
		case 8:
			strcpy(rodape, "Pressione [ENTER] duas vezes para continuar");
			rodape_reset = 1;
			printf(
			"|    Menu Principal > Ajuda e Acessibilidade                   |\n"
			"|                                                              |\n"
			"|    + Navegação Rápida                                        |\n"
			"|       Em vez de selecionar o caminho passo-a-passo, poderá   |\n"
			"|       optar por escrver o caminho de uma só vez.             |\n"
			"|          Exemplo: 9 seguido de 2 para Guardar e Sair pode    |\n"
			"|                   ser escrito 92 e ter o mesmo efeito        |\n"
			"|                                                              |\n"
			"|                                                              |\n"
			"|                                                              |\n"
			"|                                                              |\n"
			"|           %50s |\n"
			"****************************************************************\n"
			">> ", rodape );
			getchar(); clearInputBuffer(); // nao funciona ainda, precisa de 2x[ENTER]
			input = 0;
			break;
		default:
			printf(
			"|    Menu Principal                                            |\n"
			"|                                                              |\n"
			"|    1) Novo Pedido                                            |\n"
			"|    2) Gerir Clientes                                         |\n"
			"|    3) Gerir Camiões                                          |\n"
			"|    4) Gerir Localizações                                     |\n"
			"|                                                              |\n"
			"|    8) Ajuda e Acessibilidade                                 |\n"
			"|    9) Sair                                                   |\n"
			"|                                                              |\n"
			"|                                                              |\n"
			"|                                                              |\n"
			"|           %50s |\n"
			"****************************************************************\n"
			">> ", rodape );
			readInt(&input);
			if( input == -1 )
				input = 0;
		}
		
		if( rodape_reset ){
			strcpy(rodape, " ");
			rodape_reset = 0;
		}
}*/

#include <string.h>
#include <stdio.h>

#include "menu.h"
#include "utils.h"

int printMenu(int input){
	char fill[64+2]  = "****************************************************************\n";
	char space[64+2] = "*                                                              *\n";
	char title[64+2] = "*    Transportes LEI - Gestao de Transportes                   *\n";
	char status[60+1] = " ";
	char menuAnt[62+1] = "0) Voltar ao Menu Anterior";
	
	clearScreen();
	printf("%s%s%s%s",fill,space,title,space);
	switch( input ){
		case 9:
			printf( "*    %-56s  *\n"
				"%s"
				"*    %-56s  *\n"
				"*    %-56s  *\n",
					"Menu Principal > Sair", space,
					"1) Guardar e Sair",
					"2) Sair"
			);
			break;
		case 91:
			strcpy(status, "Guardado");
			strcpy(menuAnt, " ");
			printf( "*    %-56s  *\n", "Menu Principal > Sair > Guardar e Sair");
			break;
		case 92:
			strcpy(status, "O programa vai terminar sem guardar dados");
			strcpy(menuAnt, " ");
			printf( "*    %-56s  *\n", "Menu Principal > Sair > Sair sem guarda sem guardarr");
			break;
		case 8:
			//strcpy(status, "Pressione [ENTER] duas vezes para continuar");
			printf( "*    %-56s  *\n"
				"%s"
				"*    %-56s  *\n"
				"*    %-56s  *\n"
				"*    %-56s  *\n"
				"*    %-56s  *\n"
				"*    %-56s  *\n",
					"Menu Principal > Ajuda e Acessibilidade", space,
					"+ Navegação Rápida",
					"   Em vez de selecionar o caminho passo-a-passo, podera",
					"   optar por escrever o caminho de uma so vez.",
					"      Exemplo: 9 seguido de 2 para Guardar e Sair pode",
					"               ser escrito 92 e ter o mesmo efeito"
			);
			break;
		default:
			printf( "*    %-56s  *\n"
				"%s"
				"*    %-56s  *\n"
				"*    %-56s  *\n"
				"*    %-56s  *\n"
				"*    %-56s  *\n"
				"%s"
				"*    %-56s  *\n",
					"Menu Principal", space,
					"1) Novo Pedido",
					"2) Gerir Clientes",
					"3) Gerir Camioes",
					"4) Gerir Localizacoes",space,
					"8) Ajuda e Acessibilidade"
			);
			

			strcpy(menuAnt, "9) Sair");
	}
	printf(
		"%s"
		"*    %-56s  *\n"
		"%s%s"
		"* %60s *\n"
		"%s>> ",
			space, menuAnt, space, space, status, fill);
	
	switch( input ){
		case -1:
			input = 0;
		case 9:
			input = getIntLoop();
			if( input == 1 || input == 2 )
				input += 90;
			else if( input != 0 )
				input = 9;
			break;
		case 91:
			input = -1;
			break;
		case 92:
			input = -1;
			break;
		case 8:
			getchar(); clearInputBuffer();
			input = 0;
			break;
		default:
			input = getIntLoop();
			if( input == -1 )
				input = 0;
	}

	return input;
}

int getIntLoop(){
	int x;
	if( isInt( readInt( &x ) ) == 0 ){
		printf("Numero invalido\n>> ");
		return getIntLoop();
	}else
		return x;
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

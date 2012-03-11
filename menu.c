#include "menu.h"

int menu(){
	clearScreen();
		printf(
			";**************************************************************;\n"
			"|                                                              |\n"
			"|    Transportes LEI - Gestão de Transportes                   |\n"
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
}

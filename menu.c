#include <string.h>
#include <stdio.h>

#include "menu.h"
#include "utils.h"
#include "dados.h"

static int last[3]; //ultimas 3 escolhas

// usada para ficar com registo das ultimas 3 acções do utilizador
// depois mete-te na parte onde agora estão os atalhos
//
// basta ele fazer 1 coisa uma vez e depois sabe que vai estar sempre no atalho da tecla 5
// depois carrega sempre 5 5 5 5 5 se for uma tarefa repetitiva
static void novaEscolha(int input){
    if( input != last[0] && input != last[1] ){
        last[2] = last[1];
        last[1] = last[0];
        last[0] = input;
    }else if( input == last[1] ){
        last[1] = last[0];
        last[0] = input;
    }
}

int printMenu(int input){
	char fill[64+2]  = "****************************************************************\n";
	char space[64+2] = "*                                                              *\n";
	char title[64+2] = "*    Transportes LEI - Gestao de Transportes                   *\n";
	char status[60+1] = " ";
	char menuAnt[62+1] = "0) Voltar ao Menu Anterior";
        char inputWait[4] = ">> ";
	
	clearScreen();
        //printf("input=%d\n",input);
	printf("%s%s%s%s",fill,space,title,space);
	switch( input ){
                case 2:
                        printf( "*    %-56s  *\n"
                                "%s"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n",
                                    "Menu P. > Gestao de Clientes", space,
                                    "1) Novo cliente",
                                    "2) Eliminar cliente",
                                    "3) Listar clientes",
                                    "4) Actualizar dados do cliente"
                        );
                        break;
                case 21:
                        strcpy( inputWait, "" );
                        strcpy( menuAnt, "[qualquer]) Voltar ao Menu anterior" );
                        strcpy( status, "Inserindo dados de teste..." ); //debug
                        printf( "*    %-56s  *\n"
                                "%s"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n",
                                    "Menu P. > Gestao de Clientes > Novo cliente", space,
                                    "Campos:",
                                    "NIF - número de contribuinte (9 digitos)",
                                    "Nome - Nome do cliente",
                                    "Morada - Morada do cliente"
                        );
                        break;
                case 23:
                        strcpy( status, "Listando Elementos..." );
                        strcpy( inputWait, "" );
                        strcpy( menuAnt, "[qualquer]) Voltar ao Menu anterior" );
                        printf( "*    %-56s  *\n",
                                    "Menu P. > Gestao de Clientes > Listagem"
                        ); 
                        break;
                case 3:
                        printf( "*    %-56s  *\n"
                                "%s"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n",
                                    "Menu P. > Gestao de Camioes", space,
                                    "1) Novo veiculo",
                                    "2) Eliminar veiculo",
                                    "3) Listar veiculos",
                                    "4) Actualizar dados do veiculo"
                        );
                        break;
                case 31:
                        strcpy( inputWait, "" );
                        strcpy( menuAnt, "[qualquer]) Voltar ao Menu anterior" );
                        strcpy( status, "Inserindo dados de teste..." ); //debug
                        printf( "*    %-56s  *\n"
                                "%s"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n",
                                    "Menu P. > Gestao de Camioes > Novo veiculo", space,
                                    "Campos:",
                                    "ID - inteiro positivo que identifica o veiculo",
                                    "Matricula - conjunto de caracteres no formato XX-XX-XX",
                                    "Consumo - consumo de combustivel a cada 100km"
                        );
                        break;
                case 33:
                        strcpy( status, "Listando Elementos..." );
                        strcpy( inputWait, "" );
                        strcpy( menuAnt, "[qualquer]) Voltar ao Menu anterior" );
                        printf( "*    %-56s  *\n",
                                    "Menu P. > Gestao de Camioes > Listagem"
                        ); 
                        break;
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
			strcpy(status, "O programa terminou sem guardar dados");
			strcpy(menuAnt, " ");
			printf( "*    %-56s  *\n", "Menu Principal > Sair > Sair sem guardar");
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
                case 32:
                case 34:
                        strcpy(status, "Funcionalidade não disponivel (ainda)..");
		default:
			printf( "*    %-56s  *\n"
				"%s"
				"*    %-56s  *\n"
				"*    %-56s  *\n"
				"*    %-56s  *\n"
				"*    %-56s  *\n"
				"%s"
				"*    %-56s  *\n"
				"*    %-56s  *\n"
				"*    %-56s  *\n"
				"*    %-56s  *\n"
				"*    %-56s  *\n",
					"Menu Principal", space,
					"1) Novo Pedido",
					"2) Gerir Clientes",
					"3) Gerir Camioes",
					"4) Gerir Localidades",space,
                                        "--Atalhos--",
                                        "5) Adicionar Localidade",
                                        "6) Listar pedidos do cliente",
                                        "", //outro atalho...
					"8) Ajuda e Acessibilidade"
			);
			

			strcpy(menuAnt, "9) Sair");
	}
	printf(
		"%s"
		"*    %-56s  *\n"
		"%s%s"
		"* %60s *\n"
		"%s%s",
			space, menuAnt, space, space, status, fill, inputWait);
	
	
	return input;
}

int getInput(int input, MainTreePt camioes, MainTreePt clientes){
    Camiao camiao_teste[20] = {
        {0, "00-60-00", 1.0},
        {1, "60-00-00", 1.5},
        {2, "00-00-60", 2.0},
        {3, "00-85-00", 2.5},
        {4, "94-00-00", 3.0},
        {5, "00-63-85", 3.5},
        {6, "63-00-60", 4.0},
        {7, "60-94-00", 4.5},
        {8, "85-85-85", 5.0},
        {9, "85-AA-85", 5.5},
        {10, "60-BB-00", 6.0},
        {11, "00-BB-60", 6.5},
        {12, "94-CC-00", 7.0},
        {13, "00-DC-00", 7.5},
        {14, "00-NY-00", 8.0},
        {15, "00-FK-00", 8.5},
        {16, "85-XX-00", 9.0},
        {17, "94-94-94", 9.5},
        {18, "85-85-85",10.0},
        {19, "60-60-60",10.5} };
    Cliente cliente_teste[20] = {
        {111111111, "luis", "Rua de baixo"},
        {222222222, "paulo", "Rua de cima"},
        {333333333, "joaquim", "Rua da esquerda"},
        {444444444, "albertina", "Rua da direita"},
        {726347623, "daniel", "praça do centro"},
        {638649271, "bruno", "praça ao lado"},
        {119372931, "fernando", "rua do fernando"},
        {682643264, "vanessa", "cidade feliz"},
        { 64826471, "claudia", "rua atravessada"},
        {101928498, "bernardo", "estrada do ar"},
        {628303648, "rui", "rua sem nome"},
        {356456456, "josé", "mais um nome de rua"},
        {554555423, "antonio", "um nome de cidade"},
        {729372984, "joao", "lisboa"},
        {380934803, "jorge", "porto"},
        {987654321, "joana", "santarem"},
        {456789121, "antonia", "leiria"},
        {732738231, "fernanda", "braga"},
        {452134541, "bruna", "guimarães"},
        {454645231, "vasco", "ultima rua à direita"}
    };
    int i;
    switch( input ){
        case -1:
            input = 0;
        case 2:
            input = getIntLoop();
            if( input >= 1 && input <= 4)
                input += 20;
            else if( input != 0 )
                input = 2;
            break;
        case 21:
            for(i=0; i<20; i++)
                tree_insert(clientes, cliente_novo( cliente_teste[i].nif, cliente_teste[i].nome, cliente_teste[i].morada ));
            getchar(); clearInputBuffer();
            input /= 10;
            break;
        case 22: break;
        case 23:
            printf("ordenados por Nome: \n");
            tree_applyToAllOrdered( clientes, 1 , cliente_dump);
            printf("ordenados por NIF: \n");
            tree_applyToAllOrdered( clientes, 0 , cliente_dump);
            getchar(); clearInputBuffer();
            input /= 10;
            break;
        case 24: //novaEscolha(input);
            //input = 2;
            break;
        case 3:
            input = getIntLoop();
            if( input >= 1 && input <= 4)
                input += 30;
            else if( input != 0 )
                input = 3;
            break;
        case 31:
            for(i=0; i<20; i++)
                tree_insert( camioes, camiao_novo( camiao_teste[i].id, camiao_teste[i].matricula, camiao_teste[i].custo ) );
            getchar(); clearInputBuffer();
            input /= 10;
            break;
        case 32:break;
        case 33:
            printf("ordenados por matricula: \n");
            tree_applyToAllOrdered( camioes, 1 , camiao_dump);
            printf("ordenados por id: \n");
            tree_applyToAllOrdered( camioes, 0 , camiao_dump);
            getchar(); clearInputBuffer();
            input /= 10;
            break;
        case 34: //novaEscolha(input);
            //input = 3;
            break;
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
    if( isInt( x = readInt() ) == 0 ){
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

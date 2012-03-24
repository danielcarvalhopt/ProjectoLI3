/**
 * @file menu.c
 * @brief Definições estáticas do módulo da interface com o utilizador
 *
 * */
#include <string.h>
#include <stdio.h>

#include "input.h"
#include "menu.h"
#include "utils.h"
#include "dados.h"



static int lastInt[3];          /**< Representação numérica dos atalhos **/
static char lastString[3][54];  /**<  Representação string dos atalhos  **/


/**
 * Altera os valores das variáveis static que controlam os atalhos mostrados ao utilizador
 * @param input Representação numérica da ultima opção escolhida pelo utilizador
 * @param str Representação string da ultima opção escolhida pelo utilizador
 * @see lastInt
 * @see lastString
 * */
static void novaEscolha(int input, char *str){
    if( input != lastInt[0] && input != lastInt[1] ){
        lastInt[2] = lastInt[1];
        lastInt[1] = lastInt[0];
        lastInt[0] = input;
       
        strcpy( lastString[2], lastString[1] );
        strcpy( lastString[1], lastString[0] );
        strcpy( lastString[0], str );
    }else if( input == lastInt[1] ){
        lastInt[1] = lastInt[0];
        lastInt[0] = input;

        strcpy( lastString[1], lastString[0] );
        strcpy( lastString[0], str );
    }
}

void inicializarAtalhos(){
    lastInt[0] = 21;
    strcpy(lastString[0], "Inserir Cliente");

    lastInt[1] = 31;
    strcpy( lastString[1], "Inserir Veiculo");

    lastInt[2] = 41;
    strcpy( lastString[2], "Inserir Localidade");
}


int printMenu(int input){
	char fill[64+2]  = "****************************************************************\n";
	char space[64+2] = "*                                                              *\n";
	char title[64+2] = "*    Transportes LEI - Gestao de Transportes                   *\n";
	char status[60+1] = " ";
	char menuAnt[62+1] = "0) Voltar ao Menu Principal";
        char inputWait[4] = ">> ";

        int i;
        
        /**
         * Caso se tenha seleccionado um atalho, modifica a variável input
         * */
        for( i=5; i<8; i++ )
            if( input == i )
                input = lastInt[i-5];


	clearScreen();
	printf("%s%s%s%s",fill,space,title,space);
	switch( input ){
                case 1:
                        strcpy( menuAnt, "[qualquer]) Voltar ao Menu principal" );
                        strcpy( status, "Funcionalidade ainda nao esta disponivel..." ); 

                        printf( "*    %-56s  *\n"
                                "%s",
                                    "Menu Principal > Novo pedido", space
                        );
                        break;

                case 2:
                        printf( "*    %-56s  *\n"
                                "%s"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n",
                                    "Menu P. > Gestao de Clientes", space,
                                    "1) Inserir Cliente",
                                    "2) Eliminar Cliente",
                                    "3) Listar Clientes",
                                    "4) Modificar Cliente"
                        );
                        break;
                case 21:
                        strcpy( inputWait, "" );
                        strcpy( menuAnt, "[qualquer]) Voltar ao Menu Principal" );
                        strcpy( status, "Inserindo dados de teste..." ); 
                        printf( "*    %-56s  *\n"
                                "%s"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n",
                                    "Menu P. > Gestao de Clientes > Inserir Cliente", space,
                                    "Campos:",
                                    "NIF - número de contribuinte (9 digitos)",
                                    "Nome - Nome do cliente",
                                    "Morada - Morada do cliente"
                        );
                        novaEscolha(21,"Inserir Cliente");
                        break;
                case 22:
                        strcpy( menuAnt, "[qualquer]) Voltar ao Menu Principal" );
                        strcpy( status, "Funcionalidade ainda nao esta disponivel..." ); 

                        printf( "*    %-56s  *\n"
                                "%s",
                                    "Menu P. > Gestao de Clientes > Eliminar Cliente", space
                        );
                        novaEscolha(22, "Eliminar Cliente");
                        break;

                case 23:
                        strcpy( status, "Listando Elementos..." );
                        strcpy( inputWait, "" );
                        strcpy( menuAnt, "[qualquer]) Voltar ao Menu Principal" );
                        printf( "*    %-56s  *\n"
                                "%s",
                                    "Menu P. > Gestao de Clientes > Listar Clientes", space
                        );
                        novaEscolha(23, "Listar Clientes");
                        break;
                case 24:
                        strcpy( menuAnt, "[qualquer]) Voltar ao Menu Principal" );
                        strcpy( status, "Funcionalidade ainda nao esta disponivel..." ); 

                        printf( "*    %-56s  *\n"
                                "%s",
                                    "Menu P. > Gestao de Clientes > Modificar Cliente", space
                        );
                        novaEscolha(24, "Modificar Cliente");
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
                                    "4) Modificar veiculo"
                        );
                        break;
                case 31:
                        strcpy( inputWait, "" );
                        strcpy( menuAnt, "[qualquer]) Voltar ao Menu Principal" );
                        strcpy( status, "Inserindo dados de teste..." ); 
                        printf( "*    %-56s  *\n"
                                "%s"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n",
                                    "Menu P. > Gestao de Camioes > Inserir veiculo", space,
                                    "Campos:",
                                    "ID - inteiro positivo que identifica o veiculo",
                                    "Matricula - conjunto de caracteres no formato XX-XX-XX",
                                    "Consumo - consumo de combustivel a cada 100km"
                        );
                        novaEscolha(31, "Inserir Veiculo");
                        break;
                case 32:
                        strcpy( menuAnt, "[qualquer]) Voltar ao Menu Principal" );
                        strcpy( status, "Funcionalidade ainda nao esta disponivel..." ); 

                        printf( "*    %-56s  *\n"
                                "%s",
                                    "Menu P. > Gestao de Camioes > Eliminar Veiculo", space
                        );
                        novaEscolha(32, "Eliminar Veiculo");
                        break;
                case 33:
                        strcpy( status, "Listando Elementos..." );
                        strcpy( inputWait, "" );
                        strcpy( menuAnt, "[qualquer]) Voltar ao Menu Principal" );
                        printf( "*    %-56s  *\n",
                                    "Menu P. > Gestao de Camioes > Listar Veiculos"
                        ); 
                        novaEscolha(33, "Listar Veiculos");
                        break;
                case 34:
                        strcpy( menuAnt, "[qualquer]) Voltar ao Menu Principal" );
                        strcpy( status, "Funcionalidade ainda nao esta disponivel..." ); 

                        printf( "*    %-56s  *\n"
                                "%s",
                                    "Menu P. > Gestao de Camioes > Modificar Veiculo", space
                        );
                        novaEscolha(34, "Modificar Veiculo");
                        break;
                case 4:
                        printf( "*    %-56s  *\n"
                                "%s"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n",
                                    "Menu P. > Gestao de Localidades", space,
                                    "1) Inserir Localidade",
                                    "2) Eliminar Localidade",
                                    "3) Listar localidades",
                                    "4) Modificar localidade"
                        );
                        break;
                case 41:
                        strcpy( inputWait, "" );
                        strcpy( menuAnt, "[qualquer]) Voltar ao Menu Principal" );
                        strcpy( status, "Inserindo dados de teste..." ); 
                        printf( "*    %-56s  *\n"
                                "%s"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n",
                                    "Menu P. > Gestao de Localidades > Inserir Localidade", space,
                                    "Campos:",
                                    "???"
                        );
                        novaEscolha(31, "Inserir Localidade");
                        break;
                case 42:
                        strcpy( menuAnt, "[qualquer]) Voltar ao Menu Principal" );
                        strcpy( status, "Funcionalidade ainda nao esta disponivel..." ); 

                        printf( "*    %-56s  *\n"
                                "%s",
                                    "Menu P. > Gestao de Localidades > Eliminar Localidade", space
                        );
                        novaEscolha(32, "Eliminar Localidade");
                        break;
                case 43:
                        strcpy( status, "Listando Elementos..." );
                        strcpy( inputWait, "" );
                        strcpy( menuAnt, "[qualquer]) Voltar ao Menu Principal" );
                        printf( "*    %-56s  *\n",
                                    "Menu P. > Gestao de Localidades > Listar Localidades"
                        ); 
                        novaEscolha(33, "Listar Localidades");
                        break;
                case 44:
                        strcpy( menuAnt, "[qualquer]) Voltar ao Menu Principal" );
                        strcpy( status, "Funcionalidade ainda nao esta disponivel..." ); 

                        printf( "*    %-56s  *\n"
                                "%s",
                                    "Menu P. > Gestao de Localidades > Modificar Localidade", space
                        );
                        novaEscolha(34, "Modificar Localidade");
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
                        printf( "*    %-56s  *\n"
				"%s"
				"*    %-56s  *\n"
				"*    %-56s  *\n"
				"*    %-56s  *\n",
					"Menu Principal > Exportar/Importar Dados", space,
					"1) Exportar",
                                        "2) Exportar (especificando nome do ficheiro)",
					"3) Importar"
			);
			break;

		case 81:
                        strcpy( menuAnt, "[qualquer]) Voltar ao Menu Principal" );
                        strcpy( status, "Funcionalidade ainda nao esta disponivel..." ); 
                        printf( "*    %-56s  *\n",
                                    "Menu P. > Importar/Exportar Dados > Exportar Dados"
                        ); 
                        novaEscolha(81, "Exportar Dados");
                        break;
                case 82:
                        strcpy( menuAnt, "[qualquer]) Voltar ao Menu Principal" );
                        strcpy( status, "Funcionalidade ainda nao esta disponivel..." ); 
                        printf( "*    %-56s  *\n",
                                    "Menu P. > Importar/Exportar Dados > Exportar Dados..."
                        ); 
                        novaEscolha(82, "Exportar Dados (especificando nome de ficheiro)");
                        break;
                case 83:
                        strcpy( menuAnt, "[qualquer]) Voltar ao Menu Principal" );
                        strcpy( status, "Funcionalidade ainda nao esta disponivel..." ); 
                        printf( "*    %-56s  *\n",
                                    "Menu P. > Importar/Exportar Dados > Importar Dados"
                        ); 
                        novaEscolha(83, "Importar Dados");
                        break;
		default:
			printf( "*    %-56s  *\n"
				"%s"
				"*    %-56s  *\n"
				"*    %-56s  *\n"
				"*    %-56s  *\n"
				"*    %-56s  *\n"
				"%s"
				"*    %-56s  *\n"
				"*    5) %-53s  *\n"
				"*    6) %-53s  *\n"
				"*    7) %-53s  *\n"
				"%s"
				"*    %-56s  *\n",
					"Menu Principal", space,
					"1) Novo Pedido",
					"2) Gerir Clientes",
					"3) Gerir Camioes",
					"4) Gerir Localidades",space,
                                        "--Recentemente usados--",
                                        lastString[0],
                                        lastString[1],
                                        lastString[2],space,
					"8) Importar/Exportar Dados"
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
    //alguns dados para testes

    Camiao camiao_teste[20] = {
        {0, "00-60-00", 1.0, 10},
        {1, "60-00-00", 1.5, 10},
        {2, "00-00-60", 2.0, 10},
        {3, "00-85-00", 2.5, 10},
        {4, "94-00-00", 3.0, 10},
        {5, "00-63-85", 3.5, 10},
        {6, "63-00-60", 4.0, 10},
        {7, "60-94-00", 4.5, 10},
        {8, "85-85-85", 5.0, 10},
        {9, "85-AA-85", 5.5, 10},
        {10, "60-BB-00", 6.0, 10},
        {11, "00-BB-60", 6.5, 10},
        {12, "94-CC-00", 7.0, 10},
        {13, "00-DC-00", 7.5, 10},
        {14, "00-BB-00", 8.0, 10},
        {15, "00-AA-00", 8.5, 10},
        {16, "85-XX-00", 9.0, 10},
        {17, "94-94-94", 9.5, 10},
        {18, "85-85-85",10.0, 10},
        {19, "60-60-60",10.5, 10} };
    Cliente cliente_teste[20] = {
        {111111111, "luis", "Rua de baixo", NULL},
        {222222222, "paulo", "Rua de cima", NULL},
        {333333333, "joaquim", "Rua da esquerda", NULL},
        {444444444, "albertina", "Rua da direita", NULL},
        {726347623, "daniel", "praça do centro", NULL},
        {638649271, "bruno", "praça ao lado", NULL},
        {119372931, "fernando", "rua do fernando", NULL},
        {682643264, "vanessa", "cidade feliz", NULL},
        { 64826471, "claudia", "rua atravessada", NULL},
        {101928498, "bernardo", "estrada do ar", NULL},
        {628303648, "rui", "rua sem nome", NULL},
        {356456456, "josé", "mais um nome de rua", NULL},
        {554555423, "antonio", "um nome de cidade", NULL},
        {729372984, "joao", "lisboa", NULL},
        {380934803, "jorge", "porto", NULL},
        {987654321, "joana", "santarem", NULL},
        {456789121, "antonia", "leiria", NULL},
        {732738231, "fernanda", "braga", NULL},
        {452134541, "bruna", "guimarães", NULL},
        {454645231, "vasco", "ultima rua à direita", NULL}
    };
    int i;
    switch( input ){
        case -1:
            input = 0;
        case 1: getchar(); clearInputBuffer(); input=0; break;
        case 2:
            input = getIntLoop();
            if( input >= 1 && input <= 4)
                input += 20;
            else if( input != 0 )
                input = 2;
            break;
        case 21:
            for(i=0; i<20; i++)
                tree_insert(clientes, cliente_novo( cliente_teste[i].nif, cliente_teste[i].nome, cliente_teste[i].morada, cliente_teste[i].servicos ));
            getchar(); clearInputBuffer();
            input = 0;
            break;
        case 22: getchar(); clearInputBuffer(); input=0; break;
        case 23:
            // modo de listagem para efeitos de debug
            printf("ordenados por Nome: \n");
            tree_applyToAllOrdered( clientes, 1 , cliente_dump);
            printf("ordenados por NIF: \n");
            tree_applyToAllOrdered( clientes, 0 , cliente_dump);
            getchar(); clearInputBuffer();
            input = 0;
            break;
        case 24: getchar(); clearInputBuffer(); input=0; break;
        case 3:
            input = getIntLoop();
            if( input >= 1 && input <= 4)
                input += 30;
            else if( input != 0 )
                input = 3;
            break;
        case 31:
            for(i=0; i<20; i++)
                tree_insert( camioes, camiao_novo( camiao_teste[i].id, camiao_teste[i].matricula, camiao_teste[i].custo, camiao_teste[i].peso ) );
            getchar(); clearInputBuffer();
            input = 0;
            break;
        case 32:break;
        case 33:
            // modo de listagem para efeitos de debug
            printf("ordenados por matricula: \n");
            tree_applyToAllOrdered( camioes, 1 , camiao_dump);
            printf("ordenados por id: \n");
            tree_applyToAllOrdered( camioes, 0 , camiao_dump);
            getchar(); clearInputBuffer();
            input = 0;
            break;
        case 34: getchar(); clearInputBuffer(); input=0; break;
            break;
        case 4:
            input = getIntLoop();
            if( input >= 1 && input <= 4)
                input += 40;
            else if( input != 0 )
                input = 4;
            break;
        case 41: getchar(); clearInputBuffer(); input=0; break;
        case 42: getchar(); clearInputBuffer(); input=0; break;
        case 43: getchar(); clearInputBuffer(); input=0; break;
        case 44: getchar(); clearInputBuffer(); input=0; break;
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
            input = getIntLoop();
            if( input >= 1 && input <= 3 )
                input += 80;
            else if( input != 0 )
                input = 8;
            break;
        case 81: getchar(); clearInputBuffer(); input=0; break;
        case 82: getchar(); clearInputBuffer(); input=0; break;
        case 83: getchar(); clearInputBuffer(); input=0; break;
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



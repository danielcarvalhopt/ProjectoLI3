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
#include "serial.h"



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
        char inputWait[4] = "";


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
                        printf( "*    %-56s  *\n"
                                "%s",
                                    "Menu Principal > Novo pedido", space
                        );
                        break;
                case 2:
                        strcpy(inputWait, ">> ");
                        printf( "*    %-56s  *\n"
                                "%s"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "%s"
                                "*    %-56s  *\n",
                                    "Menu P. > Gestao de Clientes", space,
                                    "1) Inserir Cliente",
                                    "2) Eliminar Cliente",
                                    "3) Listar Clientes",
                                    "4) Modificar Cliente",space,
                                    "5) Listar Servicos do Cliente"
                        );
                        break;
                case 21:
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
                        printf( "*    %-56s  *\n"
                                "%s",
                                    "Menu P. > Gestao de Clientes > Eliminar Cliente", space
                        );
                        novaEscolha(22, "Eliminar Cliente");
                        break;
                case 23:
                        printf( "*    %-56s  *\n"
                                "%s",
                                    "Menu P. > Gestao de Clientes > Listar Clientes", space
                        );
                        novaEscolha(23, "Listar Clientes");
                        break;
                case 24:
                        printf( "*    %-56s  *\n"
                                "%s",
                                    "Menu P. > Gestao de Clientes > Modificar Cliente", space
                        );
                        novaEscolha(24, "Modificar Cliente");
                        break;
                case 25:
                        printf( "*    %-56s  *\n"
                                "%s",
                                    "Menu P. > Gestao de Clientes > Listar Servicos", space
                        );
                        novaEscolha(25, "Listar Servicos de Cliente");
                        break;
                case 3:
                        strcpy(inputWait, ">> ");
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
                        printf( "*    %-56s  *\n"
                                "%s"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n",
                                    "Menu P. > Gestao de Camioes > Inserir veiculo", space,
                                    "Campos:",
                                    "ID - (inteiro positivo) identificador unico do veiculo",
                                    "Matricula - (caracteres) formato: XX-XX-XX",
                                    "Consumo - (numero real) consumo de combustivel a cada 100km",
                                    "Peso - (numero real) peso maximo que o camiao pode carregar",
                                    "Local - (caracteres) localidade onde o camiao se encontra"
                        );
                        novaEscolha(31, "Inserir Veiculo");
                        break;
                case 32:
                        printf( "*    %-56s  *\n"
                                "%s",
                                    "Menu P. > Gestao de Camioes > Eliminar Veiculo", space
                        );
                        novaEscolha(32, "Eliminar Veiculo");
                        break;
                case 33:
                        printf( "*    %-56s  *\n",
                                    "Menu P. > Gestao de Camioes > Listar Veiculos"
                        ); 
                        novaEscolha(33, "Listar Veiculos");
                        break;
                case 34:
                        printf( "*    %-56s  *\n"
                                "%s",
                                    "Menu P. > Gestao de Camioes > Modificar Veiculo", space
                        );
                        novaEscolha(34, "Modificar Veiculo");
                        break;
                case 4:
                        strcpy(inputWait, ">> ");
                        printf( "*    %-56s  *\n"
                                "%s"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "%s"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n"
                                "*    %-56s  *\n",
                                    "Menu P. > Gestao de Localidades/Ligacoes", space,
                                    "1) Inserir Localidade",
                                    "2) Eliminar Localidade",space,
                                    "3) Criar Ligacao",
                                    "4) Eliminar Ligacao",
                                    "5) Listar Ligacoes",
                                    "6) Modificar Ligacoes"
                        );
                        break;
                case 41:
                        printf( "*    %-56s  *\n",
                                    "Menu P. > Localidades/Ligacoes > Inserir Localidade"
                        );
                        novaEscolha(41, "Inserir Localidade");
                        break;
                case 42:
                        printf( "*    %-56s  *\n"
                                "%s",
                                    "Menu P. > Localidades/Ligacoes > Eliminar Localidade", space
                        );
                        novaEscolha(42, "Eliminar Localidade");
                        break;
                case 43:
                        printf( "*    %-56s  *\n"
                                "%s",
                                    "Menu P. > Localidades/Ligacoes > Criar Ligacao", space
                        );
                        novaEscolha(43, "Criar Ligacao");
                        break;
                case 44:
                        printf( "*    %-56s  *\n"
                                "%s",
                                    "Menu P. > Localidades/Ligacoes > Eliminar Ligacao", space
                        );
                        novaEscolha(44, "Eliminar Ligacao");
                        break;
                case 45:
                        printf( "*    %-56s  *\n"
                                "%s",
                                    "Menu P. > Localidades/Ligacoes > Listar Ligacao", space
                        );
                        novaEscolha(45, "Listar Ligacao");
                        break;
                case 46:
                        printf( "*    %-56s  *\n"
                                "%s",
                                    "Menu P. > Localidades/Ligacoes > Modificar Ligacao", space
                        );
                        novaEscolha(46, "Modificar Ligacao");
                        break;
                case 9:
                        strcpy(inputWait, ">> ");
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
                        strcpy(inputWait, ">> ");
                        printf( "*    %-56s  *\n"
				"%s"
				"*    %-56s  *\n"
				"*    %-56s  *\n",
					"Menu Principal > Exportar/Importar Dados", space,
					"1) Exportar",
					"2) Importar"
			);
			break;
		case 81:
                        printf( "*    %-56s  *\n",
                                    "Menu P. > Importar/Exportar Dados > Exportar Dados"
                        ); 
                        novaEscolha(81, "Exportar Dados");
                        break;
                case 82:
                        printf( "*    %-56s  *\n",
                                    "Menu P. > Importar/Exportar Dados > Importar Dados"
                        ); 
                        novaEscolha(82, "Importar Dados");
                        break;
		default:
                        strcpy(inputWait, ">> ");
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
					"4) Gerir Localidades e Ligacoes",space,
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

int getInput(int input, MainTreePt *camioes, MainTreePt *clientes, TabelaHashPTR *localidades){
    char pressENTER[101] = "Pressione [ENTER] para continuar";
    switch( input ){
        case -1:
            input = 0;
        case 1: insereServicoInput(*localidades, *clientes, *camioes);
            clearInputBuffer();
            input = 0;
            break;
        case 2:
            input = getIntLoop();
            if( input >= 1 && input <= 5)
                input += 20;
            else if( input != 0 )
                input = 2;
            break;
        case 21:
            clientei_insere(*clientes);
            clearInputBuffer();
            input = 0;
            break;
        case 22:
            clientei_remove(*clientes);
            clearInputBuffer();
            input=0; break;
        case 23: 
            clientei_lista(*clientes);
            clearInputBuffer();
            input = 0;
            break;
        case 24:
            clientei_modifica(*clientes);
            clearInputBuffer();
            input=0; break;
        case 25:
            servicosi_lista(*clientes);
            clearInputBuffer();
            input=0; break;
        case 3:
            input = getIntLoop();
            if( input >= 1 && input <= 4)
                input += 30;
            else if( input != 0 )
                input = 3;
            break;
        case 31:
            camiaoi_insere( *camioes, *localidades );
            printf("\n%s", pressENTER);
            clearInputBuffer();
            input = 0;
            break;
        case 32:
            camiaoi_remove( *camioes );
            clearInputBuffer();
            input = 0;
            break;
        case 33:
            camiaoi_lista(*camioes);
            printf("\n%s", pressENTER);
            clearInputBuffer();
            input = 0;
            break;
        case 34:
            camiaoi_modifica(*camioes, *localidades);
            clearInputBuffer();
            input=0;
            break;
        case 4:
            input = getIntLoop();
            if( input >= 1 && input <= 6)
                input += 40;
            else if( input != 0 )
                input = 4;
            break;
        case 41: inserelocalidadeinput(*localidades); clearInputBuffer(); input=0; break;
        case 42: removelocalidadeinput(*localidades); clearInputBuffer(); input=0; break;
        case 43: insereligacaoinput(*localidades); clearInputBuffer(); input=0; break;
        case 44: removeligacaoinput(*localidades); clearInputBuffer(); input=0; break;
        case 45: imprimelistaligacoesinput(*localidades); clearInputBuffer(); input=0; break;
        case 46: editaligacaoinput(*localidades); clearInputBuffer(); input=0; break;
        case 9:
            input = getIntLoop();
            if( input == 1 || input == 2 )
                input += 90;
            else if( input != 0 )
                input = 9;
            break;
        case 91:
            serialize( *localidades, *camioes, *clientes );
            input = -1;
            break;
        case 92:
            input = -1;
            break;
        case 8:
            input = getIntLoop();
            if( input >= 1 && input <= 2 )
                input += 80;
            else if( input != 0 )
                input = 8;
            break;
        case 81: serialize( *localidades, *camioes, *clientes ); clearInputBuffer(); input=0; break;
        case 82: deserialize( camioes, comparaCamioes, clientes, comparaClientes, localidades, comparalocalidades, hash_function );
                 clearInputBuffer(); input=0; break;
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



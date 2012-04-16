/**
 * @file menu.h
 *
 * @brief Módulo da interface com o utilizador.
 * @details Tem funções para escrever o menú no ecrã e interpretar o input do utilizador
 * */
#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "mod_avl_n_dimensional.h"
#include "mod_tabela_hash.h"

/**
 * @brief Escreve o menú no ecrã
 * @param input Inteiro que indica o menú a apresentar
 * @return Inteiro que indica o menú que foi apresentado
 * */
int printMenu(int input);

/**
 * @brief Continua a pedir um número ao utilizador até que o utilizador introduza um número válido
 * @return O inteiro válido introduzido pelo utilizador
 * */
int getIntLoop();

/**
 * @brief Chama outras funções de acordo com o input do utilizador
 * @param input Inteiro que indica o menú que foi mostrado ao utilizador
 * @param camioes Estrutura de controlo de uma avl n-dimensional com os dados relativos aos camioes
 * @param clientes Estrutura de controlo de uma avl n-dimensional com os dados relativos aos camioes
 * @param localidades Tabela de Hash para tratamento de dados de localidades
 * @return Inteiro que indica o próximo menú a mostrar ao utilizador
 * */
int getInput(int input, MainTreePt *camioes, MainTreePt *clientes, TabelaHashPTR *localidades);

/** 
 * @brief Inicializa as variáveis static que controlam os atalhos mostrados ao utilizador com três atalhos iniciais e predefinidos
 * @see lastInt
 * @see lastString
 * */
void inicializarAtalhos();
void inserelocalidadeinput(TabelaHashPTR table);
void removelocalidadeinput(TabelaHashPTR table);
void insereligacaoinput(TabelaHashPTR table);

#endif /* MENU_H_INCLUDED */


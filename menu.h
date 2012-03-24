/**
 * @file menu.h
 *
 * @brief Módulo da interface com o utilizador.
 * @details Tem funções para escrever o menú no ecrã e interpretar o input do utilizador
 * */
#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "mod_avl_n_dimensional.h"

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
 * @return Inteiro que indica o próximo menú a mostrar ao utilizador
 * */
int getInput(int input, MainTreePt camioes, MainTreePt clientes);

/** 
 * @brief Inicializa as variáveis static que controlam os atalhos mostrados ao utilizador com três atalhos iniciais e predefinidos
 * @see lastInt
 * @see lastString
 * */
void inicializarAtalhos();


void removeligacaoinput(TabelaHashPTR table);

#endif /* MENU_H_INCLUDED */


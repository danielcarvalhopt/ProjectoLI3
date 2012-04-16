/**
 * @file serial.h
 *
 * @brief Módulo de serialização e de-serialização
 * @details Tem funções para gravar os dados num ficheiro e ler os dados anteriormente gravados.
 * */
#ifndef SERIAL_H_INCLUDED
#define SERIAL_H_INCLUDED

#include "mod_avl_n_dimensional.h"
#include "mod_tabela_hash.h"

#include <stdio.h>

int serialize(TabelaHashPTR tabela, MainTreePt camioes, MainTreePt clientes);

int deserialize(
        MainTreePt *camioes, int (*comparaCamioes[DIM])(void*,void*),
        MainTreePt *clientes, int (*comparaClientes[DIM])(void*,void*),
        TabelaHashPTR *localidades, int (*func_compare)(void*,void*), int(*hash_function)(void*,int) );

char* novaString(unsigned int n);
void serial_clienteRec( TreePt thisTree, FILE *file );
void serial_cliente( MainTreePt thisMainTree, FILE *file );
void serial_camiaoRec( TreePt thisTree, FILE *file );
void serial_camiao( MainTreePt thisMainTree, FILE *file );

#endif /* MENU_H_INCLUDED */

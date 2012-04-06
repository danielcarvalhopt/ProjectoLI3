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


void serialize(TabelaHashPTR tabela, MainTreePt camioes, MainTreePt clientes);
void deserialize();

#endif /* MENU_H_INCLUDED */

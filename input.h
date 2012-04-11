/**
 * @file input.h
 * @brief Módulo de input (definições)
 * @details Tem funções para receber input do utilizador 
 * */
#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "dados.h"

struct sSampleLocalidades{
    char nome[113];
    int lig[9];
};

/**
 * @brief Lê uma variável do tipo double.
 * @details Primeiro verifica se a string introduzida corresponde a um número no formato decimal, depois faz parsing da string para um double
 * @return Variável decimal de dupla precisão com o número introduzido pelo utilizador 
 * */
double readDouble();

/**
 * @brief Lê uma variável do tipo inteiro sem sinal
 * @return O inteiro sem sinal introduzido pelo utilizador
 * */
unsigned int readUInt();

/**
 * @brief Lê uma variável do tipo inteiro
 * @return O inteiro introduzido pelo utilizador
 * */
int readInt();

/**
 * @brief  Lê um conjunto de caracteres
 * @details Começa por criar um String buffer, depois vai ler caracteres para o buffer até ler \0, \n ou chegar ao limite do buffer. No caso de chegar ao limite do buffer é enviado um sinal específico. 
 * @param ptr Um apontador que vai apontar para a nova string
 * @return -1 se leu a string, mas teve de a cortar porque era maior que o buffer
 * @return 0 se não consguiu alocar espaço para a string
 * @return 1 se teve sucesso na leitura dos caracteres
 * @see allocStr()
 * */
int lerStr(char **ptr);


//
//
//  FUNÇOES DE INPUT ESPECÍFICAS
//
//

void inserelocalidadeinput(TabelaHashPTR table);
void removelocalidadeinput(TabelaHashPTR table);
void insereligacaoinput(TabelaHashPTR table);
void removeligacaoinput(TabelaHashPTR table);
void imprimeLocalidades (TabelaHashPTR table);
void imprimelistaligacoesinput(TabelaHashPTR localidades);
void editaligacaoinput(TabelaHashPTR localidades);

/**
 * @brief Imprime ligações de uma determinada localidade
 * @details Imprime ligações de uma determinada localidade passada como argumento da função mostrando as localidades, o custo e a distância entre elas.
 * @param lista Apontador de Lista Ligada para uma localidade
 * */
void imprimelistaligacoes(LinkedListPTR lista);

/**
 * @brief Imprime todas as localidades existentes nos indices da tabela de Hash
 * @details 
 * @param lista Apontador de Lista Ligada para uma lista de localidades existentes nos indices da tabela de hash
 * */
void imprimelista(LinkedListPTR lista);



/**
 * @brief Providencia a sequência de input necessária para inserir um novo camião
 * @param camioes apontador para a estrutura de controlo da árvore de camiões
 * @param localidades apontador para a estrutura de controlo da tabela de hash de localidades
 * */
void camiaoi_insere(MainTreePt camioes, TabelaHashPTR localidades);


int reSampleLocalidades();
int reSampleUser();


#endif /* INPUT_H_INCLUDED */

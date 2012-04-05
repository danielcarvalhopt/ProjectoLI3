/**
 * @file input.h
 * @brief Módulo de input (definições)
 * @details Tem funções para receber input do utilizador 
 * */
#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

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
 * @details Começa por criar um array de caracteres de tamanho fixo,
 *          depois aloca espaço em memória suficiente para conter o
 *          conjunto de caracteres lido e devolve um apontador para
 *          o início do espaço criado.
 * @param ptr O apontador que vai ficar a apontar para a String lida
 * @return Um apontador para o primeiro caracter da sequência lida
 * @see allocStr()
 * */
char* readStr(char *ptr);

/**
 * @brief  Lê um conjunto de caracteres
 * @details Começa por criar um String buffer, depois vai ler caracteres para o buffer até ler \0, \n ou chegar ao limite do buffer. No caso de chegar ao limite do buffer é enviado um sinal específico. 
 * @param ptr O apontador que vai ficar a apontar para a String lida
 * @return -1 se leu a string, mas teve de a cortar porque era maior que o buffer
 * @return 0 se não consguiu alocar espaço para a string
 * @return 1 se teve sucesso na leitura dos caracteres
 * @see allocStr()
 * */
int lerStr(char *ptr);

#endif /* INPUT_H_INCLUDED */

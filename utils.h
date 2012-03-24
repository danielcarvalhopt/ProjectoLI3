/**
 * @file utils.h
 * @brief Módulo de utilitários
 * @details Contém algumas funções que são necessárias ao longo do código mas não pertencem a nenhum dos outros módulos
 * */
#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

//////////////////////////////////
//
// I/O geral
//
//////////////////////////////////

/**
 * @brief Descarta os caracteres que estejam no stdin
 * */
void clearInputBuffer();

/**
 * @brief Selecciona o sistema operativo com base no sucesso de alguns comandos
 * */
void chooseSO();

/**
 * @brief Limpa o texto e coloca o cursor no topo da consola
 * */
void clearScreen();

//////////////////////////////////
//
// inteiros
//
//////////////////////////////////

/**
 * @brief Verifica se o inteiro sem sinal é válido
 * @details De acordo com o funcionamento do programa, todo o inteiro
 *          diferente de INT_MAX é válido.\n
 *          INT_MAX é o maior inteiro representável.
 * @param n Número que se pretende verificar se é inteiro sem sinal
 * @return Um inteiro com o seguinte significado:
 *         0 - n não é um inteiro sem sinal válido
 *         1 - n é um inteiro sem sinal válido
 * */
int isUInt(unsigned int n);


/**
 * @brief Verifica se o inteiro é válido
 * @details De acordo com o funcionamento do programa, todo o inteiro
 *         diferente de INT_MAX é válido.\n
 *         INT_MAX é o maior inteiro representável.
 * @param n Número que se pretende verificar se é inteiro
 * @return Um inteiro com o seguinte significado:
 *         0 - n não é um inteiro válido
 *         1 - n é um inteiro válido
 * */
int isInt(int n);

/**
 * @brief Escolhe o maior de dois inteiros
 * @param a primeiro inteiro
 * @param b segundo inteiro
 * @return O maior dos dois inteiros
 * */
int maxInt(int a, int b);

/**
 * @brief Compara dois inteiros
 * @param a primeiro inteiro
 * @param b segundo inteiro
 * @return Um inteiro com o seguinte significado:
 *         -1 se a<b
 *          0 se a=b
 *          1 se a>b
 * */
int intcmp(int a, int b);

/**
 * @brief Compara dois inteiros sem sinal
 * @param a primeiro inteiro sem sinal
 * @param b segundo inteiro sem sinal
 * @return Um inteiro com o seguinte significado:
 *         -1 se a<b
 *          0 se a=b
 *          1 se a>b
 * */
int uintcmp(unsigned int a, unsigned int b);

//////////////////////////////////
//
// double
//
//////////////////////////////////

/**
 * @brief Verifica se o numero real de dupla precisão é válido
 * @details De acordo com o funcionamento do programa, os números
 *          reais de dupla precisão que não são válidos têm o valor
 *          de NaN (Not a Number) ou +/-infinito.
 * @param n Número que se pretende verificar se é real de dupla precisão
 * @return Um inteiro com o seguinte significado:
 *         0 - n não é um real de dupla precisão válido
 *         1 - n é um real de dupla precisão válido
 * */
int isDouble(double n);

//////////////////////////////////
//
// strings
//
//////////////////////////////////

/**
 * @brief Copia uma string para outra
 * @details Aloca espaço para uma string de tamanho igual à string em src,
 *          coloca o apontador dest a apontar para esse espaço e copia o
 *          conteúdo da origem (src) para o destino (dest).
 * @param dest String de destino
 * @param src String de origem
 * @return Um apontador para a cópia da string em src
 *         NULL se não conseguir alocar espaço para a nova string
 * */
char* allocStr(char *dest, char *src);

/**
 * @brief Concatena src em dest
 * @details Realoca espaço em memória para que as duas strings possam ser
 *          inseridas no espaço apontado por dest. Depois concatena as duas
 *          strings nesse espaço.
 * @param dest String de destino
 * @param src String de destino
 * @return Uma string com a concatenação das duas strings que são passadas como argumento
 * */
char* concatStr(char *dest, char *src);

/*
funções sem interesse--

char* extendStr(char *str, int i);
char* addCharEnd(char *dest, char chr);
char* addnCharEnd(char *dest, char chr, int i);
char* addChar(char *dest, char chr);
char* addnChar(char *dest, char chr, int i);
*/

#endif /* UTILS_H_INCLUDED */

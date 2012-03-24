/**
 * @file dados.h
 * @brief Estruturas e Funções específicas dos dados
 * @details Estruturas dos vários modelos de dados e funções para inicializar, comparar, ...
 * */
#ifndef DADOS_H_INCLUDED
#define DADOS_H_INCLUDED

#include "mod_lista_ligada.h"
#include "mod_avl_n_dimensional.h"
#include "mod_tabela_hash.h"

//
// Funções e estruturas dos camiões
//

/**
 * @brief Estrutura de dados que define um Camiao.
 * @param id Identificador único do camião
 * @param matricula Matrícula do camião
 * @param custo Gasto por Km em função do consumo e desgaste do veiculo
 * @param peso Peso máximo que o camião pode transportar 
 * */
typedef struct sCamiao{
    unsigned int id;
    char *matricula;
    double custo;
    double peso;
} Camiao, *CamiaoPt;

/**
 * @brief Escreve de uma forma simplista a informação sobre determinado camião
 * @param camiao Apontador para o camião cuja informação se quer imprimir
 * */
void camiao_dump( void* camiao );

/**
 * @brief Compara o campo Id de dois camiões
 * @param camiaoUm O primeiro camião
 * @param camiaoDois O segundo camião
 * @return Um valor inteiro que representa a comparação dos campos Id dos dois camiões
 *         -1 se o primeiro id for menor que o segundo
 *          0 se os id forem iguais
 *          1 se o primeiro id for maior que o segundo
 * */
int camiao_compararId(void* camiaoUm, void* camiaoDois);

/**
 * @brief Compara o campo matricula de dois camiões
 * @param camiaoUm O primeiro camião
 * @param camiaoDois O segundo camião
 * @return Um valor inteiro que representa a comparação dos campos matricula dos dois camiões
 *         -1 se a matricula do primeiro for considerada menor que a do segundo
 *          0 se as matriculas forem iguais
 *          1 se a matricula do primeiro for considerada maior que a do segundo
 * */
int camiao_compararMatricula(void* camiaoUm, void* camiaoDois);

/**
 * @brief Inicializa uma nova variável camiao
 * @details Aloca espaço em memória para uma nova variável do tipo camiao,
 *          depois preenche os dados do camião de acordo com os argumentos
 *          passados à função.\n
 *          Por fim retorna um apontador para o espaço alocado.
 * @param id Inteiro sem sinal que representa o identificador único do camião
 * @param matricula Conjunto de caracteres que representam a matrícula do camião
 * @param custo Valor real de dupla precisão que representa o gasto por km associado ao camião
 * @param peso Valor real de dupla precisão que representa o peso máximo que o camião pode transportar
 * @return Um apontador para o novo camião
 * @see Camiao
 * */
CamiaoPt camiao_novo( unsigned int id, char *matricula, double custo, double peso );

//
// Funções e estruturas dos clientes
//

/**
 * @brief Estrutura de dados que define um Cliente
 * @param nif Número de Identificação Fiscal (nº contribuinte) do cliente 
 * @param nome Nome do cliente
 * @param morada Morada do cliente
 * @param serviços Apontador para a estrutura de controlo da lista de serviços anteriores do cliente 
 * */
typedef struct sCliente{
    unsigned int nif;
    char *nome;
    char *morada;
    MainListPTR servicos;
} Cliente, *ClientePt;

/**
 * @brief Compara o campo Nif de dois clientes
 * @param clienteUm O primeiro cliente
 * @param clienteDois O segundo cliente
 * @return Um valor inteiro que representa a comparação dos campos Nif dos dois clientes
 *         -1 se o nif do primeiro for menor que o do segundo
 *          0 se os nif forem iguais
 *          1 se o nif do primeiro for maior que o do segundo
 * */
int cliente_compararNif(void* clienteUm, void* clienteDois);

/**
 * @brief Compara o campo Nome de dois clientes
 * @param clienteUm O primeiro cliente
 * @param clienteDois O segundo cliente
 * @return Um valor inteiro que representa a comparação dos campos Nome dos dois clientes
 *         -1 se o nome do primeiro for considerado menor que o nome do segundo
 *          0 se os nomes forem iguais
 *          1 se o nome do primeiro for considerado maior que o nome do segundo
 * */
int cliente_compararNome(void* clienteUm, void* clienteDois);

/**
 * @brief Escreve de uma forma simplista a informação sobre determinado cliente
 * @param cliente Apontador para o cliente cuja informação se quer imprimir
 * */
void cliente_dump( void* cliente );

/**
 * @brief Inicializa uma nova variável cliente
 * @details Aloca espaço em memória para uma nova variável do tipo cliente,
 *          depois preenche os dados do cliente de acordo com os argumentos
 *          passados à função.\n
 *          Por fim retorna um apontador para o espaço alocado.
 * @param nif Inteiro sem sinal que representa o contribuinte do cliente
 * @param nome Conjunto de caracteres que representam o nome do utilizador
 * @param morada Conjunto de caracteres que representam a morada do utilizador
 * @param servicos Apontador para a estrutura de controlo da lista de serviços anteriores do cliente
 * @return Um apontador para o novo cliente
 * @see Cliente
 * */
ClientePt cliente_novo( unsigned int nif, char *nome, char *morada, MainListPTR servicos );

/**
 * @brief Substitui os dados de um cliente com determinado Nome
 * @details A função procura o cliente pelo Nome, depois cria um novo
 *          cliente com os argumentos passados à função e com a lista
 *          de serviços anteriores do cliente que encontrou.\n
 *          Por fim, apaga o cliente que encontrou e insere o que criou.
 * @param clientesPt Apontador para a estrutura de controlo da árvore de clientes
 * @param procuraNome Nome do cliente que se quer modificar
 * @param nif Novo nif do cliente
 * @param nome Novo nome do cliente
 * @param morada Nova morada do cliente
 * @return Um inteiro com o seguinte significado:
 *         -1 - Não foi encontrado nenhum cliente
 *          0 - O cliente foi removido mas não foi inserido um novo
 *          1 - O cliente foi removido e foi inserido um novo
 * */
int cliente_substituiPeloNome( MainTreePt clientesPt, char *procuraNome, unsigned int nif, char *nome, char *morada );

/**
 * @brief Substitui os dados de um cliente com determinado Nif
 * @details A função procura o cliente pelo Nif, depois cria um novo
 *          cliente com os argumentos passados à função e com a lista
 *          de serviços anteriores do cliente que encontrou.\n
 *          Por fim, apaga o cliente que encontrou e insere o que criou.
 * @param clientesPt Apontador para a estrutura de controlo da árvore de clientes
 * @param procuraNif Nif do cliente que se quer modificar
 * @param nif Novo nif do cliente
 * @param nome Novo nome do cliente
 * @param morada Nova morada do cliente
 * @return Um inteiro com o seguinte significado:
 *         -1 - Não foi encontrado nenhum cliente
 *          0 - O cliente foi removido mas não foi inserido um novo
 *          1 - O cliente foi removido e foi inserido um novo
 * */
int cliente_substituiPeloNif( MainTreePt clientesPt, unsigned int procuraNif, unsigned int nif, char *nome, char *morada );

/**
 * @brief Obtém a lista de serviços anteriores de um cliente
 * @details Obtém o apontador para a estrutura de controlo da
 *          lista de serviços anteriores do cliente a partir
 *          da subárvore que aponta para o cliente.
 * @param thisTreePt Subárvore que aponta para o cliente
 * @return Apontador para a estrutura de controlo da lista de serviços anteriores do cliente
 * */
MainListPTR cliente_getServico( TreePt thisTreePt );


//
// Funções e estruturas das Localidades
//

typedef struct Ligacoesida{
	char* nome;
	float custo;
	float distancia;
}*LigacoesidaPTR;

typedef struct Ligacoesvinda{
	char* nome;
}*LigacoesvindaPTR;


typedef struct Localidade{
	char* nome;
	MainListPTR ligacoesida;
	MainListPTR ligacoesvinda;
}*LocalidadePTR;

// função de input
void removeligacaoinput(TabelaHashPTR table);

int removerligacao (TabelaHashPTR table, char *nomeorigem, char *nomedestino);
void imprimelistaligacoes(LinkedListPTR lista);
void hashprint (TabelaHashPTR table);
void imprimelista(LinkedListPTR lista);
int removerligacao (TabelaHashPTR table, char *nomeorigem, char *nomedestino);
int inserirligacao(TabelaHashPTR table, char *nomeorigem, char *nomedestino, float custo, float distancia);
LigacoesvindaPTR crialigacaovinda (char* nome);
LigacoesidaPTR crialigacaoida (char* nome, float custo, float distancia);
int removerlocalidade (TabelaHashPTR table, char *nome);
int inserelocalidade (TabelaHashPTR table, char *nome);
LocalidadePTR crialocalidade (char* nome);
int compareligacoesvinda (void *a, void *b);
int compareligacoesida (void *a, void *b);
int comparalocalidades (void *a, void *b);

/**
 * @brief Remove a ligação entre duas localidades
 * @param table Apontador para a tabela de hash
 * @param nomeorigem Nome da cidade que serve de ponto de partida
 * @param nomedestino Nome da cidade que serve de ponto de chegada
 * @return -1 Não encontrou localidades
 * @return 0  Não encontrou ligação
 * @return 1  Removeu a ligação
 * */
int removerligacao (TabelaHashPTR table, char *nomeorigem, char *nomedestino);


void inserelocalidadeinput(TabelaHashPTR table);
void removelocalidadeinput(TabelaHashPTR table);
void insereligacaoinput(TabelaHashPTR table);
void removeligacaoinput(TabelaHashPTR table);

/*
//
// Funções e estruturas dos serviços anteriores
//

typedef struct sServico{

} Servico, *ServicoPt;

//
// Mais coisas?
// 
*/

#endif /* DADOS_H_INCLUDED */

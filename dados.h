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
    char *local;
} Camiao, *CamiaoPt;

/**
 * @brief Array das funções de comparação
 * */
int (*comparaCamioes[DIM])(void*,void*);


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
CamiaoPt camiao_novo( unsigned int id, char *matricula, double custo, double peso, char *local );
int camiao_substituiPelaMatricula( MainTreePt camiaoPt, char *procuraMatricula, double custo, double peso, char *local );
void camiaoMaisBaratoRec( TreePt thisTree, char *local, CamiaoPt *camiao );
CamiaoPt camiaoMaisBarato( MainTreePt camioes, char *local );

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
 * @brief Array das funções de comparação
 * */
int (*comparaClientes[DIM])(void*,void*);

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
 * @brief Procura um cliente pelo nif
 * @param clientesPt um apontador para a estrutura de controlo da árvore de clientes
 * @param nif numero de contribuinte do cliente
 * @return NULL caso não tenha encontrado uma correspondencia
 * @return Um ClientePt caso tenha encontrado
 * */
ClientePt cliente_procuraNif( MainTreePt clientesPt, unsigned int nif);

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
/**
    @brief Estrutura de que identifica as localidades às quais uma localidade se liga
    @param nome Nome da localidade para onde se estabeleceu uma ligação
    @param custo Custo associado à ligação
    @param distancia Distancia entre as localidades
 */
typedef struct Ligacoesida{
	char* nome;
	double custo;
	double distancia;
}*LigacoesidaPTR;

/**
    @brief Estrutura de que identifica as localidades que fazem ligação a uma determinada localidade
    @param nome Nome da localidade com quem existe ligação
 */
typedef struct Ligacoesvinda{
	char* nome;
}*LigacoesvindaPTR;


/**
    @brief Estrutura de que identifica uma localidade
    @param nome Nome da localidade
    @param ligacoesida Lista de ligações às quais a localidade se liga
    @param ligacoesvinda Lista de ligações da localidades que se ligam à localidade
 */
typedef struct Localidade{
	char* nome;
	MainListPTR ligacoesida;
	MainListPTR ligacoesvinda;
}*LocalidadePTR;



int hash_function (void *localidade, int hashsize);

/**
    @brief Pede a inserção do nome das localidades de onde se pretende remover uma ligação
    @details Pede a inserção do nome das localidades de onde se pretende remover uma ligação invocando as
             funções correspondentes que o fazem e imprime mensagem de sucesso ou não conforme o resultado da operação
    @param table Tabela de Hash com as localidades
 */
void removeligacaoinput(TabelaHashPTR table);


/**
 * @brief Remove a ligação entre duas dadas localidades
 * @details Remove uma ligação entre duas dadas localidades fazendo a verificação se as localidades existem e se a ligação existe
 * @param table Tabela de Hash com as localidades
 * @param nomeorigem String com o nome da localidade de origem da ligação
 * @param nomedestino String com o nome da localidade de destino da ligação
 * @return -1 Caso localidades não existam
 * @return 0 Caso ligação não exista
 * @return 1 Caso seja removida com sucesso
 * */
int removerligacao (TabelaHashPTR table, char *nomeorigem, char *nomedestino);


/**
 * @brief Imprime todas as localidades inseridas no programa invocando uma função auxiliar de output
 * @details 
 * @param table Tabela de Hash com as localidades
 * */
void hashprint (TabelaHashPTR table);



/**
 * @brief Insere uma ligação entre duas localidades
 * @details Insere uma ligação entre duas dadas localidades fazendo a verificação se as localidades existem e se a ligação existe
 * @param table Tabela de Hash com as localidades
 * @param nomeorigem String com o nome da localidade de origem da ligação
 * @param nomedestino String com o nome da localidade de destino da ligação
 * @param custo Custo associado à ligação entre localidades
 * @param distancia Distância entre as duas localidades
 * @return -1 Caso localidades não existam
 * @return 0 Caso ligação já exista
 * @return 1 Caso seja inserida com sucesso
 * */
int inserirligacao(TabelaHashPTR table, char *nomeorigem, char *nomedestino, double custo, double distancia);

/**
 * @brief Aloca espaço e cria para uma estrutura de dados do tipo ligacaovinda
 * @details 
 * @param nome String com o nome da localidade
 * @return Apontador para a estrutura criada ou NULL caso não seja possível alocar memória
 * */
LigacoesvindaPTR crialigacaovinda (char* nome);

/**
 * @brief Aloca espaço e cria para uma estrutura de dados do tipo ligacaoida
 * @details 
 * @param nome String com o nome da localidade
 * @param custo Custo de ida para a localidade inserida
 * @param distancia Distancia para a localidade inserida
 * @return Apontador para a estrutura criada ou NULL caso não seja possível alocar memória
 * */
LigacoesidaPTR crialigacaoida (char* nome, double custo, double distancia);

/**
 * @brief Remove uma localidade da tabela de Hash
 * @details
 * @param table Tabela de Hash com as localidades
 * @param nome String com o nome da localidade a remover
 * @return 1 Caso seja removida com sucesso
 * @return 0 Caso não seja removida com sucesso
 * */
int removerlocalidade (TabelaHashPTR table, char *nome);

/**
 * @brief Insere uma localidade na tabela de Hash
 * @details 
 * @param table Tabela de Hash com as localidades
 * @param nome String com o nome da localidade a inserir
 * @return 1 Caso seja inserida com sucesso
 * @return 0 Caso não seja inserida com sucesso
 * */
int inserelocalidade (TabelaHashPTR table, char *nome);

/**
 * @brief Cria uma estrutura de localidade
 * @details
 * @param nome String com o nome da localidade a criar
 * @return Apontador para a estrutura criada
 * */
LocalidadePTR crialocalidade (char* nome);

/**
 * @brief Compara duas estruturas de dados ligacoesvinda
 * @details 
 * @param a Ligação a comparar
 * @param b Ligação a comparar
 * @return 1 Caso sejam iguais
 * @return 0 Caso sejam diferentes
 * */
int compareligacoesvinda (void *a, void *b);

/**
 * @brief Compara duas estruturas de dados ligacoesida
 * @details 
 * @param a Ligação a comparar
 * @param b Ligação a comparar
 * @return 1 Caso sejam iguais
 * @return 0 Caso sejam diferentes
 * */
int compareligacoesida (void *a, void *b);

/**
 * @brief Compara duas estruturas de dados localidade
 * @details 
 * @param a Localidade a comparar
 * @param b Localidade a comparar
 * @return 1 Caso sejam iguais
 * @return 0 Caso sejam diferentes
 * */
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
void freeLocalidade(LocalidadePTR localidade);
void freeLigacaoVinda(LigacoesvindaPTR ligacao);
void freeLigacaoIda(LigacoesidaPTR ligacao);
double costCheapestPath(TabelaHashPTR localidades, char* localidadeorigem, char* localidadedestino, double custoCamiaoKm);
//
// Funções e estruturas dos serviços anteriores
//
/**
 * @brief Estrutura de dados que define um serviço anterior 
 * @param datahora Data e hora do pedido
 * @param camiao Camião que fez o serviço (matricula)
 * @param origem Local onde estava o camião antes do pedido
 * @param carga Local para onde o camião se deslocou para ser carregado
 * @param destino Local para onde o camião transportou a carga
 * */
typedef struct sServico{
    char *datahora; // "AAAA-MM-DD HH:MM:SS"
    char *camiao; //matricula do camiao
    double custo;
    double peso;
    char *origem;
    char *carga;
    char *destino;
} Servico, *ServicoPt;

/**
 * @brief Insere um serviço na lista de serviços
 * @param nif Nif do cliente a associar ao serviço
 * @param thisCamiao O camiao a associar ao serviço
 * @param origem Local onde estava o camião antes do pedido
 * @param carga Local para onde o camião se deslocou para ser carregado
 * @param destino Local para onde o camião transportou a carga
 * @return -2 Não encontrou o cliente
 * @return -1 Não conseguiu alocar
 * @return 0 Não conseguiu inserir ou não conseguiu gerar a data e hora
 * @return 1 Inseriu o serviço na lista
 * */
int cliente_insereServico( MainTreePt clientesPt, unsigned int nif, char *camiao, double custo, double peso, char *origem, char *carga, char *destino );

/**
 * @brief Compara as datas de dois serviços
 * @param servUm Primeiro serviço
 * @param servDois Segundo serviço
 * @return <0 Primeira data é anterior à segunda
 * @return =0 As datas sao iguais
 * @return >0 Primeira data é posterior à segunda
 * */
int cliente_comparaServico( void* servUm, void* servDois );

//
// Mais coisas?
// 


#endif /* DADOS_H_INCLUDED */

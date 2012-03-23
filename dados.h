// metemos aqui as definições das estruturas de dados e das funções de comparação, output, clone, etc
//
// as definições das funções devem ser do género:
// tipo transporte_novo(argumentos)
// tipo transporte_compara(argumentos)
//
//


//
// Funções e estruturas dos camiões
//

typedef struct sCamiao{
    unsigned int id;
    char *matricula;
    float custo; //por Km
} Camiao, *CamiaoPt;

void camiao_dump( void* camiao );
int camiao_compararId(void* camiaoUm, void* camiaoDois);
int camiao_compararMatricula(void* camiaoUm, void* camiaoDois);
CamiaoPt camiao_novo( unsigned int id, char *matricula, float custo );

//
// Funções e estruturas dos clientes
//

typedef struct sCliente{
    unsigned int nif; //numero de identificacao fiscal = contribuinte
    char *nome;
    char *morada;
} Cliente, *ClientePt;

int cliente_compararNif(void* clienteUm, void* clienteDois);
int cliente_compararNome(void* clienteUm, void* clienteDois);
void cliente_dump( void* cliente );
ClientePt cliente_novo( unsigned int nif, char *nome, char *morada );


//
// Funções e estruturas das Localidades
//

typedef struct sLocal{

} Local, *LocalPt;

//
// Funções e estruturas dos serviços anteriores
//

typedef struct sServico{

} Servico, *ServicoPt;

//
// Mais coisas?
// 




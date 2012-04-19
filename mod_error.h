/* Erros gerais */
#define ERROR_SUCCESS		 	0		// Operação executada com sucesso!
#define ERROR_MEMALOC 			1 		// Não foi possível executar a operação por falta de memória!

/* Erros Localidades */
#define ERROR_LOCEXIST 			2 		// Localidade(s) já existe(m)!
#define ERROR_LOCNOTEXIST 		3 		// Localidade(s) não existe(m)!
#define ERROR_LIGLOCEXIST 		4 		// Ligação entre localidades já existe!
#define ERROR_LIGLOCNOTEXIST            5               // Ligação entre localidades não existe!
#define ERROR_NOLIGS 			6 		// Não existem ligações a partir desta localidade!

#define ERROR_NOCAMLOC			7               // Não existe um camião nessa localidade
#define ERROR_NOPATH			8               // Não há caminho spossiveis entre as localidades
#define ERROR_CANCEL			9               // Operacao cancelada pelo utilizador

#define ERROR_INVALID_VALI              10              // Valor inválido (veja as instruções acima)


typedef struct error
{
  char *error_code;
  char *message;
} Error;


int errorMessage(int error_code);

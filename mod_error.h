/* Erros gerais */
#define ERROR_SUCCESS		 	0		// Operação executada com sucesso!
#define ERROR_MEMALOC 			1 		// Não foi possível executar a operação por falta de memória!

/* Erros Localidades */
#define ERROR_LOCEXIST 			2 		// Localidade(s) já existe(m)!
#define ERROR_LOCNOTEXIST 		3 		// Localidade(s) não existe(m)!
#define ERROR_LIGLOCEXIST 		4 		// Ligação entre localidades já existe!
#define ERROR_LIGLOCNOTEXIST 	5 		// Ligação entre localidades não existe!
#define ERROR_NOLIGS 			6 		// Não existem ligações a partir desta localidade!


typedef struct error
{
  char *error_code;
  char *message;
} Error;


int errorMessage(int error_code);

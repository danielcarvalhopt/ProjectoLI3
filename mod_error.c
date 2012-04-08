#include <stdio.h>
#include "mod_error.h"

typedef struct error
{
  char *error_code;
  char *message;
} Error;

static Error errors[] =
{
  /* Erros Gerais */
  {"ERROR_SUCCESS",	"Operação executada com sucesso!"},
  {"ERROR_MEMALOC",	"Não foi possível executar a operação por falta de memória!"},
  /* Erros Localidades */
  {"ERROR_LOCEXIST",	"Localidade(s) já existe(m)!"},
  {"ERROR_LOCNOTEXIST",	"Localidade(s) não existe(m)!"},
  {"ERROR_LIGLOCEXIST",		"Ligação entre localidades já existe!"},
  {"ERROR_LIGLOCNOTEXIST",	"Ligação entre localidades não existe!"},
  {"ERROR_NOLIGS",	"Não existem ligações para esta localidade!"}
  /*      -------      */
};


int errorMessage(int error_code)
{
  fprintf(stderr, "%s: %s\n", errors[error_code].error_code, errors[error_code].message);
  return error_code;
}

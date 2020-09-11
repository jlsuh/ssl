#include "lexema.h"
#include "scanner.h"

void contarLexema(int resultado, int lexemasEncontrados[]){
  switch(resultado){
    case tokenIdentificador:
      lexemasEncontrados[tokenIdentificador] += 1;
      break;
    case tokenConstanteEntera:
      lexemasEncontrados[tokenConstanteEntera] += 1;
      break;
    case tokenNumeral:
      lexemasEncontrados[tokenNumeral] += 1;
      break;
    case tokenError:
      lexemasEncontrados[tokenError] += 1;
      break;
  }
}

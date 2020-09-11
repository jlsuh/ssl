#include <stdio.h>
#include <stdlib.h>
#include "lexema.h"
#include "scanner.h"

int main(int argc, const char*argv[]){
  int resultado;
  int lexemasEncontrados[] = {0 /*Identificadores*/, 0 /*Constantes enteras*/, 0 /*Numerales*/, 0 /*Errores*/};

  while(resultado != tokenFDT){
    resultado = scanFlujo();  // Invocación del scanner
    switch(resultado){
      case tokenIdentificador:
        printf("identificador\n");
        break;
      case tokenConstanteEntera:
        printf("constante entera\n");
        break;
      case tokenNumeral:
        printf("Numeral\n");
        break;
      case tokenError:
        printf("error\n");
        break;
    }
    contarLexema(resultado, lexemasEncontrados);
  }

  /* Show lexemas encontrados */
  printf("----\nTotales:\n");
  printf("Identificadores %d\n", lexemasEncontrados[tokenIdentificador]);
  printf("Constantes enteras %d\n", lexemasEncontrados[tokenConstanteEntera]);
  printf("Numerales %d\n", lexemasEncontrados[tokenNumeral]);
  printf("Errores %d\n", lexemasEncontrados[tokenError]);

  return EXIT_SUCCESS;
}

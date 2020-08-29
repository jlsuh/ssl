#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

int main(){
  int resultado;

  FILE *archivo = fopen("datosPrueba.txt", "r");
  if(archivo == NULL){
    printf("Error al intentar abrir el archivo...");
  }

  while(resultado != tokenFDT){
    resultado = analizarCadena(archivo);
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
  }

  fclose(archivo);

  return EXIT_SUCCESS;
}














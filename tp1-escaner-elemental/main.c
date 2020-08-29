#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

int main(){
  FILE *archivo = fopen("datosPrueba.txt", "r");
  int resultado;
//  imprimirContenido(archivo);

//  int array[] = {1,2,3};
//
//  int aux = longitudArray(array);
//
//  printf("long. array: %d",aux);

  while(resultado != 3){
    resultado = analizador(archivo);
    switch(resultado){
    case 0:
      printf("identificador\n");
      break;
    case 1:
      printf("constante entera\n");
      break;
    case 2:
      printf("Numeral\n");
      break;
    case 4:
      printf("error\n");
      break;
    }
  }

  fclose(archivo);

  return EXIT_SUCCESS;
}














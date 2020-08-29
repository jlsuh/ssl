#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

int main(){
  FILE *archivo = fopen("datosPrueba.txt", "r");

  imprimirContenido(archivo);

  int array[] = {1,2,3};

  int aux = longitudArray(array);

  printf("long. array: %d",aux);

  fclose(archivo);

  return EXIT_SUCCESS;
}














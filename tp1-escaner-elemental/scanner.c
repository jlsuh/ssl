#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "scanner.h"

#define CANT_ESTADOS_ACEPTORES 4
#define CANT_ESTADOS_CENTINELA 4
#define CANT_COLUMNAS 6
#define CANT_FILAS 5

const int ESTADO_INICIAL = E0;

const int ESTADOS_ACEPTORES[CANT_ESTADOS_ACEPTORES] = {E5, E99, E129, E189};

const int TT[CANT_FILAS][CANT_COLUMNAS] = {
/* T.T     L     D     #     seq. escape  Otro  fdt*/
/* E0- */ {E1,   E2,   E4,   E0,          E3,   E5},
/* E1  */ {E1,   E1,   E99,  E99,         E99,  E99},
/* E2  */ {E129, E2,   E129, E129,        E129, E129},
/* E3  */ {E159, E159, E159, E159,        E3,   E159},
/* E4  */ {E189, E189, E189, E189,        E189, E189}
};

/*
* Para la posteridad:
* En caso de agregar algún otro lexema a reconocer más, no olvidar de modificar el switch que evalúa el estado.
* Modificar defines de CANT_FILAS y CANT_ESTADOS_ACEPTORES (en caso que amerite).
*/

int scanFlujo(void){
  int estado = ESTADO_INICIAL;
  char *caracterLeido = malloc(sizeof(char));

  while(estado < E5){
    *caracterLeido = getchar();
    int simbolo = categorizarCaracter(*caracterLeido);
    estado = TT[estado][simbolo];
  }

  if(esAceptor(estado)){
    ungetc(*caracterLeido, stdin);
    free(caracterLeido);
    switch(estado){
      case E99:
        return tokenIdentificador;
      case E129:
        return tokenConstanteEntera;
      case E189:
        return tokenNumeral;
      case E5:
        return tokenFDT;
    }
  }

  ungetc(*caracterLeido, stdin);
  free(caracterLeido);
  return tokenError;
}

int categorizarCaracter(int c){
  if(isalpha(c)){
    return COL0; // Columna de letras
  } else if(isdigit(c)){
    return COL1; // Columna de dígitos
  } else if(c == '#'){
    return COL2; // Columna de numeral
  } else if(isspace(c)){
    return COL3; // Columna secuencias escapes
  } else if(c == EOF){
    return COL5; // Columna fin de texto
  }
  return COL4; // Columna otros
}

int esAceptor(int estado){
  return esUnoDe(estado, CANT_ESTADOS_ACEPTORES, ESTADOS_ACEPTORES);
}

int esUnoDe(int estado, const int CANTIDAD, const int ESTADOS_QUE_CUMPLEN[]){
  for(int i = 0; i < CANTIDAD; i += 1){
    if(estado == ESTADOS_QUE_CUMPLEN[i]){
      return 1;
    }
  }
  return 0;
}

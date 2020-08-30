#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"

#define CANT_ESTADOS_ACEPTORES 4
#define CANT_ESTADOS_CENTINELA 4
#define CANT_COLUMNAS 7
#define CANT_FILAS 5

const int ESTADO_INICIAL = E0;

const int ESTADOS_CENTINELA[CANT_ESTADOS_CENTINELA] = {E5, E99, E129, E189};
const int ESTADOS_ACEPTORES[CANT_ESTADOS_ACEPTORES] = {E5, E99, E129, E189};

const int TT[CANT_FILAS][CANT_COLUMNAS] = {
/* T.T     L     0     D     #     seq. escape  Otro  fdt*/
/* E0- */ {E1,   E3,   E2,   E4,   E0,          E3,   E5},
/* E1  */ {E1,   E1,   E1,   E99,  E99,         E99,  E99},
/* E2  */ {E129, E2,   E2,   E129, E129,        E129, E129},
/* E3  */ {E159, E159, E159, E159, E159,        E3,   E159},
/* E4  */ {E189, E189, E189, E189, E189,        E189, E189}
};

/*
* Para la posteridad:
* En caso de agregar algún otro lexema a reconocer más, no olvidar de modificar el switch que evalúa el estado.
* Modificar defines de CANT_FILAS, CANT_ESTADOS_ACEPTORES (en caso que amerite), CANT_ESTADOS_CENTINELA (en caso que amerite).
*/

int scanFlujo(FILE* archivo, int lexemasEncontrados[]){
  int estado = ESTADO_INICIAL;
  char *caracterLeido = malloc(sizeof(char));

  while(estado < E5){
    *caracterLeido = getc(archivo);
    int simbolo = categorizarCaracter(caracterLeido);
    estado = TT[estado][simbolo];
  }

  if(esAceptor(estado)){
    if(esCentinela(estado)){
      ungetc(*caracterLeido, archivo);
      free(caracterLeido);
      switch(estado){
      case E99:
        lexemasEncontrados[tokenIdentificador] += 1;
        return tokenIdentificador;
      case E129:
        lexemasEncontrados[tokenConstanteEntera] += 1;
        return tokenConstanteEntera;
      case E189:
        lexemasEncontrados[tokenNumeral] += 1;
        return tokenNumeral;
      case E5:
        return tokenFDT;
      }
    }
  } else {
    ungetc(*caracterLeido, archivo);
    free(caracterLeido);
    lexemasEncontrados[tokenError] += 1;
    return tokenError;
  }

  return -1;
}

int categorizarCaracter(char *c){
  if(isalpha(*c)){
    return COL0; // Columna de letras
  } else if(*c == '0'){
    return COL1; // Columna del cero
  } else if(isdigit(*c)){
    return COL2; // Columna de dígitos
  } else if(*c == '#'){
    return COL3; // Columna de numeral
  } else if(isspace(*c) || *c == '\n' || *c == '\t'){
    return COL4; // Columna secuencias escapes (son las dadas por consigna)
  } else if(*c == EOF){
    return COL6; // Columna fin de texto
  }
  return COL5; // Columna otros
}

int esAceptor(int estado){
  return esUnoDe(estado, CANT_ESTADOS_ACEPTORES, ESTADOS_ACEPTORES);
}

int esCentinela(int estado){
  return esUnoDe(estado, CANT_ESTADOS_CENTINELA, ESTADOS_CENTINELA);
}

int esUnoDe(int estado, const int CANTIDAD, const int ESTADOS_QUE_CUMPLEN[]){
  for(int i = 0; i < CANTIDAD; i += 1){
    if(estado == ESTADOS_QUE_CUMPLEN[i]){
      return 1;
    }
  }
  return 0;
}

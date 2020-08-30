#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"

#define CANT_ESTADOS_ACEPTORES 4
#define CANT_ESTADOS_CENTINELA 5
#define CANT_ESTADOS_A_PARAR 5
#define CANT_COLUMNAS 7
#define CANT_FILAS 10

const int ESTADO_INICIAL = E0;

const int ESTADOS_CENTINELA[CANT_ESTADOS_CENTINELA] = {E2, E4, E6 , E8, E9};
const int ESTADOS_ACEPTORES[CANT_ESTADOS_ACEPTORES] = {E2, E4, E8, E9};
const int ESTADOS_A_PARAR[CANT_ESTADOS_A_PARAR] = {E2, E4, E6, E8, E9};

const int TT[CANT_FILAS][CANT_COLUMNAS] = {
/* T.T     L    0    D    #    seq. escape  Otro  fdt*/
/* E0- */ {E1,  E5,  E3,  E7,  E0,          E5,   E9},
/* E1  */ {E1,  E1,  E1,  E2,  E2,          E2,   E2},
/* E2+ */ {E99, E99, E99, E99, E99,         E99,  E99},
/* E3  */ {E4,  E3,  E3,  E4,  E4,          E4,   E4},
/* E4+ */ {E99, E99, E99, E99, E99,         E99,  E99},
/* E5  */ {E6,  E6,  E6,  E6,  E6,          E5,   E6},
/* E6  */ {E99, E99, E99, E99, E99,         E99,  E99},
/* E7  */ {E8,  E8,  E8,  E8,  E8,          E8,   E8},
/* E8+ */ {E99, E99, E99, E99, E99,         E99,  E99},
/* E9+ */ {E99, E99, E99, E99, E99,         E99,  E99}
};

int scanFlujo(FILE* archivo, int lexemasEncontrados[]){
  int estado = ESTADO_INICIAL;
  char *caracterLeido = malloc(sizeof(char));

  while(!pararDeAnalizar(estado)){
    *caracterLeido = getc(archivo);
    int simbolo = categorizarCaracter(caracterLeido);
    estado = TT[estado][simbolo];
  }

  if(esAceptor(estado)){
    if(esCentinela(estado)){
      ungetc(*caracterLeido, archivo);
      free(caracterLeido);
      switch(estado){
      case E2:
        lexemasEncontrados[tokenIdentificador] += 1;
        return tokenIdentificador;
      case E4:
        lexemasEncontrados[tokenConstanteEntera] += 1;
        return tokenConstanteEntera;
      case E8:
        lexemasEncontrados[tokenNumeral] += 1;
        return tokenNumeral;
      case E9:
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

int pararDeAnalizar(int estado){
  return esUnoDe(estado, CANT_ESTADOS_A_PARAR, ESTADOS_A_PARAR);
}

int esUnoDe(int estado, const int CANTIDAD, const int ESTADOS_QUE_CUMPLEN[]){
  for(int i = 0; i < CANTIDAD; i += 1){
    if(estado == ESTADOS_QUE_CUMPLEN[i]){
      return 1;
    }
  }
  return 0;
}

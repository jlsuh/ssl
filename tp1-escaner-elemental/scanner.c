#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"  // << toda biblioteca por implementación que scanner.c llegue a usar, deberá estar declarada de esta manera

#define CANTIDAD_FILAS 10
#define CANTIDAD_COLUMNAS 17
#define CANTIDAD_ESTADOS_A_PARAR 5
#define CANTIDAD_ESTADOS_ACEPTORES 4
#define CANTIDAD_ESTADOS_CENTINELA 5
#define LEN_TOKEN_FORMADO 50

const int ESTADO_INICIAL = E0;

int ESTADOS_A_PARAR[CANTIDAD_ESTADOS_A_PARAR] = {E2, E4, E6, E8, E9};
int ESTADOS_ACEPTORES[CANTIDAD_ESTADOS_ACEPTORES] = {E2, E4, E8, E9};
int ESTADOS_CENTINELA[CANTIDAD_ESTADOS_CENTINELA] = {E2, E4, E6 ,E8, E9};

int TT[CANTIDAD_FILAS][CANTIDAD_COLUMNAS] = {
/* T.T     L    0    D    #    seq. escape  Otro  fdt*/
/* E0  */ {E1,  E5,  E3,  E7,  E0,          E5,   E9},
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

int analizarCadena(FILE* archivo){
  int estado = ESTADO_INICIAL;
  char *caracterLeido = malloc(sizeof(caracterLeido));
  char *tokenFormado = malloc(sizeof(tokenFormado) * LEN_TOKEN_FORMADO);

  while(!pararDeAnalizar(estado)){
    *caracterLeido = getc(archivo);
    int simbolo = columnaAAcceder(caracterLeido);
    estado = TT[estado][simbolo];

    /* Otras acciones como contar líneas, armar lexema, entre otras yerbas */

    tokenFormado = concatenar(tokenFormado, caracterLeido);
  }

  if(esAceptor(estado)){
    if(esCentinela(estado)){
      ungetc(*caracterLeido, archivo);
      switch(estado){
      case E2:
        return tokenIdentificador;
      case E4:
        return tokenConstanteEntera;
      case E8:
        return tokenNumeral;
      case E9:
        return tokenFDT;
      }
    }
  } else {
    ungetc(*caracterLeido, archivo);
    return tokenError;
  }

  free(caracterLeido);
  free(tokenFormado);

  return -1;
}

char* concatenar(const char *s1, const char *s2){
  const size_t len1 = strlen(s1);
  const size_t len2 = strlen(s2);
  char *resultado = malloc(len1 + len2 + 1);
  memcpy(resultado, s1, len1);
  memcpy(resultado + len1, s2, len2 + 1);
  return resultado;
}

int columnaAAcceder(char *c){
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
  return esUnoDe(estado, CANTIDAD_ESTADOS_ACEPTORES, ESTADOS_ACEPTORES);
}

int esCentinela(int estado){
  return esUnoDe(estado, CANTIDAD_ESTADOS_CENTINELA, ESTADOS_CENTINELA);
}

int pararDeAnalizar(int estado){
  return esUnoDe(estado, CANTIDAD_ESTADOS_A_PARAR, ESTADOS_A_PARAR);
}

int esUnoDe(int estado, const int CANTIDAD, int ESTADOS_QUE_CUMPLEN[]){
  for(int i = 0; i < CANTIDAD; i += 1){
    if(estado == ESTADOS_QUE_CUMPLEN[i]){
      return 1;
    }
  }
  return 0;
}

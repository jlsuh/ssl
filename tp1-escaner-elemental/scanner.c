#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"  // toda biblioteca que scanner.h llegue a usar, deberá estar declarada de esta manera

#define CANTIDAD_FILAS 10
#define CANTIDAD_COLUMNAS 17
#define CANTIDAD_ESTADOS_A_PARAR 5
#define CANTIDAD_ESTADOS_ACEPTORES 4
#define CANTIDAD_ESTADOS_CENTINELA 5
#define LEN_TOKEN_FORMADO 50

enum ESTADOS {E0, E1, E2, E3, E4, E5, E6, E7, E8, E9, E99};
enum TOKENS {tokenIdentificador, tokenConstanteEntera, tokenNumeral, tokenFDT, tokenError};
const int ESTADO_INICIAL = E0;
int ESTADOS_A_PARAR[CANTIDAD_ESTADOS_A_PARAR] = {E2, E4, E6, E8, E9};
int ESTADOS_ACEPTORES[CANTIDAD_ESTADOS_ACEPTORES] = {E2, E4, E8, E9};
int ESTADOS_CENTINELA[CANTIDAD_ESTADOS_CENTINELA] = {E2, E4, E6 ,E8, E9};

//int TT[CANTIDAD_FILAS][CANTIDAD_COLUMNAS] = {
///* T.T     L    0    1    2    3    4    5    6    7    8    9    #    esp  \t   s.l.  Otro  fdt*/
///* E0  */ {E1,  E5,  E3,  E3,  E3,  E3,  E3,  E3,  E3,  E3,  E3,  E7,  E0,  E0,  E0,   E5,   E9},
///* E1  */ {E1,  E1,  E1,  E1,  E1,  E1,  E1,  E1,  E1,  E1,  E1,  E2,  E2,  E2,  E2,   E2,   E2},
///* E2+ */ {E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99,  E99,  E99},
///* E3  */ {E4,  E3,  E3,  E3,  E3,  E3,  E3,  E3,  E3,  E3,  E3,  E4,  E4,  E4,  E4,   E4,   E4},
///* E4+ */ {E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99,  E99,  E99},
///* E5  */ {E6,  E6,  E6,  E6,  E6,  E6,  E6,  E6,  E6,  E6,  E6,  E6,  E6,  E6,  E6,   E5,   E6},
///* E6  */ {E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99,  E99,  E99},
///* E7  */ {E8,  E8,  E8,  E8,  E8,  E8,  E8,  E8,  E8,  E8,  E8,  E8,  E8,  E8,  E8,   E8,   E8},
///* E8+ */ {E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99,  E99,  E99},
///* E9+ */ {E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99, E99,  E99,  E99}
//};

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

int analizador(FILE* archivo){
  int estado = ESTADO_INICIAL;
  char *caracterLeido = malloc(sizeof(caracterLeido));
  char *tokenFormado = malloc(sizeof(tokenFormado) * LEN_TOKEN_FORMADO);

  while(!pararDeAnalizar(estado)){
//    if((*caracterLeido = fgetc(archivo)) != EOF){ // >>> REPRESENTAR EOF CON TOKEN <<<
//    }
    *caracterLeido = getc(archivo);

    /* No es parte del pseudocódigo*/
    int simbolo = columnaAAcceder(caracterLeido);
    /* ----------------------------- */

    estado = TT[estado][simbolo];

    /* Otras acciones como contar líneas, armar lexema, entre otras yerbas */

    tokenFormado = concatenar(tokenFormado, caracterLeido);
//    printf("caracter leido: %c\n", *caracterLeido);

  }

  if(esAceptor(estado)){
    if(esCentinela(estado)){
      ungetc(*caracterLeido, archivo);
        switch(estado){
        case 2:
          return tokenIdentificador;
        case 4:
          return tokenConstanteEntera;
        case 8:
          return tokenNumeral;
        case 9:
          return tokenFDT;
        }
    }
  } else {
      ungetc(*caracterLeido, archivo);
      return tokenError;
  }

  free(caracterLeido);
}

char* concatenar(const char *s1, const char *s2){
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char *resultado = malloc(len1 + len2 + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    memcpy(resultado, s1, len1);
    memcpy(resultado + len1, s2, len2 + 1); // +1 to copy the null-terminator
    return resultado;
}

int columnaAAcceder(char *c){
  if(isalpha(*c)){ /* { a-z A-Z }-> L */
    return 0; // Columna L
  } else if(*c == '0'){
    return 1; // Columna 0
  } else if(isdigit(*c)){
    return 2; // Columna D
  } else if(*c == '#'){
    return 3; // Columna #
  } else if(isspace(*c) || *c == '\n' || *c == '\t'){
    return 4; // Columna Secuencia Escape (son las dadas por consigna)
  } else if(*c == EOF){
    return 6; // Columna fdt
  }
  return 5; // Columna Otro
}

int esAceptor(int estado){
  for(int i = 0; i < CANTIDAD_ESTADOS_ACEPTORES; i += 1){
    if(estado == ESTADOS_ACEPTORES[i]){
      return 1;
    }
  }
  return 0;
}

int esCentinela(int estado){
  for(int i = 0; i < CANTIDAD_ESTADOS_CENTINELA; i += 1){
    if(estado == ESTADOS_CENTINELA[i]){
      return 1;
    }
  }
  return 0;
}

int pararDeAnalizar(int estado){
  for(int i = 0; i < CANTIDAD_ESTADOS_A_PARAR; i += 1){
    if(estado == ESTADOS_A_PARAR[i]){
      return 1;
    }
  }
  return 0;
}

//int longitudArray(int *v){
//  int tamanioArray = sizeof(v);
//  int tamanioElemento = sizeof(v[0]);
//  int longitud = tamanioArray / tamanioElemento;
//  return longitud + 1;
//}

void imprimirContenido(FILE *archivo){
  char aux;
  while((aux = fgetc(archivo)) != EOF){
    putchar(aux);
  }
}

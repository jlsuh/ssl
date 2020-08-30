#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

enum TOKENS {tokenIdentificador, tokenConstanteEntera, tokenNumeral, tokenError, tokenFDT};
enum ESTADOS {E0, E1, E2, E3, E4, E5, E6, E7, E8, E9, E99};
enum COLUMNAS {COL0, COL1, COL2, COL3, COL4, COL5, COL6};

int esUnoDe(int estado, const int CANTIDAD, const int ESTADOS_QUE_CUMPLEN[]);
int scanFlujo(FILE* archivo, int lexemasEncontrados[]);
int categorizarCaracter(char *c);
int pararDeAnalizar(int estado);
int esCentinela(int estado);
int esAceptor(int estado);

#endif // SCANNER_H_INCLUDED

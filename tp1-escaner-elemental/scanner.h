#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

enum ESTADOS {E0, E1, E2, E3, E4, E5, E6, E7, E8, E9, E99};
enum TOKENS {tokenIdentificador, tokenConstanteEntera, tokenNumeral, tokenError, tokenFDT};
enum COLUMNAS {COL0, COL1, COL2, COL3, COL4, COL5, COL6};

void imprimirContenido(FILE *archivo);
int analizarCadena(FILE* archivo, int lexemasEncontrados[]);
int pararDeAnalizar(int estado);
int esCentinela(int estado);
int esAceptor(int estado);
int columnaAAcceder(char *c);
char* concatenar(const char *s1, const char *s2);
int esUnoDe(int estado, const int CANTIDAD, int ESTADOS_QUE_CUMPLEN[]);

#endif // SCANNER_H_INCLUDED

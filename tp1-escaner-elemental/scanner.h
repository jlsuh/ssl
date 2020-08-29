#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED



void imprimirContenido(FILE *archivo);
char* analizador(FILE* archivo);
int longitudArray(int v[]);
int pararDeAnalizar(int estado);
int esCentinela(int estado);
int esAceptor(int estado);
int columnaAAcceder(char c);


#endif // SCANNER_H_INCLUDED

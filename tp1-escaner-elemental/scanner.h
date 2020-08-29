#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

void imprimirContenido(FILE *archivo);
int analizador(FILE* archivo);
int pararDeAnalizar(int estado);
int esCentinela(int estado);
int esAceptor(int estado);
int columnaAAcceder(char *c);
char* concatenar(const char *s1, const char *s2);

#endif // SCANNER_H_INCLUDED

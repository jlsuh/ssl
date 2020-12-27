#ifndef SEMANTIC_H_INCLUDED
#define SEMANTIC_H_INCLUDED

extern struct simbolo *tabla_simbolos;

void comenzar();
void terminar();
int asignar(const char *valor_l, const char *valor_r);
int declarar(const char *nombre_simbolo, int bytes_reservados);
int leer(const char *valor_l);
void escribir(const char *nombre_simbolo);
char generar_infijo(const char* operando_izq, const char* operando_der, char operador);
int inversion(const char* nombre_simbolo);

#endif // SEMANTIC_H_INCLUDED

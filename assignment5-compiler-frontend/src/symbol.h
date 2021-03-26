#ifndef SYMBOL_H_INCLUDED
#define SYMBOL_H_INCLUDED

#include "parser.h"
#include "semantic.h"

struct simbolo {
    char nombre[32];
    struct simbolo* sig;
};

struct simbolo *crear_nuevo_simbolo(char *nuevoNombre);
void insertar_al_principio(struct simbolo **head, struct simbolo *simboloAInsertar);
int contiene_simbolo(struct simbolo *head, const char* nombreABuscar);

#endif // SYMBOL_H_INCLUDED

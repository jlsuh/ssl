#include "symbol.h"

struct simbolo *crear_nuevo_simbolo(char *nuevoNombre) {
    struct simbolo *nuevoSimbolo = malloc(sizeof(*nuevoSimbolo));
    strcpy(nuevoSimbolo->nombre, nuevoNombre);
    nuevoSimbolo->sig = NULL;
    return nuevoSimbolo;
}

void insertar_al_principio(struct simbolo **head, struct simbolo *simboloAInsertar) {
    simboloAInsertar->sig = *head;
    *head = simboloAInsertar;
    return;
}

int contiene_simbolo(struct simbolo *head, const char* nombreABuscar) {
    struct simbolo *auxHead = head;
    while(auxHead != NULL) {
        if(strcmp(auxHead->nombre, nombreABuscar) == 0) {
            return 1;
        }
        auxHead = auxHead->sig;
    }
    return 0;
}

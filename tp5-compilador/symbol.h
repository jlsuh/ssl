#ifndef SYMBOL_H_INCLUDED
#define SYMBOL_H_INCLUDED

struct simbolo {
    char nombre[32];
    char tipo[7]; // Solamente del tipo: Integer
    struct simbolo* sig;
};

struct simbolo *crear_nuevo_simbolo(const char* nombre_simbolo);
struct simbolo *insertar_al_principio(struct simbolo **head, struct simbolo *simbolo_a_insertar);
void imprimir_lista(struct simbolo *head);
int contiene_simbolo(struct simbolo *head, const char* nombre_a_buscar);

#endif // SYMBOL_H_INCLUDED

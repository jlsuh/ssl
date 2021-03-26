#include "semantic.h"

int contadorTemporales = 0;

void comenzar() {
    generar_pseudo("Load", "rtlib", "", "");
    return;
}

void terminar() {
    generar_pseudo("Exit", "", "", "");
    return;
}

void escribir(char *nombreSimbolo) {
    generar_pseudo("Write", nombreSimbolo, "Integer", "");
    free(nombreSimbolo);
    return;
}

void asignar(char *valorL, char *valorR) {
    generar_pseudo("Store", valorR, valorL, "");
    free(valorL);
    free(valorR);
    return;
}

void leer(char *valorL) {
    generar_pseudo("Read", valorL, "Integer", "");
    free(valorL);
    return;
}

int declarar(char *nombreSimbolo) {
    if(!contiene_simbolo(tablaSimbolos, nombreSimbolo)) { // Se declara normalmente
        struct simbolo *nuevoSimbolo = crear_nuevo_simbolo(nombreSimbolo);
        insertar_al_principio(&tablaSimbolos, nuevoSimbolo);
        generar_pseudo("Reserve", nombreSimbolo, "4", "");
        return 0;
    }
    notificar_error_semantico(nombreSimbolo, "ya");
    return 1;
}

int procesar_id(char *nombreSimbolo) {
    if(!contiene_simbolo(tablaSimbolos, nombreSimbolo)) {
        notificar_error_semantico(nombreSimbolo, "NO");
        return 1;
    }
    return 0;
}

void notificar_error_semantico(char* nombreSimbolo, char* status) {
    yysemerrs++;
    sprintf(buffer, "Error semántico: identificador %s %s declarado", nombreSimbolo, status);
    yyerror(buffer);
    return;
}

void generar_pseudo(char *codigoPseudo, char *primerParametro, char *segundoParametro, char *tercerParametro) {
    printf("%s %s,%s,%s\n", codigoPseudo, primerParametro, segundoParametro, tercerParametro);
    return;
}

char *generar_infijo(char *operandoIzq, int operador, char *operandoDer) {
    char *temporal = declarar_nuevo_temporal();
    switch(operador) {
        case '+':
            generar_pseudo("ADD", operandoIzq, operandoDer, buffer);
        break;
        case '-':
            generar_pseudo("SUB", operandoIzq, operandoDer, buffer);
        break;
        case '*':
            generar_pseudo("MUL", operandoIzq, operandoDer, buffer);
        break;
        case '/':
            generar_pseudo("DIV", operandoIzq, operandoDer, buffer);
        break;
    }
    return temporal;
}

char *generar_unario(char *operando) {
    char *temporal = declarar_nuevo_temporal();
    generar_pseudo("NEG", operando, "", buffer);
    return temporal;
}

char *declarar_nuevo_temporal() {
    sprintf(buffer, "Temp#%d", ++contadorTemporales);
    char *temporal = strdup(buffer);
    declarar(temporal);
    return temporal;
}

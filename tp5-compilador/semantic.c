#include <stdio.h>
#include "semantic.h"
#include "parser.h"
#include "symbol.h"

/* Requisitos:
• Al declarar una variable reservaremos 4 bytes de memoria con Reserve y dos parámetros, el nombre de la variable y la cantidad de bytes a reservar.
• Load, para la carga de la biblioteca en tiempo de ejecución, debe quedar: Load rtlib,,
TODO • ADD, para la suma
TODO • SUB, para la resta
TODO • MUL, para la multiplicación
TODO • DIV, para la división
TODO • NEG, para el menos unario. OJO hay que usar precedencia de contexto. Generaremos algo como: NEG Var,,VarNeg es decir, el segundo operando lo dejamos en blanco y guardamos (consistentemente con el resto de las operaciones) en el tercer operando
• Store, para la asignación
• Read, para la lectura de un identificador
• Write, para la escritura de una expresión
• Exit, para frenar el programa

Las variables deben declararse antes de usarse y no es correcto duplicar una declaración. Por este motivo pueden ocurrir dos tipos de errores semánticos:
TODO • definir más de una vez una variable (redeclarar)
TODO • utilizar en las sentencias una variable no declarada.
*/

int contador_temporales = 0;

void comenzar() {
    printf("Load rtlib,,\n");
    return;
}

void terminar() {
    printf("Exit ,\n");
    return;
}

int asignar(const char *valor_l, const char *valor_r) {
    if(contiene_simbolo(tabla_simbolos, valor_l)) {
        printf("Store %s,%s\n", valor_r, valor_l); // Store $1,$3
        return 0;
    } else {
        yysemerrs++;
        sprintf(msg, "Error semántico: identificador %s NO declarado", valor_l);
        yyerror(msg);
        return -1;
    }
}

int declarar(const char *nombre_simbolo, int bytes_reservados) {
    if(!contiene_simbolo(tabla_simbolos, nombre_simbolo)) {
        struct simbolo *nuevo_simbolo = crear_nuevo_simbolo(nombre_simbolo);
        insertar_al_principio(&tabla_simbolos, nuevo_simbolo);
        printf("Reserve %s,4\n", nombre_simbolo); // Reserve $2,4
        return 0;
    } else {
        yysemerrs++;
        sprintf(msg, "Error semántico: identificador %s ya declarado", nombre_simbolo);
        yyerror(msg);
        return -1;
    }
}

int leer(const char *valor_l) {
    if(contiene_simbolo(tabla_simbolos, valor_l)) {
        printf("Read %s,Integer\n", valor_l); // Read $1,Integer
        // TODO: tipo de dato irrelevante?
        return 0;
    } else {
        yysemerrs++;
        sprintf(msg, "Error semántico: identificador %s NO declarado", valor_l);
        yyerror(msg);
        return -1;
    }
}

void escribir(const char *nombre_simbolo) {
    printf("Write %s,Integer\n", nombre_simbolo);
    // TODO: tipo de dato irrelevante?
    return;
}

char generar_infijo(const char* operando_izq, const char* operando_der, char operador) {
    int aux_izq, aux_der;
    sscanf(operando_izq, "%d", &aux_izq);
    sscanf(operando_der, "%d", &aux_der);
    sprintf(msg, "Temp#%d", ++contador_temporales);
    declarar(msg, 4);
    switch(operador) {
    case '+':
        printf("ADD %s,%s,%s\n", operando_izq, operando_der, msg);
        return aux_izq + aux_der + '0';
    case '-':
        printf("SUB %s,%s,%s\n", operando_izq, operando_der, msg);
        return aux_izq - aux_der + '0';
    case '*':
        printf("MUL %s,%s,%s\n", operando_izq, operando_der, msg);
        return aux_izq * aux_der + '0';
    case '/':
        printf("DIV %s,%s,%s\n", operando_izq, operando_der, msg);
        return aux_izq / aux_der + '0';
    }
}

int inversion(const char* nombre_simbolo) {
    sprintf(msg, "Temp#%d", ++contador_temporales);
    int res = declarar(msg, 4);
    printf("NEG %s,,%s\n", nombre_simbolo, msg);
    return res;
}

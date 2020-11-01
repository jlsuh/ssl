/* Grupo 01:
 * Integrantes:
 * - Matias Ferraro
 * - Nahuel Farias
 * - Joel Suh
 */

#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

int main()
{

    TOKEN token;

    do {
        token = yylex();
        switch (token) {
            case tokenLeer:
                puts("Token: Leer");
            break;
            case tokenDeclarar:
                puts("Token: Declarar");
            break;
            case tokenEscribir:
                puts("Token: Escribir");
            break;
            case tokenPrograma:
                puts("Token: Programa");
            break;
            case tokenFinProg:
                puts("Token: Fin-Prog");
            break;
            case tokenIdentificador:
                puts("Token: Identificador\tlexema: ");
                puts(yytext);
            break;
            case tokenConstanteEntera:
                puts("Token: Constante\tlexema: ");
                puts(yytext);
            break;
            case tokenAsig:
                puts("Token: Asignación");
            break;
            case '+':
                puts("Token: \'+\'");
            break;
            case '-':
                puts("Token: \'-\'");
            break;
            case '*':
                puts("Token: \'*\'");
            break;
            case '/':
                puts("Token: \'/\'");
            break;
            case '(':
                puts("Token: \'(\'");
            break;
            case ')':
                puts("Token: \')\'");
            break;
            case ',':
                puts("Token: \',\'");
            break;
            case ';':
                puts("Token: \';\'");
            break;
            case tokenErrorComun:
                puts("Error léxico: cadena desconocida: ");
                puts(yytext);
            break;
            case tokenErrorIdentificador:
                puts("Error léxico: identificador inválido: ");
                puts(yytext);
            break;
            case tokenErrorConstante:
                puts("Error léxico: constante inválida: ");
                puts(yytext);
            break;
        }
    } while (token != FDT);
    
    if(token == FDT)
        puts("Token: Fin de Archivo");
    
    return EXIT_SUCCESS;

}

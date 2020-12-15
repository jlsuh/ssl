%code top{
#include <stdio.h>
#include "scanner.h"
#include "symbol.h"
#include "semantic.h"

struct simbolo *tabla_simbolos = NULL;
}
%code provides{
void yyerror(const char *);
extern int yylexerrs;
extern int yysemerrs;
extern char msg[120];
}
%defines "parser.h"
%output "parser.c"
%define api.value.type {char *}
%define parse.error verbose
%start programa-mini

%token IDENTIFICADOR LEER DECLARAR ESCRIBIR PROGRAMA FINPROG CONSTANTE
%token ASIGNACION "<-"
%left '+' '-'
%left '*' '/'
%precedence NEG
%%
programa-mini            : {comenzar();} PROGRAMA lista-sentencias FINPROG { if (yynerrs || yylexerrs) YYABORT; terminar();}
                         ;
lista-sentencias         : %empty
                         | sentencia lista-sentencias
                         | sentencia
                         ;
sentencia                : IDENTIFICADOR "<-" expresion-aditiva ';' { if( asignar($1, $3) ) YYERROR; }
                         | DECLARAR IDENTIFICADOR ';' { if( declarar($2, 4) ) YYERROR; }
                         | LEER '(' lista-identificadores ')' ';' // verificación de semántica en no-terminal: lista-identificadores
                         | ESCRIBIR '(' expresion-aditiva ')' ';' { escribir($3); }
                         | error ';'
                         ;
lista-identificadores    : IDENTIFICADOR { if( leer($1) ) YYERROR; } ',' lista-identificadores
                         | IDENTIFICADOR { if( leer($1) ) YYERROR; }
                         ;
expresion-aditiva        : expresion-multiplicativa
                         | expresion-aditiva '+' expresion-multiplicativa
                           {
                            char resultado = generar_infijo($1, $3, '+');
                            $$ = &resultado;
                           }
                         | expresion-aditiva '-' expresion-multiplicativa
                           {
                            char resultado = generar_infijo($1, $3, '-');
                            $$ = &resultado;
                           }
                         ;
expresion-multiplicativa : expresion-primaria
                         | expresion-multiplicativa '*' expresion-primaria
                           {
                            char resultado = generar_infijo($1, $3, '*');
                            $$ = &resultado;
                           }
                         | expresion-multiplicativa '/' expresion-primaria
                           {
                            char resultado = generar_infijo($1, $3, '/');
                            $$ = &resultado;
                           }
                         ;
expresion-primaria       : CONSTANTE
                         | IDENTIFICADOR
                         | '(' expresion-aditiva ')'
                         | '-' expresion-aditiva %prec NEG { if ( inversion($2) ) YYERROR; }
                         ;
%%
/* Informar ocurrencia de un error */
void yyerror(const char *s){ // si no hubiese estado definido, directamente el yyerror imprimiría: "syntax error" solamente
    printf("Línea #%d: %s\n", yylineno, s);
    return;
}

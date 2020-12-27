%code top{
#include <stdio.h>
#include "scanner.h"
#include "symbol.h"
#include "semantic.h"

struct simbolo *tabla_simbolos = NULL;
char resultado;
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
                         ;
sentencia                : IDENTIFICADOR "<-" expresion ';' { if( asignar($1, $3) ) YYERROR; }
                         | DECLARAR IDENTIFICADOR ';' { if( declarar($2, 4) ) YYERROR; }
                         | LEER '(' lista-identificadores ')' ';' // verificación de semántica en no-terminal: lista-identificadores
                         | ESCRIBIR '(' lista-expresion ')' ';' { escribir($3); }
                         | error ';'
                         ;
lista-expresion          : expresion ',' lista-expresion
                         | expresion
                         ;
lista-identificadores    : IDENTIFICADOR { if( leer($1) ) YYERROR; } ',' lista-identificadores
                         | IDENTIFICADOR { if( leer($1) ) YYERROR; }
                         ;
expresion                : expresion-primaria
                         | expresion '+' expresion
                           {
                            resultado = generar_infijo($1, $3, '+');
                            $$ = &resultado;
                           }
                         | expresion '-' expresion
                           {
                            resultado = generar_infijo($1, $3, '-');
                            $$ = &resultado;
                           }
                         | expresion '*' expresion
                           {
                            resultado = generar_infijo($1, $3, '*');
                            $$ = &resultado;
                           }
                         | expresion '/' expresion
                           {
                            resultado = generar_infijo($1, $3, '/');
                            $$ = &resultado;
                           }
                         ;
expresion-primaria       : CONSTANTE
                         | IDENTIFICADOR
                         | '(' expresion ')'
                         | '-' expresion %prec NEG { if ( inversion($2) ) YYERROR; }
                         ;
%%
/* Informar ocurrencia de un error */
void yyerror(const char *s){ // si no hubiese estado definido, directamente el yyerror imprimiría: "syntax error" solamente
    printf("Línea #%d: %s\n", yylineno, s);
    return;
}

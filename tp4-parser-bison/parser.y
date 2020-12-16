%code top{
#include <stdio.h>
#include "scanner.h"
}
%code provides{
void yyerror(const char *);
extern int yylexerrs;
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
programa-mini            : PROGRAMA lista-sentencias FINPROG { if (yynerrs || yylexerrs) YYABORT;}
                         ;
lista-sentencias         : %empty
                         | sentencia lista-sentencias
                         ;
sentencia                : IDENTIFICADOR "<-" expresion ';' {printf("asignación\n");}
                         | DECLARAR IDENTIFICADOR ';' {printf("declarar %s\n", yylval);}
                         | LEER '(' lista-identificadores ')' ';' {printf("leer\n");}
                         | ESCRIBIR '(' expresion ')' ';' {printf("escribir\n");}
                         | error ';'
                         ;
lista-identificadores    : IDENTIFICADOR ',' lista-identificadores
                         | IDENTIFICADOR
                         ;
// gramática achatada //
expresion                : expresion-primaria
                         | expresion '+' expresion {printf("suma\n");}
                         | expresion '-' expresion {printf("resta\n");}
                         | expresion '*' expresion {printf("multiplicación\n");}
                         | expresion '/' expresion {printf("división\n");}
                         ;
expresion-primaria       : CONSTANTE
                         | IDENTIFICADOR
                         | '(' expresion ')' {printf("paréntesis\n");}
                         | '-' expresion %prec NEG {printf("inversión\n");}
                         ;
%%
/* Informar ocurrencia de un error */
void yyerror(const char *s){ // si no hubiese estado definido, directamente el yyerror imprimiría: "syntax error" solamente
    printf("Línea #%d: %s\n", yylineno, s);
    return;
}

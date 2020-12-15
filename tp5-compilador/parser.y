%code top{
#include <stdio.h>
#include "scanner.h"
#include "symbol.h"
#include "semantic.h"
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
                         | sentencia
                         ;
sentencia                : IDENTIFICADOR "<-" expresion-aditiva ';' {printf("asignación\n");}
                         | DECLARAR IDENTIFICADOR ';' {printf("declarar %s\n", yylval);}
                         | LEER '(' lista-identificadores ')' ';' {printf("leer\n");}
                         | ESCRIBIR '(' expresion-aditiva ')' ';' {printf("escribir\n");}
                         | error ';'
                         ;
lista-identificadores    : IDENTIFICADOR ',' lista-identificadores
                         | IDENTIFICADOR
                         ;
expresion-aditiva        : expresion-multiplicativa
                         | expresion-aditiva '+' expresion-multiplicativa {printf("suma\n");}
                         | expresion-aditiva '-' expresion-multiplicativa {printf("resta\n");}
                         ;
expresion-multiplicativa : expresion-primaria
                         | expresion-multiplicativa '*' expresion-primaria {printf("multiplicación\n");}
                         | expresion-multiplicativa '/' expresion-primaria {printf("división\n");}
                         ;
expresion-primaria       : CONSTANTE
                         | IDENTIFICADOR
                         | '(' expresion-aditiva ')' {printf("paréntesis\n");}
                         | '-' expresion-aditiva %prec NEG {printf("inversión\n");}
                         ;
%%
/* Informar ocurrencia de un error */
void yyerror(const char *s){ // si no hubiese estado definido, directamente el yyerror imprimiría: "syntax error" solamente
    printf("Línea #%d: %s\n", yylineno, s);
    return;
}

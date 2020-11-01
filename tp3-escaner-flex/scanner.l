%top{
#include "tokens.h"
}
%option outfile="scanner.c"
%option header-file="scanner.h"
%option noinput
%option nounput

Digito              [[:digit:]]
Letra               [[:alpha:]]
Espacio             [[:space:]]
Otros               [[:^alnum:]]{-}[[:space:]]{-}[\+\-\*"/"]{-}[\(\);,]

%%
declarar                              return tokenDeclarar;
leer                                  return tokenLeer;
escribir                              return tokenEscribir;
programa                              return tokenPrograma;
fin-prog                              return tokenFinProg;
{Letra}({Letra}|{Digito})*            return tokenIdentificador;
(0|[1-9]{Digito}*)                    return tokenConstanteEntera;
"+"                                   return '+';
"-"                                   return '-';
"*"                                   return '*';
"/"                                   return '/';
"<-"                                  return tokenAsig;
"("                                   return '(';
")"                                   return ')';
","                                   return ',';
";"                                   return ';';
{Otros}+                              return tokenErrorComun;
{Letra}({Letra}|{Digito}|{Otros})*    return tokenErrorIdentificador;
(0|[1-9]{Digito}*)({Letra}|{Digito})* return tokenErrorConstante;
{Espacio}+                            ;
##.*                                  ;


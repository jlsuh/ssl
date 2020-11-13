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
Otros               [[:^alnum:]]{-}[[:space:]]{-}[-+*/();,]
Identificador       {Letra}({Letra}|{Digito})*
ConstanteEntera     (0|[1-9]{Digito}*)

%%
declarar                                                        return tokenDeclarar;
leer                                                            return tokenLeer;
escribir                                                        return tokenEscribir;
programa                                                        return tokenPrograma;
fin-prog                                                        return tokenFinProg;
{Identificador}                                                 return tokenIdentificador;
{ConstanteEntera}                                               return tokenConstanteEntera;
"+"                                                             return '+';
"-"                                                             return '-';
"*"                                                             return '*';
"/"                                                             return '/';
"<-"                                                            return tokenAsig;
"("                                                             return '(';
")"                                                             return ')';
","                                                             return ',';
";"                                                             return ';';
{Otros}+                                                        return tokenErrorComun;
{Identificador}{Otros}({Letra}|{Digito}|{Otros})*               return tokenErrorIdentificador;
{ConstanteEntera}({Letra}|{Digito})*                            return tokenErrorConstante;
{Espacio}+                                                      ;
##.*                                                            ;

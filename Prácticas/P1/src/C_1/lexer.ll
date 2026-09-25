/* lexer.ll
   Analizador léxico para el lenguaje C_1.
   Al compilarlo con flex++ se genera Lexer.cpp.
   Santiago Zapata Amezcua */

%{
#include <iostream>
#include "Lexer.hpp"
#include "tokens.hpp"
%}

%option c++
%option outfile="Lexer.cpp"
%option yyclass="Lexer"
%option noyywrap
%option yylineno

digito     [0-9]
letra      [a-zA-Z]
espacio    [ \t\n\r]
id         ({letra}|_)({letra}|{digito}|_)*
entero     {digito}+
decimal    ({digito}*"."{digito}+|{digito}+"."{digito}*)
exponente  [eE][+-]?{digito}+
numero     {entero}|{decimal}{exponente}?|{entero}{exponente}

%%

{espacio}+  { /* los espacios se ignoran */ }

 /* palabras reservadas (van antes de id para que ganen el empate) */
"int"       { return INT; }
"float"     { return FLOAT; }
"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }

{id}        { return ID; }
{numero}    { return NUMERO; }

 /* símbolos */
";"         { return PYC; }
","         { return COMA; }
"("         { return LPAR; }
")"         { return RPAR; }

 /* cualquier otro carácter es un error léxico */
.           { std::cout << "Error léxico en la línea " << yylineno << ": " << yytext << std::endl; }

%%

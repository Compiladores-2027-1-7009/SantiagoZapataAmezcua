%{
#include <iostream>
#include <string>
using namespace std;

#include "headers/Symbols.hpp"
#include "headers/Lexer.hpp"

int line=1;
%}

%option c++
%option outfile="Lexer.cpp"
%option yyclass="Lexer"

DIGITO  [0-9]
LETRA   [a-zA-Z_]
ID      {LETRA}({LETRA}|{DIGITO})*
NUM     {DIGITO}+("."{DIGITO}+)?

%%

[ \t\r]+ {}
"\n" 	 {line++;}

  /* Palabras reservadas, van antes que ID para que no se tomen como identificadores */
"int"    { return t_int; }
"float"  { return t_float; }
"if"     { return t_if; }
"else"   { return t_else; }
"while"  { return t_while; }

  /* Identificadores (pueden empezar con _) y números enteros o con punto decimal */
{ID}     { return t_id; }
{NUM}    { return t_num; }

  /* Símbolos */
";"      { return t_pyc; }
","      { return t_coma; }
"="      { return t_asig; }
"("      { return t_lpar; }
")"      { return t_rpar; }
"+"      { return t_mas; }
"-"      { return t_menos; }
"*"      { return t_mul; }
"/"      { return t_div; }

  /* Fin de archivo */
<<EOF>>  { return t_eof; }

.    	 { cout << "ERROR LEXICO " << yytext << endl;}

%%

int yyFlexLexer::yywrap(){
    return 1;
}

int Lexer::getLine()
{
    return line;
}

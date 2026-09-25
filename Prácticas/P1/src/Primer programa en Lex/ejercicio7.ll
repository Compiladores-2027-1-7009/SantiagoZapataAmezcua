/* Ejercicio 7: reconoce hexadecimales, palabras reservadas,
   identificadores de C++ (máximo 32 caracteres) y espacios en blanco.
   Santiago Zapata Amezcua */
%{
  #include <iostream>
%}

%option c++
%option noyywrap

digito      [0-9]
hexdigito   [0-9a-fA-F]
letra       [a-zA-Z]
sufijo      ([uU](l|L|ll|LL)?|(l|L|ll|LL)[uU]?)
hexadecimal 0[xX]{hexdigito}+{sufijo}?
reservada   if|else|while|return|class
id          ({letra}|_)({letra}|{digito}|_){0,31}
idlargo     ({letra}|_)({letra}|{digito}|_){32,}
espacio     [ \t\n]+

%%

{hexadecimal} { std::cout << "Encontré un hexadecimal: " << yytext << std::endl; }
{reservada}   { std::cout << "Encontré una palabra reservada: " << yytext << std::endl; }
{id}          { std::cout << "Encontré un identificador: " << yytext << std::endl; }
{idlargo}     { std::cout << "Identificador demasiado largo (más de 32): " << yytext << std::endl; }
{espacio}     { std::cout << "Encontré espacio en blanco" << std::endl; }

%%

int main() {
  FlexLexer* lexer = new yyFlexLexer;
  lexer->yylex();
  return 0;
}

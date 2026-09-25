// Lexer.hpp
// Clase Lexer: hereda de yyFlexLexer y sobreescribe yylex(),
// que es la función que genera flex a partir de lexer.ll.
// Santiago Zapata Amezcua

#ifndef LEXER_HPP
#define LEXER_HPP

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include <iostream>
#include "tokens.hpp"

class Lexer : public yyFlexLexer {
public:
    // Recibe el flujo de entrada (el archivo que vamos a analizar)
    Lexer(std::istream *in) : yyFlexLexer(in) {}

    using FlexLexer::yylex;
    // Regresa el siguiente token, o 0 cuando se acaba el archivo
    virtual int yylex();
};

#endif

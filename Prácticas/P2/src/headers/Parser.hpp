#ifndef PARSER_H
#define PARSER_H
#include <string>
#include "Lexer.hpp"
#include "Symbols.hpp"
using namespace std;

namespace C_1
{
  class Parser
  {

  private:
    Lexer *lexer;
    int token;
    
  public:
    Parser();
    Parser(Lexer *lexer);
    ~Parser();
    
    void programa(); //función del símbolo incial
    /**
     *
     *
     * Funciones del resto de NTs 
     *
     *
     */
    void declaraciones();
    void declaracionesP();
    void declaracion();
    void tipo();
    void lista_var();
    void lista_varP();
    void sentencias();
    void sentenciasP();
    void sentencia();
    void expresion();
    void expresionP();
    void termino();
    void terminoP();
    void factor();
    
    Token eat();
    void error(string msg);
    void parse();
  };    
    
}


#endif

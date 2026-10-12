#include "headers/Parser.hpp"
#include <iostream>
#include <cstdlib>

namespace C_1
{
  Parser::Parser(/* args */)
  {
  }

  Parser::Parser(Lexer *lexer)
  {
    this->lexer = lexer;
  }
    
  Parser::~Parser()
  {
  }

  // programa -> declaraciones sentencias
  // Símbolo inicial: primero vienen todas las declaraciones y luego las sentencias.
  void Parser::programa(){
    declaraciones();
    sentencias();
  }

  /************************************************************************/
  /**                                                                    **/
  /**                       Funciones por cada NT                        **/
  /**                                                                    **/
  /************************************************************************/

  // declaraciones -> declaracion declaracionesP
  // Tiene que haber al menos una declaración.
  void Parser::declaraciones(){
    declaracion();
    declaracionesP();
  }

  // declaracionesP -> declaracion declaracionesP | ε
  // Si el token es int o float sigue otra declaración, si no se toma ε.
  void Parser::declaracionesP(){
    if(token == t_int || token == t_float){
      declaracion();
      declaracionesP();
    }
  }

  // declaracion -> tipo lista_var ;
  void Parser::declaracion(){
    tipo();
    lista_var();
    if(token == t_pyc)
      token = eat();
    else
      error("se esperaba ';'");
  }

  // tipo -> int | float
  void Parser::tipo(){
    if(token == t_int || token == t_float)
      token = eat();
    else
      error("se esperaba int o float");
  }

  // lista_var -> identificador lista_varP
  void Parser::lista_var(){
    if(token == t_id){
      token = eat();
      lista_varP();
    }
    else
      error("se esperaba un identificador");
  }

  // lista_varP -> , identificador lista_varP | ε
  // Mientras haya comas se siguen leyendo identificadores.
  void Parser::lista_varP(){
    if(token == t_coma){
      token = eat();
      if(token == t_id){
        token = eat();
        lista_varP();
      }
      else
        error("se esperaba un identificador después de ','");
    }
  }

  // sentencias -> sentencia sentenciasP
  // Tiene que haber al menos una sentencia.
  void Parser::sentencias(){
    sentencia();
    sentenciasP();
  }

  // sentenciasP -> sentencia sentenciasP | ε
  // Si el token puede iniciar una sentencia (identificador, if o while) se
  // sigue leyendo. Así el cuerpo de un while o de un else se queda con todas
  // las sentencias que siguen, hasta un else o el fin del archivo.
  void Parser::sentenciasP(){
    if(token == t_id || token == t_if || token == t_while){
      sentencia();
      sentenciasP();
    }
  }

  // sentencia -> identificador = expresion ;
  //            | if ( expresion ) sentencias else sentencias
  //            | while ( expresion ) sentencias
  // Con el primer token se sabe cuál de las tres reglas usar.
  void Parser::sentencia(){
    if(token == t_id){
      token = eat();
      if(token == t_asig)
        token = eat();
      else
        error("se esperaba '='");
      expresion();
      if(token == t_pyc)
        token = eat();
      else
        error("se esperaba ';'");
    }
    else if(token == t_if){
      token = eat();
      if(token == t_lpar)
        token = eat();
      else
        error("se esperaba '('");
      expresion();
      if(token == t_rpar)
        token = eat();
      else
        error("se esperaba ')'");
      sentencias();
      if(token == t_else)
        token = eat();
      else
        error("se esperaba else");
      sentencias();
    }
    else if(token == t_while){
      token = eat();
      if(token == t_lpar)
        token = eat();
      else
        error("se esperaba '('");
      expresion();
      if(token == t_rpar)
        token = eat();
      else
        error("se esperaba ')'");
      sentencias();
    }
    else
      error("se esperaba una sentencia");
  }

  // expresion -> termino expresionP
  void Parser::expresion(){
    termino();
    expresionP();
  }

  // expresionP -> + termino expresionP | - termino expresionP | ε
  // Suma y resta, que tienen menor precedencia.
  void Parser::expresionP(){
    if(token == t_mas || token == t_menos){
      token = eat();
      termino();
      expresionP();
    }
  }

  // termino -> factor terminoP
  void Parser::termino(){
    factor();
    terminoP();
  }

  // terminoP -> * factor terminoP | / factor terminoP | ε
  // Multiplicación y división, que van antes que la suma y la resta.
  void Parser::terminoP(){
    if(token == t_mul || token == t_div){
      token = eat();
      factor();
      terminoP();
    }
  }

  // factor -> ( expresion ) | identificador | numero
  void Parser::factor(){
    if(token == t_lpar){
      token = eat();
      expresion();
      if(token == t_rpar)
        token = eat();
      else
        error("se esperaba ')'");
    }
    else if(token == t_id || token == t_num)
      token = eat();
    else
      error("se esperaba un identificador, un número o '('");
  }


  Token Parser::eat(){
    return (Token) lexer->yylex();
  }

  void Parser::error(string msg){
    cout << "ERROR DE SINTAXIS " << msg << " en la línea "<< lexer->getLine() <<endl;
    exit(EXIT_FAILURE); // se detiene en el primer error
  }   

  void Parser::parse(){
    token = eat();
    programa();
    if(token == t_eof)
      cout << "La cadena es aceptada" << endl;
    else 
      cout << "La cadena no pertenece al lenguaje generado por la gramática" << endl;
  }

}

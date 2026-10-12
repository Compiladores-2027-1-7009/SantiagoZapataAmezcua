#ifndef __SYMBOLS_HPP__
#define __SYMBOLS_HPP__

/** 
 * 1. Definir en un comentario la gramática G(N, T, P, S)
 *
 * Es la gramática ya sin ambigüedad y sin recursión izquierda,
 * que es la que sigue el parser. (P = prima, ej. declaracionesP = declaraciones')
 *
 * N = { programa, declaraciones, declaracionesP, declaracion, tipo,
 *       lista_var, lista_varP, sentencias, sentenciasP, sentencia,
 *       expresion, expresionP, termino, terminoP, factor }
 *
 * T = { int, float, identificador, numero, ;, ,, =, if, else, while,
 *       (, ), +, -, *, / }
 *
 * S = programa
 *
 * P = {
 *   programa       -> declaraciones sentencias
 *   declaraciones  -> declaracion declaracionesP
 *   declaracionesP -> declaracion declaracionesP | ε
 *   declaracion    -> tipo lista_var ;
 *   tipo           -> int | float
 *   lista_var      -> identificador lista_varP
 *   lista_varP     -> , identificador lista_varP | ε
 *   sentencias     -> sentencia sentenciasP
 *   sentenciasP    -> sentencia sentenciasP | ε
 *   sentencia      -> identificador = expresion ;
 *                   | if ( expresion ) sentencias else sentencias
 *                   | while ( expresion ) sentencias
 *   expresion      -> termino expresionP
 *   expresionP     -> + termino expresionP | - termino expresionP | ε
 *   termino        -> factor terminoP
 *   terminoP       -> * factor terminoP | / factor terminoP | ε
 *   factor         -> ( expresion ) | identificador | numero
 * }
 */


/**
 * 2. Determinar la enumeración para el conjunto T
 */
enum Token { primero, t_eof,
  t_int,    // int
  t_float,  // float
  t_if,     // if
  t_else,   // else
  t_while,  // while
  t_id,     // identificador
  t_num,    // numero
  t_pyc,    // ;
  t_coma,   // ,
  t_asig,   // =
  t_lpar,   // (
  t_rpar,   // )
  t_mas,    // +
  t_menos,  // -
  t_mul,    // *
  t_div     // /
};

/**
 * 3. Determinar la enumeración para el conjunto N
 */
enum NoTerm { strEmpty,
  n_programa, n_declaraciones, n_declaracionesP, n_declaracion, n_tipo,
  n_lista_var, n_lista_varP, n_sentencias, n_sentenciasP, n_sentencia,
  n_expresion, n_expresionP, n_termino, n_terminoP, n_factor
};

#endif // !__SYMBOLS_HPP__

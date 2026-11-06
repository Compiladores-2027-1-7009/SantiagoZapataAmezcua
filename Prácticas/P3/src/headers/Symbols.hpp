#ifndef __SYMBOLS_HPP__
#define __SYMBOLS_HPP__

/**
 * 1. Definir en un comentario la gramática G'(N', T, P', S)
 *
 * Es la misma gramática de la práctica anterior, ya sin ambigüedad y sin
 * recursión izquierda. (P = prima, ej. declaracionesP = declaraciones')
 * El número de cada producción es el que se usa en ParserLL.cpp.
 *
 * N' = { programa, declaraciones, declaracionesP, declaracion, tipo,
 *        lista_var, lista_varP, sentencias, sentenciasP, sentencia,
 *        expresion, expresionP, termino, terminoP, factor }
 *
 * T = { int, float, identificador, numero, ;, ,, =, if, else, while,
 *       (, ), +, -, *, / }
 *
 * S = programa
 *
 * P' = {
 *   1.  programa       -> declaraciones sentencias
 *   2.  declaraciones  -> declaracion declaracionesP
 *   3.  declaracionesP -> declaracion declaracionesP
 *   4.  declaracionesP -> ε
 *   5.  declaracion    -> tipo lista_var ;
 *   6.  tipo           -> int
 *   7.  tipo           -> float
 *   8.  lista_var      -> identificador lista_varP
 *   9.  lista_varP     -> , identificador lista_varP
 *   10. lista_varP     -> ε
 *   11. sentencias     -> sentencia sentenciasP
 *   12. sentenciasP    -> sentencia sentenciasP
 *   13. sentenciasP    -> ε
 *   14. sentencia      -> identificador = expresion ;
 *   15. sentencia      -> if ( expresion ) sentencias else sentencias
 *   16. sentencia      -> while ( expresion ) sentencias
 *   17. expresion      -> termino expresionP
 *   18. expresionP     -> + termino expresionP
 *   19. expresionP     -> - termino expresionP
 *   20. expresionP     -> ε
 *   21. termino        -> factor terminoP
 *   22. terminoP       -> * factor terminoP
 *   23. terminoP       -> / factor terminoP
 *   24. terminoP       -> ε
 *   25. factor         -> ( expresion )
 *   26. factor         -> identificador
 *   27. factor         -> numero
 * }
 */


/**
 * 2. Determinar la enumeración para el conjunto T
 */
enum Token { t_eof, // fin de archivo ($)
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

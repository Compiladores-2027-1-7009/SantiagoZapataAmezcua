#include "headers/ParserLL.hpp"

/*
 * En grammar.syms cada símbolo se guarda con una llave entera.
 * Los terminales usan su mismo valor del enum Token (de t_eof a t_div)
 * y los no terminales van después, por eso se les suma NT.
 */
const int NT = t_div + 1;

// Regresa la llave de un no terminal dentro de grammar.syms
static int nt(NoTerm n)
{
  return NT + n;
}

// El constructor guarda el lexer y carga la gramática y la tabla
ParserLL::ParserLL(Lexer *lexer)
{
    this->lexer = lexer;
    loadSyms();
    loadProds();
    loadTable();
}

ParserLL::~ParserLL()
{
}


void ParserLL::loadSyms()
{
  /*********************************************
   * 4. Agregar todos los símbolos (N'∪T) de G'*
   *********************************************/

  // terminales, de t_eof a t_div
  for (int t = t_eof; t <= t_div; t++)
    grammar.addSymbol(t, Symbol((Token) t));

  // no terminales, de strEmpty (ε) a n_factor
  for (int n = strEmpty; n <= n_factor; n++)
    grammar.addSymbol(nt((NoTerm) n), Symbol((NoTerm) n));

  grammar.setNum(16, 15);   // 16 terminales y 15 no terminales
  grammar.start = nt(n_programa);
}

void ParserLL::loadProds()
{
  /************************************************
   * 5. Agregar todas las producciones (P') de G' *
   ************************************************/
  // Los números son los mismos del comentario de Symbols.hpp
  int eps = nt(strEmpty);

  grammar.addProd(1,  Production(nt(n_programa),       {nt(n_declaraciones), nt(n_sentencias)}));
  grammar.addProd(2,  Production(nt(n_declaraciones),  {nt(n_declaracion), nt(n_declaracionesP)}));
  grammar.addProd(3,  Production(nt(n_declaracionesP), {nt(n_declaracion), nt(n_declaracionesP)}));
  grammar.addProd(4,  Production(nt(n_declaracionesP), {eps}));
  grammar.addProd(5,  Production(nt(n_declaracion),    {nt(n_tipo), nt(n_lista_var), t_pyc}));
  grammar.addProd(6,  Production(nt(n_tipo),           {t_int}));
  grammar.addProd(7,  Production(nt(n_tipo),           {t_float}));
  grammar.addProd(8,  Production(nt(n_lista_var),      {t_id, nt(n_lista_varP)}));
  grammar.addProd(9,  Production(nt(n_lista_varP),     {t_coma, t_id, nt(n_lista_varP)}));
  grammar.addProd(10, Production(nt(n_lista_varP),     {eps}));
  grammar.addProd(11, Production(nt(n_sentencias),     {nt(n_sentencia), nt(n_sentenciasP)}));
  grammar.addProd(12, Production(nt(n_sentenciasP),    {nt(n_sentencia), nt(n_sentenciasP)}));
  grammar.addProd(13, Production(nt(n_sentenciasP),    {eps}));
  grammar.addProd(14, Production(nt(n_sentencia),      {t_id, t_asig, nt(n_expresion), t_pyc}));
  grammar.addProd(15, Production(nt(n_sentencia),      {t_if, t_lpar, nt(n_expresion), t_rpar, nt(n_sentencias), t_else, nt(n_sentencias)}));
  grammar.addProd(16, Production(nt(n_sentencia),      {t_while, t_lpar, nt(n_expresion), t_rpar, nt(n_sentencias)}));
  grammar.addProd(17, Production(nt(n_expresion),      {nt(n_termino), nt(n_expresionP)}));
  grammar.addProd(18, Production(nt(n_expresionP),     {t_mas, nt(n_termino), nt(n_expresionP)}));
  grammar.addProd(19, Production(nt(n_expresionP),     {t_menos, nt(n_termino), nt(n_expresionP)}));
  grammar.addProd(20, Production(nt(n_expresionP),     {eps}));
  grammar.addProd(21, Production(nt(n_termino),        {nt(n_factor), nt(n_terminoP)}));
  grammar.addProd(22, Production(nt(n_terminoP),       {t_mul, nt(n_factor), nt(n_terminoP)}));
  grammar.addProd(23, Production(nt(n_terminoP),       {t_div, nt(n_factor), nt(n_terminoP)}));
  grammar.addProd(24, Production(nt(n_terminoP),       {eps}));
  grammar.addProd(25, Production(nt(n_factor),         {t_lpar, nt(n_expresion), t_rpar}));
  grammar.addProd(26, Production(nt(n_factor),         {t_id}));
  grammar.addProd(27, Production(nt(n_factor),         {t_num}));
}

void ParserLL::loadTable()
{

  /*************************************************
   **     6.Cargar la tabla de AS predictivo      **
   *************************************************/
  // table[no terminal][token] = número de producción que se aplica
  // Las casillas que no aparecen son error.

  table[n_programa][t_int] = 1;
  table[n_programa][t_float] = 1;

  table[n_declaraciones][t_int] = 2;
  table[n_declaraciones][t_float] = 2;

  table[n_declaracionesP][t_int] = 3;
  table[n_declaracionesP][t_float] = 3;
  table[n_declaracionesP][t_id] = 4;
  table[n_declaracionesP][t_if] = 4;
  table[n_declaracionesP][t_while] = 4;

  table[n_declaracion][t_int] = 5;
  table[n_declaracion][t_float] = 5;

  table[n_tipo][t_int] = 6;
  table[n_tipo][t_float] = 7;

  table[n_lista_var][t_id] = 8;

  table[n_lista_varP][t_coma] = 9;
  table[n_lista_varP][t_pyc] = 10;

  table[n_sentencias][t_id] = 11;
  table[n_sentencias][t_if] = 11;
  table[n_sentencias][t_while] = 11;

  // Con id, if y while aquí caben la 12 y la 13. Se deja la 12 para que el
  // cuerpo de un while o de un else se quede con todas las sentencias que
  // siguen, hasta un else o el fin del archivo (igual que el else colgante).
  table[n_sentenciasP][t_id] = 12;
  table[n_sentenciasP][t_if] = 12;
  table[n_sentenciasP][t_while] = 12;
  table[n_sentenciasP][t_else] = 13;
  table[n_sentenciasP][t_eof] = 13;

  table[n_sentencia][t_id] = 14;
  table[n_sentencia][t_if] = 15;
  table[n_sentencia][t_while] = 16;

  table[n_expresion][t_lpar] = 17;
  table[n_expresion][t_id] = 17;
  table[n_expresion][t_num] = 17;

  table[n_expresionP][t_mas] = 18;
  table[n_expresionP][t_menos] = 19;
  table[n_expresionP][t_pyc] = 20;
  table[n_expresionP][t_rpar] = 20;

  table[n_termino][t_lpar] = 21;
  table[n_termino][t_id] = 21;
  table[n_termino][t_num] = 21;

  table[n_terminoP][t_mul] = 22;
  table[n_terminoP][t_div] = 23;
  table[n_terminoP][t_mas] = 24;
  table[n_terminoP][t_menos] = 24;
  table[n_terminoP][t_pyc] = 24;
  table[n_terminoP][t_rpar] = 24;

  table[n_factor][t_lpar] = 25;
  table[n_factor][t_id] = 26;
  table[n_factor][t_num] = 27;
}

int ParserLL::parse()
{
  /**************************************************
   ** 7. Implementar el algoritmo de AS predictivo **
   **************************************************/

  //Auxiliares
  stack<Symbol> pila;
  map<Token, int>::iterator accion;
  vector<int> body;
  Symbol X;

  // La pila empieza con $ y encima el símbolo inicial
  pila.push(grammar.getSym(t_eof));
  pila.push(grammar.getSym(grammar.start));
  token = eat();

  while (true)
  {
    X = pila.top();

    if (X.getType() == terminal)
    {
      // Si el terminal de la pila no es el token que llegó, hay error
      if (X.getToken() != token)
        error("ERROR DE SINTAXIS en la línea " + to_string(lexer->getLine()));

      // Si los dos son $ ya se leyó todo el programa
      if (token == t_eof)
      {
        aceptar("La cadena es aceptada");
        return 0;
      }

      pila.pop();
      token = eat();
    }
    else
    {
      // Se busca en la tabla qué producción usar con el token actual
      map<Token, int> &fila = table[X.getNoTerm()];
      accion = fila.find(token);
      if (accion == fila.end())
        error("ERROR DE SINTAXIS en la línea " + to_string(lexer->getLine()));

      // Se cambia el no terminal por el cuerpo de la producción, al revés
      pila.pop();
      body = grammar.getProd(accion->second).getBody();
      for (int i = body.size() - 1; i >= 0; i--)
      {
        Symbol s = grammar.getSym(body[i]);
        // ε no se mete a la pila
        if (s.getType() == nonterminal && s.getNoTerm() == strEmpty)
          continue;
        pila.push(s);
      }
    }
  }
}

void ParserLL::error(string msg)
{
    cout<<msg<<endl;
    exit(EXIT_FAILURE);
}

Token ParserLL::eat()
{
    return (Token) lexer->yylex();
}

void ParserLL::aceptar(string msg)
{
    cout<<msg<<endl;
}

/* analizador.l - Analizador lexico. Recibe un archivo .art y
                  escribe los tokens en un archivo .tokens        */

%option noyywrap
%option yylineno

%x COMENTARIO

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char com[4096];
int  nc = 0;

void acum(char *s)
{
    int l = strlen(s);
    if (nc + l < 4095) { strcpy(com + nc, s); nc += l; }
}
%}

DIGITO      [0-9]
LETRA       [a-zA-Z_]
ENTERO      {DIGITO}+
REAL        {DIGITO}+"."{DIGITO}+([eE][+-]?{DIGITO}+)?
ID          {LETRA}({LETRA}|{DIGITO})*
CADENA      \"[^\"\n]*\"

%%

    /* e. Palabras reservadas (antes que ID) */
"if"|"then"|"else"|"while"|"do"|"case"|"is"|"void"|"true"|"false"|"begin"|"end"|"not" {
                fprintf(yyout, "<reservada, %s>\n", yytext); }

    /* g. Comentario de una linea */
"--".*          { fprintf(yyout, "<comentario_linea, %s>\n", yytext); }

    /* h. Comentario multilinea  <* ... *>  */
"<*"            { BEGIN(COMENTARIO); nc = 0; com[0] = '\0'; acum(yytext); }
<COMENTARIO>"*>"    { acum(yytext); BEGIN(INITIAL);
                      fprintf(yyout, "<comentario_multilinea, %s>\n", com); }
<COMENTARIO>\n      { acum(" "); }
<COMENTARIO>.       { acum(yytext); }
<COMENTARIO><<EOF>> { fprintf(yyout, "<error, comentario sin cerrar en la linea %d>\n",
                              yylineno); yyterminate(); }

    /* b. Numeros reales   a. Numeros enteros */
{REAL}          { fprintf(yyout, "<real, %s>\n", yytext); }
{ENTERO}        { fprintf(yyout, "<entero, %s>\n", yytext); }

    /* c. Identificadores estilo C */
{ID}            { fprintf(yyout, "<id, %s>\n", yytext); }

    /* d. Cadenas entre comillas dobles */
{CADENA}        { fprintf(yyout, "<cadena, %s>\n", yytext); }

    /* k. Operador de asignacion */
":="            { fprintf(yyout, "<asignacion, %s>\n", yytext); }

    /* j. Operadores relacionales */
"<>"            { fprintf(yyout, "<relacional, %s>\n", yytext); }
[<>=]           { fprintf(yyout, "<relacional, %s>\n", yytext); }

    /* i. Operadores aritmeticos */
[+\-*/%]        { fprintf(yyout, "<aritmetico, %s>\n", yytext); }

    /* l. Simbolos especiales */
[(){};,]        { fprintf(yyout, "<especial, %s>\n", yytext); }

    /* f. Espacios en blanco */
[ \t\r]+        { fprintf(yyout, "<espacio, %d>\n", yyleng); }
\n              { fprintf(yyout, "<salto_linea, \\n>\n"); }

    /* m. Error lexico */
.               { fprintf(yyout, "<error, caracter '%s' en la linea %d>\n",
                          yytext, yylineno); }

%%

int main(int argc, char **argv)
{
    char  salida[512];
    char *punto;
    size_t base;
    FILE *entrada, *fsal;

    if (argc != 2) {
        fprintf(stderr, "Uso: %s archivo.art\n", argv[0]);
        return 1;
    }

    /* Solo se aceptan archivos con extension .art */
    punto = strrchr(argv[1], '.');
    if (punto == NULL || strcmp(punto, ".art") != 0) {
        fprintf(stderr, "Error: el archivo de entrada debe tener extension .art\n");
        return 1;
    }

    entrada = fopen(argv[1], "r");
    if (entrada == NULL) { perror(argv[1]); return 1; }

    /* Se construye el nombre de salida cambiando .art por .tokens */
    base = punto - argv[1];
    strncpy(salida, argv[1], base);
    salida[base] = '\0';
    strcat(salida, ".tokens");

    fsal = fopen(salida, "w");
    if (fsal == NULL) { perror(salida); return 1; }

    yyin  = entrada;
    yyout = fsal;

    yylex();

    fclose(entrada);
    fclose(fsal);
    printf("Tokens escritos en %s\n", salida);
    return 0;
}

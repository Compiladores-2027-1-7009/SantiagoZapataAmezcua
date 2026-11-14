/* sumalineas.l - Lineas terminadas en A: imprime la suma.
                  Lineas terminadas en B: imprime la linea tal cual. */

%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long suma = 0;
char linea[4096];
int  n = 0;

void agrega(char *s)
{
    int l = strlen(s);
    if (n + l < 4095) { strcpy(linea + n, s); n += l; }
}

void limpia(void)
{
    suma = 0;
    n = 0;
    linea[0] = '\0';
}
%}

%%

-?[0-9]+        { suma += atol(yytext); agrega(yytext); }
[ \t]+          { agrega(yytext); }
A[ \t]*\n       { printf("%ld\n", suma); limpia(); }
B[ \t]*\n       { agrega("B"); printf("%s\n", linea); limpia(); }
\n              { limpia(); }
.               { agrega(yytext); }

%%

int main(int argc, char **argv)
{
    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (f == NULL) { perror(argv[1]); return 1; }
        yyin = f;
    }
    yylex();
    return 0;
}

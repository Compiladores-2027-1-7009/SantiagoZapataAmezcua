/* mayusculas.l - Convierte a mayusculas las palabras de un archivo */

%option noyywrap

%{
#include <stdio.h>
%}

%%

[a-z]+      { int i;
              for (i = 0; i < yyleng; i++)
                  fprintf(yyout, "%c", yytext[i] - 'a' + 'A'); }
.|\n        { ECHO; }

%%

int main(int argc, char **argv)
{
    FILE *f, *o;

    if (argc != 3) {
        fprintf(stderr, "Uso: %s entrada salida\n", argv[0]);
        return 1;
    }

    f = fopen(argv[1], "r");
    if (f == NULL) { perror(argv[1]); return 1; }
    yyin = f;

    o = fopen(argv[2], "w");
    if (o == NULL) { perror(argv[2]); return 1; }
    yyout = o;

    yylex();

    fclose(yyin);
    fclose(yyout);
    return 0;
}

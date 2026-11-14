/* wc.l - Imita el comando wc de Linux */

%option noyywrap

%{
#include <stdio.h>
int lineas = 0, palabras = 0, bytes = 0;
%}

%%

\n              { lineas++;  bytes++; }
[^ \t\n]+       { palabras++; bytes += yyleng; }
.               { bytes++; }

%%

int main(int argc, char **argv)
{
    char *nombre = "";

    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (f == NULL) { perror(argv[1]); return 1; }
        yyin = f;
        nombre = argv[1];
    }

    yylex();
    printf("%d %d %d %s\n", lineas, palabras, bytes, nombre);
    return 0;
}

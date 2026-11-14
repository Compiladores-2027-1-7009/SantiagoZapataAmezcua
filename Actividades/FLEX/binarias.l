/* binarias.l - Suma en base 10 todas las literales binarias 0b... */

%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
long suma = 0;
%}

%%

0b[01]+     { suma += strtol(yytext + 2, NULL, 2); }
.|\n        { /* se ignora el resto de la entrada */ }

%%

int main(int argc, char **argv)
{
    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (f == NULL) { perror(argv[1]); return 1; }
        yyin = f;
    }
    yylex();
    printf("%ld\n", suma);
    return 0;
}

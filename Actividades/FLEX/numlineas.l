/* numlineas.l - Imprime la entrada numerando cada linea */

%option noyywrap

%{
#include <stdio.h>
int linea = 1;
%}

%%

^.*\n       { fprintf(yyout, "%d  %s", linea++, yytext); }
^.+         { fprintf(yyout, "%d  %s\n", linea++, yytext); }

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

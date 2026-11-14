/* gato.l - Decide el resultado de cada turno del juego del Gato */

%option noyywrap

%{
#include <stdio.h>

char tablero[9];
int  pos = 0;

void evaluar(void)
{
    static const int linea[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},      /* horizontales */
        {0,3,6}, {1,4,7}, {2,5,8},      /* verticales   */
        {0,4,8}, {2,4,6}                /* diagonales   */
    };
    int i, ganaX = 0, ganaO = 0, llena = 1;

    for (i = 0; i < 9; i++)
        if (tablero[i] == '_') llena = 0;

    for (i = 0; i < 8; i++) {
        char a = tablero[linea[i][0]];
        char b = tablero[linea[i][1]];
        char c = tablero[linea[i][2]];
        if (a != '_' && a == b && b == c) {
            if (a == 'X') ganaX = 1;
            else          ganaO = 1;
        }
    }

    if      (ganaX) printf("gana X\n");
    else if (ganaO) printf("gana O\n");
    else if (llena) printf("empate\n");
    else            printf("sin ganador\n");
}
%}

%%

[XO_]       { tablero[pos++] = yytext[0];
              if (pos == 9) { evaluar(); pos = 0; } }
.|\n        { /* saltos de linea y separadores */ }

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

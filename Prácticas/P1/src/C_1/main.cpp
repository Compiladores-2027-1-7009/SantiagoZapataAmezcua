// main.cpp
// Abre el archivo que se pasa como argumento, le pide tokens al
// lexer hasta que se acaba el archivo e imprime "token, lexema".
// Santiago Zapata Amezcua

#include <iostream>
#include <fstream>
#include "Lexer.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Uso: ./compiler <archivo>" << endl;
        return 1;
    }

    ifstream archivo(argv[1]);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo " << argv[1] << endl;
        return 1;
    }

    Lexer lexer(&archivo);
    int token;

    // yylex regresa 0 cuando llega al fin del archivo
    while ((token = lexer.yylex()) != FIN) {
        cout << token << ", " << lexer.YYText() << endl;
    }

    return 0;
}

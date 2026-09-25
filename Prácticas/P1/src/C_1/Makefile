# Makefile para el analizador léxico de C_1
# Santiago Zapata Amezcua

compiler: Lexer.cpp main.cpp Lexer.hpp tokens.hpp
	g++ Lexer.cpp main.cpp -o compiler

Lexer.cpp: lexer.ll
	flex++ lexer.ll

run: compiler
	./compiler prueba

clean:
	rm -f Lexer.cpp compiler

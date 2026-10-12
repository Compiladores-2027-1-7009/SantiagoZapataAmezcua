CXX?=clang++
LEX=flex++
EXE=analyzer
CXXDEBUG= -g -Wall
CXXSTD=-std=c++14
CXXFLAGS= -Wno-deprecated-register -O0 $(CXXDEBUG) $(CXXSTD)

CPPOBJ= main Parser Lexer

FILES= $(addsuffix .cpp, $(CPPOBJ))
OBJS = $(addsuffix .o, $(CPPOBJ))

CLEANLIST = $(OBJS) $(EXE)


# con "make" se genera Lexer.cpp, se compila todo y queda el ejecutable analyzer
.PHONY: all
all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS)

# Lexer.cpp sale de lexer.ll con flex++
Lexer.cpp: lexer.ll
	$(LEX) lexer.ll

.PHONY: clean
clean:
	rm -rf $(CLEANLIST)

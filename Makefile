CC=clang++
CCLLVMFLAGS=-g -Wall -fstandalone-debug `llvm-config --cxxflags --system-libs --ldflags --libs core` -Wno-unused-command-line-argument
CCFLAGS=-g -fstandalone-debug

FLEX=flex
FLEX_OPTS=-Pflomathica

BISON=bison
BISON_OPTS=-t -pflomathica

OBJS=build/Absyn.o build/Buffer.o build/Lexer.o build/Parser.o build/ParserWrapper.o build/Printer.o build/Interpreter.o build/main.o

.PHONY : clean distclean

all : Flomathica

clean :
	rm build/*.o Flomathica

Flomathica : ${OBJS}
	${CC} ${CCLLVMFLAGS} ${OBJS} -o Flomathica
	@echo "\033[92m>> Build Flomathica successful <<\033[0m"

build/Absyn.o : Parser/Absyn.C Parser/Absyn.H
	${CC} ${CCFLAGS} -c Parser/Absyn.C -o build/Absyn.o

build/Buffer.o : Parser/Buffer.C Parser/Buffer.H
	${CC} ${CCFLAGS} -c Parser/Buffer.C -o build/Buffer.o

build/Lexer.o : Parser/Lexer.C Parser/Parser.H
	${CC} ${CCFLAGS} -c Parser/Lexer.C -o build/Lexer.o

build/Parser.o : Parser/Parser.C Parser/Absyn.H
	${CC} ${CCFLAGS} -c Parser/Parser.C -o build/Parser.o

build/ParserWrapper.o : Parser/ParserWrapper.cpp Parser/Parser.H
	${CC} ${CCFLAGS} -c Parser/ParserWrapper.cpp -o build/ParserWrapper.o

build/Printer.o : Parser/Printer.C Parser/Printer.H Parser/Absyn.H
	${CC} ${CCFLAGS} -c Parser/Printer.C -o build/Printer.o

build/Interpreter.o : Interpreter/Interpreter.cpp Interpreter/Interpreter.h
	${CC} ${CCLLVMFLAGS} -Wno-unused-parameter -c Interpreter/Interpreter.cpp -o build/Interpreter.o

build/main.o : main.cpp Interpreter/Interpreter.h Parser/ParserWrapper.h
	${CC} ${CCLLVMFLAGS} -c main.cpp -o build/main.o

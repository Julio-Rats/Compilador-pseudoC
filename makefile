all: compilador clear

compilador: main
			gcc -O3 -o compilador *.o

clear:
			rm *.h.gch *.o
main: lexico
			gcc -c -O3 main.c
lexico: parser
			gcc -c -O3 lexico.h
			gcc -c -O3 lexico.c
parser: semantico
			gcc -c -O3 parser.h
			gcc -c -O3 parser.c
semantico: virtualmachine
			gcc -c -O3 semantico.h
			gcc -c -O3 semantico.c
virtualmachine:
			gcc -c -O3 virtualmachine.h
			gcc -c -O3 virtualmachine.c

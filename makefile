all: compilador clear

compilador: main
			gcc -o compilador *.o

clear:
			rm *.h.gch *.o
main: lexico
			gcc -c main.c
lexico: parser
			gcc -c lexico.h
			gcc -c lexico.c
parser:
			gcc -c parser.h
			gcc -c  parser.c

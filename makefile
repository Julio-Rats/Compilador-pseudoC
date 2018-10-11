all:comp
comp: obj
		gcc *.o -o compilador
		rm *.gch *.o
obj:
		gcc -c *.c
		gcc -c *.h

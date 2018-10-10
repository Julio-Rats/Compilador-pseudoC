all:comp
comp: obj
		gcc *.o -o analiLexico
		rm *.gch *.o
obj:
		gcc -c *.c
		gcc -c *.h

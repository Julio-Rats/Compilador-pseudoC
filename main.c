#include <stdio.h>
#include <stdlib.h>
#include "lexico.h"

int main(int argc, char *argv[]){
	arq = fopen(argv[1],"r");
	if (!arq){
			perror("FILE: ");
			exit(9);
	}
	Token tok;
	rewind(arq);
	while(!feof(arq)){
			tok = getToken();
			printf("lexema = %s \t\t Linha = %d || Coluna = %d \t--  enum = %d\n",tok.lexema, tok.linha, tok.coluna, tok.ttoken );
	}
  fclose(arq);
	return 0;
}

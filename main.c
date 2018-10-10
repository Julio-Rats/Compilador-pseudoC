#include <stdio.h>
#include <stdlib.h>

#include "lexico.h"
#include "parser.h"

int main(int argc, char *argv[]){
	arq = fopen(argv[1],"r");
	if (!arq){
			char fileError[45];
			strcat(fileError,"Arquivo - ");
			strcat(fileError,argv[1]);
			perror(fileError);
			exit(9);
	}

	// printf("%s\n", decod_Token(NUMfloat));
	// exit(0);

	rewind(arq);

	while(!feof(arq)){
			token_atual = getToken();
			printf("lexema = %s \t\t Linha = %d || Coluna = %d \t--  enum = %d\n",token_atual.lexema, token_atual.linha, token_atual.coluna, token_atual.ttoken );
	}

	rewind(arq);

	token_atual = getToken();
	function();

  fclose(arq);
	return 0;
}

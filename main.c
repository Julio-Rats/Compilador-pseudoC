#include <stdio.h>
#include <stdlib.h>

#include "lexico.h"
#include "parser.h"

int main(int argc, char *argv[]){
	if (argc < 2){
			fprintf(stderr, "Erro de paramentro:\n\nExemplo: %s <Input>\n\nInput: Arquivo fonte para compilação\n\n", argv[0]);
			exit(7);
	}

	file_src = fopen(argv[1],"r");
	if (!file_src){
			char   fileError[45];
			strcat(fileError,"Arquivo - ");
			strcat(fileError,argv[1]);
			perror(fileError);
			exit  (9);
	}

	parser();
	// rewind  (file_src);
	//
	//
	// while(!feof(file_src)){
	// 		token_atual = getToken();
	// 		printf ("lexema = %s \t\t Linha = %d || Coluna = %d \t--  Token = %s\n",token_atual.lexema, token_atual.linha, token_atual.coluna, decod_Token(token_atual.ttoken) );
	// }

  fclose (file_src);
	return 0;
}

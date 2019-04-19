#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

int main(int argc, char *argv[]){
	if (argc < 2){
			fprintf(stderr, "Erro de paramentro:\n\nExemplo: %s <Input>\n\nInput: Arquivo fonte para compilação\n\n", argv[0]);
			exit(7);
	}

	file_src = fopen(argv[1],"r");
	if (!file_src){
			char   fileError[64];
			sprintf(fileError,"%s%s ","Arquivo = ", argv[1]);
			perror(fileError);
			exit  (9);
	}

	t_valuereturns aux = parser();
  fclose (file_src);

	exec(aux.listQuad);

	return 0;
}

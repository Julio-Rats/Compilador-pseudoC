#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "virtualmachine.h"

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


	// DESCOMENTAR EMBAIXO PRA VER AS QUADUPLAS

	// if (aux.listQuad)
	// 	for(Quad *q=aux.listQuad;q;q=q->next){
	// 			if (q->param1)
	// 				printf("(%s", q->param1);
	// 			if (q->param2)
	// 				printf(", %s", q->param2);
	// 			if (q->param3)
	// 				printf(", %s", q->param3);
	// 			else{
	// 				printf(")\n");
	// 				continue;
	// 				}
	// 			if (q->param4)
	// 				printf(", %s)\n", q->param4);
	// 			else
	// 				printf(")\n");
	// }

	exec(aux.listQuad);

	return 0;
}

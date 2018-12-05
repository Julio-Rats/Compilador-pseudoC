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

	// t_list *teste;
	// addList(teste,8);
	// addList(teste, (void*) 4);
	// teste = malloc(sizeof(t_list));
	// teste->DATA = a;
	// teste->NEXT = malloc(sizeof(t_list));
	// teste->NEXT->DATA = 20;
	// printf("%d\n", teste->DATA);

	file_src = fopen(argv[1],"r");
	if (!file_src){
			char   fileError[64];
			sprintf(fileError,"%s%s ","Arquivo = ", argv[1]);
			perror(fileError);
			exit  (9);
	}
	//
	parser();
	// rewind  (file_src);
	// //
	// //
	// while(!feof(file_src)){
	// 		token_atual = getToken();
	// 		printf ("lexema = %s \t\t Linha = %d || Coluna = %d \t--  Token = %s\n",token_atual.lexema, token_atual.linha, token_atual.coluna, decod_Token(token_atual.ttoken) );
	//
	// for(int i=0;i<lenVariables;i++){
	// 		printf("%s --> %d\n", listVariables[i].id_var, listVariables[i].value_var);
	// }
	// Quad *list;
	// Quad *q1 = geraQuad("1","2","3","4");
	// Quad *q2 = geraQuad("5","6","7","8");
	// Quad *q3 = geraQuad("9","10","11","12");
	// q1 = addQuad(q1,q2);
	// q2 = addQuad(q2,q3);
	// list = addQuad(list,q1);
	// for(Quad *aux=list;aux;aux=aux->next){
	// 		printf("%s ", aux->param1);
	// 		printf("%s ", aux->param2);
	// 		printf("%s ", aux->param3);
	// 		printf("%s\n", aux->param4);
	// }
  fclose (file_src);

	for(int i=0;i<lenVariables;i++)
			printf("var = %s\n", listVariables[i].id_var);

	printf("%d\n", lenVariables);
	return 0;
}

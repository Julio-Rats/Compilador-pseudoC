#ifndef  _PARSER_
#define   _PARSER_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexico.h"
#include "virtualmachine.h"

typedef struct{
      unsigned short int  bool_leftValue:1;
      Quad                *listQuad;
      char                *NameResult;
}t_valuereturns;

// Variavel que controla o analisador lexico, com o lexema e Tipo de Token atual.

Token  token_atual;

//Variavel que indica o nivel atual de variaveis

static u_int8_t nivel_variaveis = 0;

/*
    Funções que compõem o analisador sintatico, expressado a gramatica da linguagem
      a ser compilada.
*/

char* decod_Token(TToken token);
char* consome_token(TToken consome);
char* busca_variaveis(char *lexema);
void  deleta_variaveis();
void  error(TToken consome);
void  add_id(Token token, int tipo);
void  arglist();
void  arg();
void  restoArglist();
int   type();
t_valuereturns  parser();
t_valuereturns  function();
t_valuereturns  declaration();
t_valuereturns  identList(int vartype);
t_valuereturns  restoIdentList(int vartype);
t_valuereturns bloco(char* jump_cont, char* jump_exit);
t_valuereturns stmtList(char* jump_cont, char* jump_exit);
t_valuereturns stmt(char* jump_cont, char* jump_exit);
t_valuereturns forStmt();
t_valuereturns optExpr();
t_valuereturns ioStmt();
t_valuereturns outList();
t_valuereturns out();
t_valuereturns restOutList();
t_valuereturns whileStmt();
t_valuereturns ifStmt();
t_valuereturns elsePart();
t_valuereturns expr();
t_valuereturns atrib();
t_valuereturns restoAtrib(char *parametro);
t_valuereturns or();
t_valuereturns restoOr(char *parametro);
t_valuereturns and();
t_valuereturns restoAnd(char *parametro);
t_valuereturns not();
t_valuereturns rel();
t_valuereturns restorel(char *parametro);
t_valuereturns add();
t_valuereturns restoAdd(char* parametro);
t_valuereturns mult();
t_valuereturns restoMult(char *parametro);
t_valuereturns uno();
t_valuereturns fator();

#endif

#ifndef  _PARSER_
#define   _PARSER_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexico.h"
#include "virtualmachine.h"

typedef struct{
      u_int8_t  bool_leftValue:1;
      Quad     *listQuad;
      u_int8_t *NameResult;
}t_valuereturns;

// Variavel que controla o analisador lexico, com o lexema e Tipo de Token atual.

Token  token_atual;

//Variavel que indica o nivel atual de variaveis

static u_int8_t nivel_variaveis = 0;

/*
    Funções que compõem o analisador sintatico, expressado a gramatica da linguagem
      a ser compilada.
*/

u_int8_t type();
u_int8_t* decod_Token(TToken token);
u_int8_t* consome_token(TToken consome);
u_int8_t* busca_variaveis(u_int8_t *lexema);
void  deleta_variaveis();
void  error(TToken consome);
void  add_id(Token token, u_int8_t tipo);
void  arglist();
void  arg();
void  restoArglist();
t_valuereturns parser();
t_valuereturns function();
t_valuereturns declaration();
t_valuereturns identList(u_int8_t vartype);
t_valuereturns restoIdentList(u_int8_t vartype);
t_valuereturns bloco(u_int8_t* jump_cont, u_int8_t* jump_exit);
t_valuereturns stmtList(u_int8_t* jump_cont, u_int8_t* jump_exit);
t_valuereturns stmt(u_int8_t* jump_cont, u_int8_t* jump_exit);
t_valuereturns forStmt();
t_valuereturns optExpr();
t_valuereturns ioStmt();
t_valuereturns outList();
t_valuereturns out();
t_valuereturns restOutList();
t_valuereturns whileStmt();
t_valuereturns ifStmt(u_int8_t* jump_cont, u_int8_t* jump_exit);
t_valuereturns elsePart(u_int8_t* jump_cont, u_int8_t* jump_exit);
t_valuereturns expr();
t_valuereturns atrib();
t_valuereturns restoAtrib(u_int8_t *parametro);
t_valuereturns or();
t_valuereturns restoOr(u_int8_t *parametro);
t_valuereturns and();
t_valuereturns restoAnd(u_int8_t *parametro);
t_valuereturns not();
t_valuereturns rel();
t_valuereturns restorel(u_int8_t *parametro);
t_valuereturns add();
t_valuereturns restoAdd(u_int8_t* parametro);
t_valuereturns mult();
t_valuereturns restoMult(u_int8_t *parametro);
t_valuereturns uno();
t_valuereturns fator();

#endif

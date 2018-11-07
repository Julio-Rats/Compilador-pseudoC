#ifndef  _PARSER_
#define  _PARSER_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexico.h"
#include "virtualmachine.h"

typedef struct{
      int  bool_leftValue;
}t_valuereturns;

// Variavel que controla o analisador lexico, com o lexema e Tipo de Token atual.

Token  token_atual;

/*
    Funções que compõem o analisador sintatico, expressado a gramatica da linguagem
      a ser compilada.
*/

char* decod_Token(TToken token);
char* consome_token(TToken consome);
void  error(TToken consome);
void  parser();
void  function();
void  arglist();
void  arg();
void  restoArglist();
int   type();
void  bloco();
void  stmtList();
void  stmt();
void  declaration();
void  identList(int vartype);
void  restoIdentList(int vartype);
void  forStmt();
void  optExpr();
void  ioStmt();
void  outList();
void  out();
void  restOutList();
void  whileStmt();
void  ifStmt();
void  elsePart();
void  expr();
void  atrib();
t_valuereturns restoAtrib();
t_valuereturns or();
t_valuereturns restoOr();
t_valuereturns and();
t_valuereturns restoAnd();
t_valuereturns not();
t_valuereturns rel();
t_valuereturns restorel();
t_valuereturns add();
t_valuereturns restoAdd();
t_valuereturns mult();
t_valuereturns restoMult();
t_valuereturns uno();
t_valuereturns fator();

#endif

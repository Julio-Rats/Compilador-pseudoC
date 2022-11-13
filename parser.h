#ifndef _PARSER_
#define _PARSER_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexico.h"
#include "virtualmachine.h"

#define ERROR_MEM 1
#define ERROR_CONSUME 2
#define ERROR_DECLAR 3
#define ERROR_COMP 4
#define ERROR_TOKEN 5

typedef struct
{
      Quad *listQuad;
      char *NameResult;
      u_int8_t bool_leftValue : 1;
} t_valuereturns;

// Variavel que controla o analisador lexico, com o lexema e Tipo de Token atual.

Token token_atual;

/*
    Funções que compõem o analisador sintatico, expressado a gramatica da linguagem
      a ser compilada.
*/

u_int8_t type();
char *decod_Token(TToken token);
char *consome_token(TToken consome);
char *busca_variaveis(char *lexema);
void error_alloc(char *var, char *func);
void deleta_variaveis();
void error(TToken consome);
void add_id(Token token, u_int8_t tipo);
void arglist();
void arg();
void restoArglist();
t_valuereturns parser();
t_valuereturns function();
t_valuereturns declaration();
t_valuereturns identList(u_int8_t vartype);
t_valuereturns restoIdentList(u_int8_t vartype);
t_valuereturns bloco(char *jump_cont, char *jump_exit);
t_valuereturns stmtList(char *jump_cont, char *jump_exit);
t_valuereturns stmt(char *jump_cont, char *jump_exit);
t_valuereturns forStmt();
t_valuereturns optExpr();
t_valuereturns ioStmt();
t_valuereturns outList();
t_valuereturns out();
t_valuereturns restOutList();
t_valuereturns whileStmt();
t_valuereturns ifStmt(char *jump_cont, char *jump_exit);
t_valuereturns elsePart(char *jump_cont, char *jump_exit);
t_valuereturns expr();
t_valuereturns atrib();
t_valuereturns restoAtrib(char *parametro);
t_valuereturns or ();
t_valuereturns restoOr(char *parametro);
t_valuereturns and ();
t_valuereturns restoAnd(char *parametro);
t_valuereturns not();
t_valuereturns rel();
t_valuereturns restorel(char *parametro);
t_valuereturns add();
t_valuereturns restoAdd(char *parametro);
t_valuereturns mult();
t_valuereturns restoMult(char *parametro);
t_valuereturns uno();
t_valuereturns fator();

#endif

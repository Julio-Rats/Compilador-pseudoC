#ifndef PARSER_H
#define  PARSER_H

#include <stdio.h>
#include "lexico.h"

// Variavel que controla o analisador lexico, com o lexema e Tipo de Token atual.

Token  token_atual;

/*
    Funções que compõem o analisador sintatico, expressado a gramatica da linguagem
      a ser compilada.
*/

char* decod_Token(TToken token);
void consome_token(TToken consome);
void error(TToken consome);
void parser();
void function();
void arglist();
void arg();
void restoArglist();
void type();
void bloco();
void stmtList();
void stmt();
void declaration();
void identList();
void restoIdentList();
void forStmt();
void optExpr();
void ioStmt();
void outList();
void out();
void restOutList();
void whileStmt();
void ifStmt();
void elsePart();
void expr();
int atrib();
int restoAtrib();
int or();
int restoOr();
int and();
int restoAnd();
int not();
int rel();
int restorel();
int add();
int restoAdd();
int mult();
int restoMult();
int uno();
int fator();

#endif

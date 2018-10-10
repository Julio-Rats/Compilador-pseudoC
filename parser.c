#include "parser.h"

void consome_token(TToken consome){
    if (consome == token_atual.ttoken){
        token_atual = getToken();
        return;
    }
    error(consome);
}

void error(TToken consome){
    printf("\nError de Compilação:  Linha %d, coluna %d", token_atual.linha,token_atual.coluna);
    printf("\n\tEsperava \"%s\" mas foi recebido \"%s\"\n\n", decod_Token(consome), token_atual.lexema);
    fclose(arq);
    exit(0);
}

void function(){
    type();
    consome_token(IDENT);
    consome_token(ABRIPAR);
    arglist();
    consome_token(FECHAPAR);
    bloco();
}

void arglist(){
    if ((token_atual.ttoken == FLOAT)||(token_atual.ttoken == INT)){
      arg();
      restoArglist();
    }
}

void arg(){
    type();
    consome_token(IDENT);
}

void restoArglist(){
    if (token_atual.ttoken == VIRG){
      consome_token(VIRG);
      arglist();
    }
}

void type(){
    if (token_atual.ttoken == INT){
        consome_token(INT);
    }else{
        consome_token(FLOAT);
    }
}

void bloco(){
    consome_token(ABRICHAV);
    stmtList();
    consome_token(FECHACHAV);
}

void stmtList(){
    if ((   token_atual.ttoken == FOR)    ||(token_atual.ttoken==PRINT)  ||(token_atual.ttoken==SCAN)
          ||(token_atual.ttoken==WHILE)   ||(token_atual.ttoken==NOT)    ||(token_atual.ttoken==ABRIPAR)
          ||(token_atual.ttoken==SOMA)    ||(token_atual.ttoken==SUB)    ||(token_atual.ttoken==IDENT)
          ||(token_atual.ttoken==NUMint)  ||(token_atual.ttoken==NUMfloat)||(token_atual.ttoken==IF)
          ||(token_atual.ttoken==ABRICHAV)||(token_atual.ttoken==FLOAT)  ||(token_atual.ttoken==INT)
          ||(token_atual.ttoken==PONTVIRG)){
            stmt();
            stmtList();
          }
}

void stmt(){
    if (token_atual.ttoken==FOR){
        forStmt();
    }else if ((token_atual.ttoken==PRINT)||(token_atual.ttoken==SCAN)){
        ioStmt();
    }else if (token_atual.ttoken==WHILE){
        whileStmt();
    }else if ((token_atual.ttoken==NOT)      ||(token_atual.ttoken==ABRIPAR)
              ||(token_atual.ttoken==SOMA)   ||(token_atual.ttoken==SUB) ||(token_atual.ttoken==IDENT)
              ||(token_atual.ttoken==NUMint) ||(token_atual.ttoken==NUMfloat)){
        expr();
        consome_token(PONTVIRG);
    }else if (token_atual.ttoken==IF){
        ifStmt();
    }else if (token_atual.ttoken==ABRICHAV){
        bloco();
    }else if ((token_atual.ttoken==FLOAT)||(token_atual.ttoken==INT)){
        declaration();
    }else{
        consome_token(PONTVIRG);
    }
}

void declaration(){
    type();
    identList();
    consome_token(PONTVIRG);
}

void identList(){
    consome_token(IDENT);
    restoIdentList();
}

void restoIdentList(){
    if (token_atual.ttoken==VIRG){
      consome_token(VIRG);
      consome_token(IDENT);
      restoIdentList();
    }
}

void forStmt(){
    consome_token(FOR);
    consome_token(ABRIPAR);
    optExpr();
    consome_token(PONTVIRG);
    optExpr();
    consome_token(PONTVIRG);
    optExpr();
    consome_token(FECHAPAR);
    stmt();
}

void optExpr(){
    if ((token_atual.ttoken==NOT)            ||(token_atual.ttoken==ABRIPAR)
            ||(token_atual.ttoken==SOMA)   ||(token_atual.ttoken==SUB) ||(token_atual.ttoken==IDENT)
            ||(token_atual.ttoken==NUMint) ||(token_atual.ttoken==NUMfloat)){
              expr();
    }
}

void ioStmt(){
    if (token_atual.ttoken==SCAN){
        consome_token(SCAN);
        consome_token(ABRIPAR);
        consome_token(STR);
        consome_token(VIRG);
        consome_token(IDENT);
        consome_token(FECHAPAR);
        consome_token(PONTVIRG);
    }else{
        consome_token(PRINT);
        consome_token(ABRIPAR);
        outList();
        consome_token(FECHAPAR);
        consome_token(PONTVIRG);
    }
}

void outList(){
    out();
    restOutList();
}

void out(){
    if (token_atual.ttoken==STR){
          consome_token(STR);
    }else if (token_atual.ttoken==IDENT){
          consome_token(IDENT);
    }else if (token_atual.ttoken==NUMint){
          consome_token(NUMint);
    }else{
          consome_token(NUMfloat);
    }
}

void restOutList(){
    if (token_atual.ttoken==VIRG){
        consome_token(VIRG);
        out();
        restOutList();
    }
}

void whileStmt(){
    consome_token(WHILE);
    consome_token(ABRIPAR);
    expr();
    consome_token(FECHAPAR);
    stmt();
}

void ifStmt(){
    consome_token(IF);
    consome_token(ABRIPAR);
    expr();
    consome_token(FECHAPAR);
    stmt();
    elsePart();
}

void elsePart(){
    if (token_atual.ttoken==ELSE){
        consome_token(ELSE);
        stmt();
    }
}

void expr(){
    atrib();
}

void atrib(){
    or();
    restoAtrib();
}

void restoAtrib(){
    if (token_atual.ttoken==ATRIB){
        consome_token(ATRIB);
        atrib();
    }
}

void or(){
    and();
    restoOr();
}

void restoOr(){
    if (token_atual.ttoken==OR){
        consome_token(OR);
        and();
        restoOr();
    }
}

void and(){
    not();
    restoAnd();
}

void restoAnd(){
    if (token_atual.ttoken==AND){
        consome_token(AND);
        not();
        restoAnd();
    }
}

void not(){
    if (token_atual.ttoken==NOT){
        consome_token(NOT);
        not();
    }else{
        rel();
    }
}

void rel(){
    add();
    restorel();
}

void restorel(){
    if (token_atual.ttoken==IGUAL){
        consome_token(IGUAL);
        add();
    }else if (token_atual.ttoken==NIGUAL){
        consome_token(NIGUAL);
        add();
    }else if (token_atual.ttoken==MENOR){
        consome_token(MENOR);
        add();
    }else if (token_atual.ttoken==MENORIGUAL){
        consome_token(MENORIGUAL);
        add();
    }else if (token_atual.ttoken==MAIOR){
        consome_token(MAIOR);
        add();
    }else if (token_atual.ttoken==MAIORIGUAL){
        consome_token(MAIORIGUAL);
        add();
    }
}

void add(){
    mult();
    restoAdd();
}

void restoAdd(){
    if (token_atual.ttoken==SOMA){
        consome_token(SOMA);
        mult();
        restoAdd();
    }else if (token_atual.ttoken==SUB){
        consome_token(SUB);
        mult();
        restoAdd();
    }
}

void mult(){
    uno();
    restoMult();
}

void restoMult(){
    if (token_atual.ttoken==MULT){
        consome_token(MULT);
        uno();
    }else if (token_atual.ttoken==DIVI){
        consome_token(DIVI);
        uno();
    }else if (token_atual.ttoken==MOD){
        consome_token(MOD);
        uno();
    }
}

void uno(){
  if (token_atual.ttoken==SOMA){
      consome_token(SOMA);
      uno();
  }else if (token_atual.ttoken==SUB){
      consome_token(SUB);
      uno();
  }else{
      fator();
  }
}

void fator(){
  if (token_atual.ttoken==NUMint){
      consome_token(NUMint);
  }else if (token_atual.ttoken==NUMfloat){
      consome_token(NUMfloat);
  }else if (token_atual.ttoken==IDENT){
      consome_token(IDENT);
  }else{
      consome_token(ABRIPAR);
      atrib();
      consome_token(FECHAPAR);
  }
}

char *decod_Token(TToken token){
      char* aux = malloc(sizeof(char)*16);
      switch (token) {
        case 1:
            strcpy(aux,"Abri Parentese");
        break;
        case 2:
            strcpy(aux,"Fecha Parentese");
        break;
        case 3:
            strcpy(aux,"Virgula");
        break;
        case 4:
            strcpy(aux,"Ponto e Virgula");
        break;
        case 5:
            strcpy(aux,"Final de Arquivo");
        break;
        case 6:
            strcpy(aux,"ERRO");
        break;
        case 7:
            strcpy(aux,"Identificador");
        break;
        case 8:
            strcpy(aux,"String");
        break;
        case 9:
            strcpy(aux,"Sinal de soma(+)");
        break;
        case 10:
            strcpy(aux,"Sinal de subtração (-)");
        break;
        case 11:
            strcpy(aux,"Sinal de Divisão (/)");
        break;
        case 12:
            strcpy(aux,"Atribuição (=)");
        break;
        case 13:
            strcpy(aux,"Sinal de Multiplicação (*)");
        break;
        case 14:
            strcpy(aux,"Igual (==)");
        break;
        case 15:
            strcpy(aux,"Modulo (%)");
        break;
        case 16:
            strcpy(aux,"PRINT");
        break;
        case 17:
            strcpy(aux,"SCAN");
        break;
        case 18:
            strcpy(aux,"&&");
        break;
        case 19:
            strcpy(aux,"Abri chaves");
        break;
        case 20:
            strcpy(aux,"Fecha chaves");
        break;
        case 21:
            strcpy(aux,"Declaração de INT");
        break;
        case 22:
            strcpy(aux,"Declaração de FLOAT");
        break;
        case 23:
            strcpy(aux,"BREAK");
        break;
        case 24:
            strcpy(aux,"CONTINUE");
        break;
        case 25:
            strcpy(aux,"FOR");
        break;
        case 26:
            strcpy(aux,"Numero Inteiro");
        break;
        case 27:
            strcpy(aux,"Numero Float");
        break;
        case 28:
            strcpy(aux,"WHILE");
        break;
        case 29:
            strcpy(aux,"IF");
        break;
        case 30:
            strcpy(aux,"ELSE");
        break;
        case 31:
            strcpy(aux,"OR ( || )");
        break;
        case 32:
            strcpy(aux,"Not (!)");
        break;
        case 33:
            strcpy(aux,"Menor (<)");
        break;
        case 34:
            strcpy(aux,"Maior (>)");
        break;
        case 35:
            strcpy(aux,"Menor Igual (<=)");
        break;
        case 36:
            strcpy(aux,"Maior Igual (>=)");
        break;
        case 37:
            strcpy(aux,"Diferente (!=)");
        break;
      }
      return aux;
}

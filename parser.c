#include "parser.h"

char* consome_token(TToken consome){
    //  Validação do Token, processo do Lexima
    if (consome == token_atual.ttoken){
        char *lexema = malloc(sizeof(char)*32);
        strcpy(lexema, token_atual.lexema);
        token_atual = getToken();
        return lexema;
    }
    error(consome);
}

void error(TToken consome){
    printf("\nError de Compilação:  Linha %d, Coluna %d", token_atual.linha,token_atual.coluna);
    printf("\n\tEsperava \'%s\' Mas Foi Recebido \'%s\'\n\n", decod_Token(consome), token_atual.lexema);
    fclose(file_src);
    exit(0);
}

void parser(){
    rewind(file_src);
    token_atual = getToken(); //Inicio do Lexico
    function();
    consome_token(FOE);
}

void function(){
    t_valuereturns aux;
    type();
    consome_token(IDENT);
    consome_token(ABRIPAR);
    arglist();
    consome_token(FECHAPAR);
    aux = bloco();
    if (aux.listQuad){
      for(Quad *q=aux.listQuad;q;q=q->next){
          if (q->param1)
            printf("(%s", q->param1);
            else
                printf("olocoo\n");
          if (q->param2)
            printf(", %s", q->param2);
          if (q->param3)
            printf(", %s", q->param3);
          else{
            printf(")\n");
            continue;
            }
          if (q->param4)
            printf(", %s)\n", q->param4);
          else
            printf(")\n");
      }}else{
          printf("NOTHING\n");
      }
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

int type(){
    if (token_atual.ttoken == INT){
        consome_token(INT);
        return 0;
    }
    consome_token(FLOAT);
    return 1;
}

t_valuereturns bloco(){
    t_valuereturns aux;
    consome_token(ABRICHAV);
    aux = stmtList();
    consome_token(FECHACHAV);
    return aux;
}

t_valuereturns stmtList(){
    t_valuereturns aux, aux2;
    if (    (token_atual.ttoken == FOR)   ||(token_atual.ttoken==PRINT)   ||(token_atual.ttoken==SCAN)
          ||(token_atual.ttoken==WHILE)   ||(token_atual.ttoken==NOT)     ||(token_atual.ttoken==ABRIPAR)
          ||(token_atual.ttoken==SOMA)    ||(token_atual.ttoken==SUB)     ||(token_atual.ttoken==IDENT)
          ||(token_atual.ttoken==NUMint)  ||(token_atual.ttoken==NUMfloat)||(token_atual.ttoken==IF)
          ||(token_atual.ttoken==ABRICHAV)||(token_atual.ttoken==FLOAT)   ||(token_atual.ttoken==INT)
          ||(token_atual.ttoken==PONTVIRG)||(token_atual.ttoken==BREAK)   ||(token_atual.ttoken==CONTINUE)
          ||(token_atual.ttoken==RETURN)){
              aux  = stmt();
              aux2 = stmtList();
              aux.listQuad = addQuad(aux.listQuad,aux2.listQuad);
          }
    return aux;
}

t_valuereturns stmt(){
    t_valuereturns aux;
    aux.listQuad = NULL;
    if (token_atual.ttoken==FOR){
          aux = forStmt();
    }else if ((token_atual.ttoken==PRINT)||(token_atual.ttoken==SCAN)){
           aux = ioStmt();
    }else if (token_atual.ttoken==WHILE){
          aux = whileStmt();
    }else if ((token_atual.ttoken==NOT)      ||(token_atual.ttoken==ABRIPAR)
              ||(token_atual.ttoken==SOMA)   ||(token_atual.ttoken==SUB) ||(token_atual.ttoken==IDENT)
              ||(token_atual.ttoken==NUMint) ||(token_atual.ttoken==NUMfloat)
             ){
          aux = expr();
          consome_token(PONTVIRG);
    }else if (token_atual.ttoken==IF){
          aux = ifStmt();
    }else if (token_atual.ttoken==ABRICHAV){
          aux = bloco();
    }else if ((token_atual.ttoken==FLOAT)||(token_atual.ttoken==INT)){
          declaration();
    }else if (token_atual.ttoken==CONTINUE){
          consome_token(CONTINUE);
          Quad *q1     = genQuad((char*)"CALL",(char*)"CONTINUE",NULL,NULL);
          aux.listQuad = addQuad(aux.listQuad, q1);
          consome_token(PONTVIRG);
    }else if (token_atual.ttoken==BREAK){
          consome_token(BREAK);
          Quad *q1  = genQuad((char*)"CALL",(char*)"BREAK",NULL,NULL);
          aux.listQuad = addQuad(aux.listQuad, q1);
          consome_token(PONTVIRG);
    }else if (token_atual.ttoken==RETURN){
          consome_token(RETURN);
          Quad *q1  = genQuad((char*)"CALL",(char*)"RETURN",NULL,NULL);
          aux.listQuad = addQuad(aux.listQuad, q1);
          consome_token(PONTVIRG);
    }else{
          consome_token(PONTVIRG);
    }
    return aux;
}

void declaration(){
    int vartype     = type();
    int numvarantes = ((lenVariables-1)>=0) ? lenVariables : 0;
    identList(vartype);
    consome_token(PONTVIRG);

}

void identList(int vartype){
    int coluna = token_atual.coluna;
    char *var  = consome_token(IDENT);
    if (lenVariables == 0){
        listVariables = malloc(sizeof(t_variable));
        lenVariables  = 1;
        strcpy(listVariables[0].id_var,var);
    }else{
        for (int i=0; i<lenVariables;i++)
            if (strcmp(var,listVariables[i].id_var)==0){
                fprintf(stderr, "\nError de Compilação: Linha %d, Coluna %d\n\tMúltipla Declaração de Variavel,  Variavel = \'%s\'\n\n",token_atual.linha, coluna, var);
                fclose(file_src);
                exit(3);
            }
        listVariables= realloc(listVariables,sizeof(t_variable)*(++(lenVariables)));
        strcpy(listVariables[(lenVariables)-1].id_var,var);
    }
    restoIdentList(vartype);

}

void restoIdentList(int vartype){
    if (token_atual.ttoken==VIRG){
        consome_token(VIRG);
        int coluna = token_atual.coluna;
        char *var = consome_token(IDENT);
        for (int i=0; i<lenVariables;i++)
            if (strcmp(var,listVariables[i].id_var)==0){
                fprintf(stderr, "\nError de Compilação: Linha %d, Coluna %d\n\tMúltipla Declaração de Variavel,  Variavel = \'%s\'\n\n",token_atual.linha, coluna, var);
                fclose(file_src);
                exit(3);
        }
        listVariables= realloc(listVariables ,sizeof(t_variable)*(++(lenVariables)));
        strcpy(listVariables[(lenVariables)-1].id_var,var);
        restoIdentList(vartype);
    }
}

t_valuereturns forStmt(){
    t_valuereturns aux, aux2, aux3, aux4;
    consome_token(FOR);
    consome_token(ABRIPAR);
    aux = optExpr();
    consome_token(PONTVIRG);
    aux2 = optExpr();
    consome_token(PONTVIRG);
    aux3 = optExpr();
    consome_token(FECHAPAR);
    aux4 = stmt();
    aux.listQuad    = addQuad(aux.listQuad, aux2.listQuad);
    char *labReturn = genLabel();
    char *labExit   = genLabel();
    Quad *q1        = genQuad((char*)"IF",aux2.NameResult,labReturn,labExit);
    Quad *q1_5      = genQuad((char*)"IF",aux2.NameResult,labReturn,labExit);
    Quad *q2        = genQuad((char*)"LABEL",labReturn,NULL,NULL);
    Quad *q3        = genQuad((char*)"LABEL",labExit,NULL,NULL);
    aux.listQuad    = addQuad(aux.listQuad, q1);
    aux.listQuad    = addQuad(aux.listQuad, q2);
    aux.listQuad    = addQuad(aux.listQuad, aux4.listQuad);
    aux.listQuad    = addQuad(aux.listQuad, aux3.listQuad);
    aux.listQuad    = addQuad(aux.listQuad, q1_5);
    aux.listQuad    = addQuad(aux.listQuad, q3);
    return aux;
}

t_valuereturns optExpr(){
    t_valuereturns aux;
    if ((token_atual.ttoken==NOT)          ||(token_atual.ttoken==ABRIPAR)
            ||(token_atual.ttoken==SOMA)   ||(token_atual.ttoken==SUB) ||(token_atual.ttoken==IDENT)
            ||(token_atual.ttoken==NUMint) ||(token_atual.ttoken==NUMfloat)){
              aux = expr();
    }
    return aux;
}

t_valuereturns ioStmt(){
    t_valuereturns aux;
    if (token_atual.ttoken==SCAN){
        consome_token(SCAN);
        consome_token(ABRIPAR);
        char *str = consome_token(STR);
        consome_token(VIRG);
        char *id = consome_token(IDENT);
        Quad *q1 = genQuad((char*)"CALL","SACN",str,id);
        aux.listQuad = addQuad(aux.listQuad, q1);
        consome_token(FECHAPAR);
        consome_token(PONTVIRG);
    }else{
        consome_token(PRINT);
        consome_token(ABRIPAR);
        aux = outList();
        // Quad *q1 = genQuad((char*)"CALL","PRINT",str,id);
        // aux.listQuad = addQuad(aux.listQuad, q1);
        consome_token(FECHAPAR);
        consome_token(PONTVIRG);
    }
    return aux;
}

t_valuereturns outList(){
    t_valuereturns aux, aux2;
    aux  = out();
    aux2 = restOutList();
}

t_valuereturns out(){
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

t_valuereturns restOutList(){
    t_valuereturns aux, aux2;
    aux.listQuad = NULL;
    if (token_atual.ttoken==VIRG){
        consome_token(VIRG);
        aux = out();
        aux = restOutList();
    }
    return aux;
}

t_valuereturns whileStmt(){
    t_valuereturns aux, aux2;
    consome_token(WHILE);
    consome_token(ABRIPAR);
    aux  = expr();
    consome_token(FECHAPAR);
    aux2 = stmt();
    char *labReturn = genLabel();
    char *labExit   = genLabel();
    Quad *q1        = genQuad((char*)"WHILE",aux.NameResult,labReturn,labExit);
    Quad *q1_5      = genQuad((char*)"WHILE",aux.NameResult,labReturn,labExit);
    Quad *q2        = genQuad((char*)"LABEL",labReturn,NULL,NULL);
    Quad *q3        = genQuad((char*)"LABEL",labExit,NULL,NULL);
    aux.listQuad    = addQuad(aux.listQuad, q1);
    aux.listQuad    = addQuad(aux.listQuad, q2);
    aux.listQuad    = addQuad(aux.listQuad, aux2.listQuad);
    aux.listQuad    = addQuad(aux.listQuad, q1_5);
    aux.listQuad    = addQuad(aux.listQuad, q3);
    return aux;
}

t_valuereturns ifStmt(){
    t_valuereturns aux, aux2, aux3;
    consome_token(IF);
    consome_token(ABRIPAR);
    char *labTrue  = genLabel();
    char *labFalse = genLabel();
    aux = expr();
    Quad *q1     = genQuad((char*)"IF",aux.NameResult,labTrue,labFalse);
    aux.listQuad = addQuad(aux.listQuad, q1);
    consome_token(FECHAPAR);
    Quad *q2     = genQuad((char*)"LABEL",labTrue,NULL,NULL);
    aux.listQuad = addQuad(aux.listQuad, q2);
    aux2 = stmt();
    aux.listQuad = addQuad(aux.listQuad, aux2.listQuad);
    aux3 = elsePart();
    Quad *q4 = genQuad((char*)"LABEL",labFalse,NULL,NULL);
    if (aux3.listQuad){
        char *labExit  = genLabel();
        Quad *q3       = genQuad((char*)"JUMP",labExit,NULL,NULL);
        Quad *q5       = genQuad((char*)"LABEL",labExit,NULL,NULL);
        aux.listQuad   = addQuad(aux.listQuad, q3);
        aux.listQuad   = addQuad(aux.listQuad, q4);
        aux.listQuad   = addQuad(aux.listQuad, aux3.listQuad);
        aux.listQuad   = addQuad(aux.listQuad, q5);
        aux.NameResult = aux3.NameResult;
    }else{
        aux.NameResult = aux2.NameResult;
        aux.listQuad   = addQuad(aux.listQuad, q4);
    }
    return aux;
}

t_valuereturns elsePart(){
    t_valuereturns aux;
    aux.listQuad = NULL;
    if (token_atual.ttoken==ELSE){
        consome_token(ELSE);
        aux = stmt();
    }
    return aux;
}

t_valuereturns expr(){
    t_valuereturns aux;
    aux = atrib();
    return aux;
}

t_valuereturns atrib(){
    t_valuereturns aux, aux2;
    aux  = or();
    aux2 = restoAtrib(aux.NameResult);
    // printf("%d = %d\n", aux.bool_leftValue, aux2.bool_leftValue);
    if (!((aux.bool_leftValue)||(aux2.bool_leftValue))){
        fprintf(stderr, "\nErro de Atribuição de Variavel, linha %d coluna %d\n\n",
                token_atual.linha, token_atual.coluna);
        fclose(file_src);
        exit(3);
    }
    aux.listQuad   = addQuad(aux.listQuad, aux2.listQuad);
    aux.NameResult = aux2.NameResult;
    return aux;
}

t_valuereturns restoAtrib(char *parametro){
    t_valuereturns aux;
    aux.listQuad = NULL;
    if (token_atual.ttoken==ATRIB){
        consome_token(ATRIB);
        aux = atrib();
        Quad *q1 = genQuad((char*)"=",parametro,parametro,aux.NameResult);
        aux.listQuad = addQuad(aux.listQuad,q1);
    }else{
        aux.bool_leftValue = 1;
        aux.NameResult = parametro;
    }
    return aux;
}

t_valuereturns or(){
    t_valuereturns aux, aux2;
    aux  = and();
    aux2 = restoOr(aux.NameResult);
    aux.listQuad   = addQuad(aux.listQuad, aux2.listQuad);
    aux.NameResult = aux2.NameResult;
    aux.bool_leftValue &= aux2.bool_leftValue;
    return aux;
}

t_valuereturns restoOr(char *parametro){
    t_valuereturns aux, aux2;
    aux.listQuad = NULL;
    if (token_atual.ttoken==OR){
        consome_token(OR);
        aux      = and();
        aux2     = restoOr(aux.NameResult);
        Quad *q1       = genQuad((char*)"||",parametro,parametro,aux.NameResult);
        aux.listQuad   = addQuad(aux.listQuad,q1);
        aux.listQuad   = addQuad(aux.listQuad,aux2.listQuad);
        aux.NameResult = aux2.NameResult;
    }else{
        aux.bool_leftValue = 1;
        aux.NameResult     = parametro;
    }
    return aux;
}

t_valuereturns and(){
    t_valuereturns aux, aux2;
    aux  = not();
    aux2 = restoAnd(aux.NameResult);
    aux.listQuad   = addQuad(aux.listQuad, aux2.listQuad);
    aux.NameResult = aux2.NameResult;
    aux.bool_leftValue &= aux2.bool_leftValue;
    return aux;
}

t_valuereturns restoAnd(char *parametro){
    t_valuereturns aux, aux2;
    aux.listQuad = NULL;
    if (token_atual.ttoken==AND){
        consome_token(AND);
        aux  = not();
        aux2 = restoAnd(aux.NameResult);
        Quad *q1       = genQuad((char*)"&&",parametro,parametro,aux.NameResult);
        aux.listQuad   = addQuad(aux.listQuad,q1);
        aux.listQuad   = addQuad(aux.listQuad,aux2.listQuad);
        aux.NameResult = aux2.NameResult;
    }else{
        aux.bool_leftValue = 1;
        aux.NameResult = parametro;
    }
    return aux;
}

t_valuereturns not(){
    t_valuereturns aux;
    if (token_atual.ttoken==NOT){
        consome_token(NOT);
        aux = not();
        char *temp     = genTemp();
        Quad *q1       = genQuad((char*)"!",temp,aux.NameResult,NULL);
        aux.listQuad   = addQuad(aux.listQuad,q1);
        aux.NameResult = temp;
    }else{
        aux = rel(); // nao muda
    }
    return aux;
}

t_valuereturns rel(){
   t_valuereturns aux, aux2;
    aux  = add();
    aux2 = restorel(aux.NameResult);
    aux.listQuad   = addQuad(aux.listQuad, aux2.listQuad);
    aux.NameResult = aux2.NameResult;
    aux.bool_leftValue &= aux2.bool_leftValue;
    return aux;
}

t_valuereturns restorel(char *parametro){
    t_valuereturns aux;
    aux.listQuad = NULL;
    if (token_atual.ttoken==IGUAL){
        consome_token(IGUAL);
        aux = add();
        Quad *q1       = genQuad((char*)"==",parametro,parametro,aux.NameResult);
        aux.listQuad   = addQuad(aux.listQuad,q1);
        aux.bool_leftValue = 0;
    }else if (token_atual.ttoken==NIGUAL){
        consome_token(NIGUAL);
        aux = add();
        Quad *q1       = genQuad((char*)"!=",parametro,parametro,aux.NameResult);
        aux.listQuad   = addQuad(aux.listQuad,q1);
        aux.bool_leftValue = 0;
    }else if (token_atual.ttoken==MENOR){
        consome_token(MENOR);
        aux = add();
        Quad *q1       = genQuad((char*)"<",parametro,parametro,aux.NameResult);
        aux.listQuad   = addQuad(aux.listQuad,q1);
        aux.bool_leftValue = 0;
    }else if (token_atual.ttoken==MENORIGUAL){
        consome_token(MENORIGUAL);
        aux = add();
        Quad *q1       = genQuad((char*)"<=",parametro,parametro,aux.NameResult);
        aux.listQuad   = addQuad(aux.listQuad,q1);
        aux.bool_leftValue = 0;
    }else if (token_atual.ttoken==MAIOR){
        consome_token(MAIOR);
        aux = add();
        Quad *q1       = genQuad((char*)">",parametro,parametro,aux.NameResult);
        aux.listQuad   = addQuad(aux.listQuad,q1);
        aux.bool_leftValue = 0;
    }else if (token_atual.ttoken==MAIORIGUAL){
        consome_token(MAIORIGUAL);
        aux = add();
        Quad *q1       = genQuad((char*)">=",parametro,parametro,aux.NameResult);
        aux.listQuad   = addQuad(aux.listQuad,q1);
        aux.bool_leftValue = 0;
    }else{
        aux.bool_leftValue = 1;
    }
    aux.NameResult = parametro;
    return aux;
}

t_valuereturns add(){
    t_valuereturns aux, aux2;
    aux  = mult();
    aux2 = restoAdd(aux.NameResult);
    aux.listQuad   = addQuad(aux.listQuad,aux2.listQuad);
    aux.NameResult = aux2.NameResult;
    aux.bool_leftValue &= aux2.bool_leftValue;
    return aux;
}

t_valuereturns restoAdd(char* parametro){
    t_valuereturns aux,aux2;
    aux.listQuad = NULL;
    if (token_atual.ttoken==SOMA){
        consome_token(SOMA);
        aux  = mult();
        aux2 = restoAdd(parametro); // WALACE
        Quad *q1 = genQuad((char*)"+",parametro,parametro,aux.NameResult);
        aux.listQuad   = addQuad(aux.listQuad,q1);
        aux.listQuad   = addQuad(aux.listQuad,aux2.listQuad);
        aux.NameResult = aux2.NameResult;
        aux.bool_leftValue = 0;
    }else if (token_atual.ttoken==SUB){
        consome_token(SUB);
        aux  = mult();
        aux2 = restoAdd(aux.NameResult); // WALACE
        Quad *q1       = genQuad((char*)"-",parametro,parametro,aux.NameResult);
        aux.listQuad   = addQuad(aux.listQuad,q1);
        aux.listQuad   = addQuad(aux.listQuad,aux2.listQuad);
        aux.NameResult = aux2.NameResult;
        aux.bool_leftValue = 0;
    }else{
        aux.bool_leftValue = 1;
        aux.NameResult     = parametro;
    }
    return  aux;
}

t_valuereturns mult(){
    t_valuereturns aux, aux2;
    aux  = uno();
    // printf("%s\n", aux.NameResult);
    aux2 = restoMult(aux.NameResult);
    aux.listQuad   = addQuad(aux.listQuad,aux2.listQuad);
    aux.NameResult = aux2.NameResult;
    aux.bool_leftValue &= aux2.bool_leftValue;
    return aux;
}

t_valuereturns restoMult(char *parametro){
    t_valuereturns aux;
    aux.listQuad = NULL;
    // aux.bool_leftValue = 0;
    if (token_atual.ttoken==MULT){
        consome_token(MULT);
        aux      = uno();
        Quad *q1 = genQuad((char*)"*",parametro,parametro,aux.NameResult);
        aux.listQuad       = addQuad(aux.listQuad,q1);
        aux.bool_leftValue = 0;
    }else if (token_atual.ttoken==DIVI){
        consome_token(DIVI);
        aux = uno();
        Quad *q1     = genQuad((char*)"/",parametro,parametro,aux.NameResult);
        aux.listQuad = addQuad(aux.listQuad,q1);
        aux.bool_leftValue = 0;
    }else if (token_atual.ttoken==MOD){
        consome_token(MOD);
        aux      = uno();
        Quad *q1 = genQuad((char*)"%",parametro,parametro,aux.NameResult);
        aux.listQuad = addQuad(aux.listQuad,q1);
        aux.bool_leftValue = 0;
    }else{
        aux.bool_leftValue = 1;
    }
    aux.NameResult = parametro; // WALACE
    return aux;
}

t_valuereturns uno(){
  t_valuereturns aux;
  if (token_atual.ttoken==SOMA){
      consome_token(SOMA);
      aux = uno();
      aux.bool_leftValue = 0;
  }else if (token_atual.ttoken==SUB){
      consome_token(SUB);
      aux      = uno();
      Quad *q1 = genQuad((char*)"-",aux.NameResult,"0",aux.NameResult);
      aux.listQuad = addQuad(aux.listQuad,q1);
      aux.bool_leftValue = 0;
  }else{
      aux = fator();
  }
  return aux;
}

t_valuereturns fator(){
  t_valuereturns aux;
  if (token_atual.ttoken==ABRIPAR){
      consome_token(ABRIPAR);
      aux = atrib();
      consome_token(FECHAPAR);
      aux.bool_leftValue = 0;
  }else if (token_atual.ttoken==NUMfloat){
      char *temp   = genTemp();
      char *lexema = consome_token(NUMfloat);
      Quad *q1     = genQuad((char*)"=",temp,lexema,NULL);
      aux.listQuad = addQuad(aux.listQuad,q1);
      aux.NameResult     = temp;
      aux.bool_leftValue = 0;
  }else if (token_atual.ttoken==IDENT){
      char *lexema = consome_token(IDENT);
      int flag  = 1;
      for (int i=0;i<lenVariables;i++){
          if (strcmp(lexema,listVariables[i].id_var)==0){
              flag = 0;
              break;
          }
      }
      if (flag){
          fprintf(stderr, "\nError de Compilação: Linha %d, Coluna %d\n\tAtribuição A Uma Variavel Não Declarada,  Variavel = \'%s\'\n\n",token_atual.linha, token_atual.coluna, lexema);
          fclose(file_src);
          exit(3);
      }
      char *temp     = genTemp();
      Quad *q1       = genQuad((char*)"var",temp,lexema,NULL);
      aux.listQuad   = addQuad(aux.listQuad,q1);
      aux.NameResult = temp;
      // return 1 se IDENT
      aux.bool_leftValue = 1;
  }else{
      char *lexema = consome_token(NUMint);
      char *temp   = genTemp();
      Quad *q1     = genQuad((char*)"=",temp,lexema,NULL);
      aux.listQuad = addQuad(aux.listQuad,q1);
      aux.NameResult     = temp;
      aux.bool_leftValue = 0;
  }
  return aux;
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
            strcpy(aux,"ERROR (Não interpretado)");
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
            strcpy(aux,"AND (&&)");
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

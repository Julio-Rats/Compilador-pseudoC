#include "virtualmachine.h"

u_int32_t    lenVariables  = 0;
t_variable  *listVariables = NULL;


u_int8_t* genLabel(){
      static u_int8_t inc = 0;
      u_int8_t   *aux   = malloc(sizeof(u_int8_t)*(strlen("_l")+7));
      sprintf(aux,"%s%d","_l",inc++);
      return aux;
}
u_int8_t* genTemp(){
      static u_int8_t inc = 0;
      u_int8_t   *aux   = malloc(sizeof(u_int8_t)*(strlen("_t")+7));
      sprintf(aux,"%s%d","_t",inc++);
      return aux;
}
Quad* genQuad(u_int8_t*param1,u_int8_t*param2,u_int8_t*param3,u_int8_t*param4){
      Quad *aux   = (Quad*) malloc(sizeof(Quad));
      aux->param1 = param1;
      aux->param2 = param2;
      aux->param3 = param3;
      aux->param4 = param4;
      aux->next   = NULL;
      return aux;
}
Quad* addQuad(Quad* destine, Quad* source){
      Quad *aux = destine;
      if (aux){
          while(aux->next){
              aux = aux->next;
          }
          if (source){
              aux->next = malloc(sizeof(Quad*));
              aux->next = source;
          }
          return destine;
      }
      return source;
}

Quad* copyQuad(Quad* list){
    Quad* aux3, *aux2, *aux = malloc(sizeof(Quad));
    aux2 = list;
    aux3 = aux;
    while(aux2){
        aux3->param1 = malloc(sizeof(u_int8_t)*6);
        strcpy(aux3->param1, aux2->param1);
        if (aux2->param2){
          aux3->param2 = malloc(sizeof(u_int8_t)*6);
          strcpy(aux3->param2, aux2->param2);
        }else{
          aux3->param2 = NULL;
        }
        if (aux2->param3){
          aux3->param3 = malloc(sizeof(u_int8_t)*256);
          strcpy(aux3->param3, aux2->param3);
        }else{
          aux3->param3 = NULL;
        }
        if (aux2->param4){
          aux3->param4 = malloc(sizeof(u_int8_t)*256);
          strcpy(aux3->param4, aux2->param4);
        }else{
          aux3->param4 = NULL;
        }
        aux3->next = NULL;
        aux2 = aux2->next;
        if (aux2){
          aux3->next = malloc(sizeof(Quad));
          aux3 = aux3->next;
        }
    }
    return aux;
}

void exec(Quad *lista){
    u_int8_t type, op;
    float    valor;
    u_int8_t     str[256];
    for(Quad *aux=lista;aux;aux=aux->next){
        op = decod_inst(aux->param1);
        switch (op) {
          case 0:
              if (strcmp(aux->param3, (u_int8_t*)"V")==0){
                  valor = getValue(aux->param2);
                  if (valor == 0){
                     add_var(aux->param2, 0, atoi(aux->param4));
                   }
                   continue;
              }
              type  = getType(aux->param2);
              valor = getValue(aux->param3);
              add_var(aux->param2, valor, type);
          break;

          case 1:
              valor = getValue(aux->param3) == getValue(aux->param4);
              type  = getType(aux->param2);
              add_var(aux->param2, valor, type);
          break;

          case 2:
              valor = getValue(aux->param3) > getValue(aux->param4);
              type  = getType(aux->param2);
              add_var(aux->param2, valor, type);
          break;

          case 3:
              valor = getValue(aux->param3) >= getValue(aux->param4);
              type  = getType(aux->param2);
              add_var(aux->param2, valor, type);
          break;

          case 4:
              valor = getValue(aux->param3) < getValue(aux->param4);
              type  = getType(aux->param2);
              add_var(aux->param2, valor, type);
          break;

          case 5:
              valor = getValue(aux->param3) <= getValue(aux->param4);
              type  = getType(aux->param2);
              add_var(aux->param2, valor, type);
          break;

          case 6:
              valor = getValue(aux->param3) != getValue(aux->param4);
              type  = getType(aux->param2);
              add_var(aux->param2, valor, type);
          break;

          case 7:
              valor = !getValue(aux->param3);
              type  = getType(aux->param2);
              add_var(aux->param2, valor, type);
          break;

          case 8:
              valor = getValue(aux->param3) && getValue(aux->param4);
              type  = getType(aux->param2);
              add_var(aux->param2, valor, type);
          break;

          case 9:
              valor = getValue(aux->param3) || getValue(aux->param4);
              type  = getType(aux->param2);
              add_var(aux->param2, valor, type);
          break;

          case 10:
              if (getValue(aux->param2)){
                  aux = getLabel(lista, aux->param3);
              }else{
                  aux = getLabel(lista, aux->param4);
              }
          break;

          case 11:
              aux = getLabel(lista, aux->param2);
          break;

          case 12:
              type = decod_inst(aux->param2);
              sprintf(str, aux->param3);
              if (type == 13){
                   if (str[0] == '\"'){
                      strcpy(str, removeaspas(aux->param3));
                      strcpy(str, interpretaStr(str));
                      printf("%s", str);
                   }else if (str[0] == '_'){
                        type = getType(aux->param3);
                        if (type == 0)
                            printf("%.f",  getValue(aux->param3));
                        else
                            printf("%.2f", getValue(aux->param3));
                   }else{
                      printf("%.2f", atof(str));
                   }
                   if (aux->next){
                     if (strcmp(aux->next->param1,(u_int8_t*)"CALL")==0){
                          if (strcmp(aux->next->param2,(u_int8_t*)"PRINT")!=0){
                              printf("\n");
                          }
                    }else{
                          printf("\n");
                    }
                  }else{
                      printf("\n");
                  }
              }else if (type == 14){
                  sprintf(str, aux->param3);
                  strcpy(str, removeaspas(aux->param3));
                  strcpy(str, interpretaStr(str));
                  printf("%s", str);
                  scanf("%f", &valor);
                  type  = getType(aux->param4);
                  add_var(aux->param4, valor, type);
              }else if (type == 20){
                  printf("\nFinalizado: retorno %.f\n",trunc(getValue(aux->param3)));
                  return;
              }
              fflush(stdout);
          break;

          case 15:
              valor = getValue(aux->param3)+getValue(aux->param4);
              type  = getType(aux->param2);
              add_var(aux->param2, valor, type);
          break;

          case 16:
              valor = getValue(aux->param3)-getValue(aux->param4);
              type  = getType(aux->param2);
              add_var(aux->param2, valor, type);
          break;
          case 17:
              valor = getValue(aux->param3)*getValue(aux->param4);
              type  = getType(aux->param2);
              add_var(aux->param2, valor, type);
          break;
          case 18:
              if (getValue(aux->param4)==0){
                  fprintf(stderr, "\nERROR TEMPO DE EXECUÇÃO: Divisão por zero impossivel\n\n");
                  exit(12);
              }
              valor = getValue(aux->param3)/getValue(aux->param4);
              type  = getType(aux->param2);
              add_var(aux->param2, valor, type);
          break;
          case 19:
              valor = (u_int8_t)getValue(aux->param3) % (u_int8_t)getValue(aux->param4);
              type  = getType(aux->param2);
              add_var(aux->param2, valor, type);
          break;
        }
    }
    printf("\nFinalizado: sem retorno\n");
    return;
}

int8_t decod_inst(u_int8_t *opcode){
    if (strcmp(opcode, "=")==0){
          return 0;
    }else if (strcmp(opcode, "==")==0){
          return 1;
    }else if (strcmp(opcode, ">")==0){
          return 2;
    }else if (strcmp(opcode, ">=")==0){
          return 3;
    }else if (strcmp(opcode, "<")==0){
          return 4;
    }else if (strcmp(opcode, "<=")==0){
          return 5;
    }else if (strcmp(opcode, "!=")==0){
          return 6;
    }else if (strcmp(opcode, "!")==0){
          return 7;
    }else if (strcmp(opcode, "&&")==0){
          return 8;
    }else if (strcmp(opcode, "||")==0){
          return 9;
    }else if (strcmp(opcode, "IF")==0){
          return 10;
    }else if (strcmp(opcode, "JUMP")==0){
          return 11;
    }else if (strcmp(opcode, "CALL")==0){
          return 12;
    }else if (strcmp(opcode, "PRINT")==0){
          return 13;
    }else if (strcmp(opcode, "SCAN")==0){
          return 14;
    }else if (strcmp(opcode, "+")==0){
          return 15;
    }else if (strcmp(opcode, "-")==0){
          return 16;
    }else if (strcmp(opcode, "*")==0){
          return 17;
    }else if (strcmp(opcode, "/")==0){
          return 18;
    }else if (strcmp(opcode, "%")==0){
          return 19;
    }else if (strcmp(opcode, "RETURN")==0){
          return 20;
    }
    return -1;
}

void add_var(u_int8_t *id, float value,  u_int8_t type){
    if (lenVarambiente == 0){
        listVarambiente = malloc(sizeof(t_varambiente));
        lenVarambiente  = 1;
        listVarambiente[0].id_var = id;
        if (type == 0){
            listVarambiente[0].value_numeric = trunc(value);
            listVarambiente[0].type = 0;
        }else if (type == 1){
            listVarambiente[0].value_numeric = value;
              listVarambiente[0].type = 1;
        }
        return;
    }
    for(u_int8_t i=0;i<lenVarambiente;i++)
        if (strcmp(listVarambiente[i].id_var, id)==0){
          if (type == 0){
              listVarambiente[i].value_numeric = trunc(value);
              listVarambiente[i].type = 0;
          }else if (type == 1){
              listVarambiente[i].value_numeric = value;
              listVarambiente[i].type = 1;
          }
          return;
        }

    listVarambiente = realloc(listVarambiente, sizeof(t_varambiente)*(++lenVarambiente));
    listVarambiente[(lenVarambiente)-1].id_var = id;
    listVarambiente[(lenVarambiente)-1].type   = type;

    if (type == 0){
        listVarambiente[(lenVarambiente)-1].value_numeric = trunc(value);
    }else if (type == 1){
        listVarambiente[(lenVarambiente)-1].value_numeric = value;
    }

}

u_int8_t getType(u_int8_t *lexema){
    for(u_int8_t i=0;i<lenVarambiente;i++){
        if (strcmp(lexema, listVarambiente[i].id_var)==0){
          return listVarambiente[i].type;
        }
    }
    return 1;
}

float getValue(u_int8_t *lexema){
    for(u_int32_t i=0;i<lenVarambiente;i++){
        if (strcmp(lexema, listVarambiente[i].id_var)==0){
            return listVarambiente[i].value_numeric;
        }
    }
    return atof(lexema);
}

Quad* getLabel(Quad* list, u_int8_t* lexema){
    Quad *aux = list;
    while(aux){
      if (strcmp((u_int8_t*)"LABEL", aux->param1)==0)
         if (strcmp(lexema, aux->param2)==0)
            return aux;
      aux = aux->next;
    }
    return NULL;
}

u_int8_t* removeaspas(u_int8_t* str){
      u_int8_t len = strlen(str);
      u_int8_t* aux = malloc(sizeof(u_int8_t)*len-1);
      for(u_int8_t i=0;i<len-2;i++){
          aux[i] = str[i+1];
      }
      aux[len-2] = '\0';
      return aux;
}

u_int8_t* interpretaStr(u_int8_t* str){
      u_int8_t len   = strlen(str);
      u_int8_t* aux = malloc(sizeof(u_int8_t)*len);
       u_int8_t indice = 0;
      for(u_int8_t i=0;i<len;i++){
        if((str[i]=='\\')){
            switch (str[i+1]) {
              case 'n':
                  aux[indice] = '\0';
                  sprintf(aux,"%s\n",aux);
                  indice++;
                  i+=1;
                  continue;
              break;
              case 't':
                  aux[indice] = '\0';
                  sprintf(aux,"%s\t",aux);
                  indice++;
                  i++;
                  continue;
              break;
              default:
                  aux[indice++] = str[i];
                  continue;
              break;
            }
        }
        aux[indice++] = str[i];
     }
    aux[indice] = '\0';
    return aux;
}

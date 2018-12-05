#include "virtualmachine.h"

unsigned int lenVariables  = 0;
t_variable  *listVariables = NULL;


char* genLabel(){
      static unsigned short int inc = 0;
      char   *aux   = malloc(sizeof(char)*(strlen("_label")+6));
      sprintf(aux,"%s%d","_l",inc++);
      return aux;
}
char* genTemp(){
      static unsigned short int inc = 0;
      char   *aux   = malloc(sizeof(char)*(strlen("_temp")+6));
      sprintf(aux,"%s%d","_t",inc++);
      return aux;
}
Quad* genQuad(char*param1,char*param2,char*param3,char*param4){
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

void exec(){
    
}

#ifndef  _virtualmachine_
#define   _virtualmachine_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include<unistd.h>

typedef struct quad_t Quad;

struct quad_t{
      char *param1;
      char *param2;
      char *param3;
      char *param4;
      Quad *next;
};

typedef struct{
    char      *id_var;
    u_int8_t   nivel;
    u_int8_t   type:1;
}t_variable;

extern unsigned int  lenVariables;
extern t_variable   *listVariables;

typedef struct{
    char     *id_var;
    double    value_numeric;
    u_int8_t  type:2;
}t_varambiente;

unsigned int  lenVarambiente;
t_varambiente *listVarambiente;

char* genLabel();
char* genTemp ();
Quad* genQuad (char *param1, char *param2, char *param3, char *param4);
Quad* addQuad (Quad *destine, Quad *Source);
Quad* copyQuad(Quad* list);
int decod_inst(char *opcode);
void add_var(char *id, float value,  int type);
int getType(char *lexema);
float getValue(char *lexema);
Quad* getLabel(Quad* list, char* lexema);
char* removeaspas(char* str);
char* interpretaStr(char* str);

void exec();

#endif

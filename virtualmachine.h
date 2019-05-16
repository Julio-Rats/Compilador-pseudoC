#ifndef  _virtualmachine_
#define   _virtualmachine_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct quad_t Quad;

struct quad_t{
      char* param1;
      char* param2;
      char* param3;
      char* param4;
      Quad* next;
};

typedef struct{
    char*     id_var;
    u_int8_t  nivel;
    u_int8_t  type:1;
}t_variable;

extern u_int32_t   lenVariables;
extern t_variable *listVariables;

typedef struct{
    char*     id_var;
    double    value_numeric;
    u_int8_t  type:1;
}t_varambiente;

u_int32_t     lenVarambiente;
t_varambiente *listVarambiente;

void  add_var(char* id, double value,  u_int8_t type);
float  getValue(char* lexema);
Quad* copyQuad(Quad* list);
Quad* addQuad (Quad* destine,  Quad* Source);
Quad* getLabel(Quad* list, char* lexema);
Quad* genQuad (char* param1, char* param2, char* param3, char* param4);
char* genLabel();
char* genTemp ();
char* removeaspas  (char* str);
char* interpretaStr(char* str);
u_int8_t    getType(char* lexema);
int8_t    decod_inst (char* opcode);

void exec();

#endif

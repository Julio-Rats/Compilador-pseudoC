#ifndef  _virtualmachine_
#define   _virtualmachine_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct quad_t Quad;

struct quad_t{
      u_int8_t *param1;
      u_int8_t *param2;
      u_int8_t *param3;
      u_int8_t *param4;
      Quad     *next;
};

typedef struct{
    u_int8_t   *id_var;
    u_int8_t   nivel;
    u_int8_t   type:1;
}t_variable;

extern u_int32_t   lenVariables;
extern t_variable *listVariables;

typedef struct{
    u_int8_t  *id_var;
    double    value_numeric;
    u_int8_t  type:1;
}t_varambiente;

u_int32_t     lenVarambiente;
t_varambiente *listVarambiente;

void  add_var(u_int8_t *id, double value,  u_int8_t type);
float  getValue(u_int8_t *lexema);
Quad* copyQuad(Quad* list);
Quad* addQuad (Quad *destine,  Quad *Source);
Quad* getLabel(Quad* list, u_int8_t* lexema);
Quad* genQuad (u_int8_t *param1, u_int8_t *param2, u_int8_t *param3, u_int8_t *param4);
u_int8_t* genLabel();
u_int8_t* genTemp ();
u_int8_t* removeaspas  (u_int8_t* str);
u_int8_t* interpretaStr(u_int8_t* str);
u_int8_t    getType    (u_int8_t *lexema);
int8_t    decod_inst (u_int8_t *opcode);

void exec();

#endif

#ifndef  _virtualmachine_
#define  _virtualmachine_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct quad Quad;

struct quad{
      char *param1;
      char *param2;
      char *param3;
      char *param4;
      Quad *next;
};

typedef struct{
    char  *id_var;
    char  *temp;
}t_variable;

extern unsigned int lenVariables;
extern t_variable   *listVariables;

char* genLabel();
char* genTemp ();
Quad* genQuad(char *param1, char *param2, char *param3, char *param4);
Quad* addQuad (Quad *destine, Quad *Source);


#endif

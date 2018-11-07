#ifndef  _virtualmachine_
#define  _virtualmachine_

#include <stdlib.h>

typedef struct{
    char         *id_label;
    unsigned int  pos_label;
}t_label;

typedef struct{
    char  *id_var;
    int    type;
    float  value_var;
}t_variable;

extern unsigned int lenLabels;
extern unsigned int lenVariables;
extern t_label     *listLabels;
extern t_variable  *listVariables;


#endif

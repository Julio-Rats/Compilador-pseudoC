#ifndef LIST
#define  LIST

#include <stdio.h>
#include <stdlib.h>

typedef struct list t_list;

struct list{
    void   *DATA;
    t_list *NEXT;
};

void addList(t_list *list, void *DATA);
int  remList(t_list list, void *DATA);

#endif

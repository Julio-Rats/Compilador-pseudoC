#include "list.h"

void addList(t_list *list, void* DATA){
      // t_list aux = list;
      // if (!list){
          while ((list = malloc(sizeof(t_list)))<=0){printf("ola\n");}
          list->DATA = (int*) DATA;
          list->NEXT = NULL;
          printf("olaa %d\n", list->DATA);
          return;
      // }
      // while(aux){
      //     aux = aux->NEXT;
      // }
      // printf("ol %d\n", DATA);
      // addList(aux, DATA);
      // return;
}

int  remList(t_list list, void *DATA){

}

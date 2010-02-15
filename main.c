// Program to test FSM
#include "fsm.h"
#include<stdio.h>

void abc(struct fsm_object *obj, int val,void **arg)
{
    printf("%d\n",val);
    printf("%s\n",obj->fsm_cur_state_name);
    fsm_to_state(obj,"hello",0,NULL);
}

void xyz(struct fsm_object *obj, int val,void **arg)
{
    printf("%d\n",val);
    printf("%s\n",obj->fsm_cur_state_name);
    fsm_terminate(obj);
//    fsm_to_state("default",1,NULL);
}


int main()
{
    // initialise the FSM
    struct fsm_object obj;
    fsm_init(&obj);
    fsm_default(&obj,abc);
    fsm_add(&obj,"qwerty",xyz);
    fsm_add(&obj,"hello",xyz);
    fsm_remove(&obj,"qwerty");
    fsm_main(&obj);
    return 0;
}

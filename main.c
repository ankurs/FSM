// Program to test FSM
#include "fsm.h"
#include<stdio.h>

void abc(struct fsm_object *obj, int val,void **arg)
{
    // state -> default
    printf("%d\n",val);
    printf("%s\n",obj->fsm_cur_state_name);
    fsm_to_state(obj,"hello",0,NULL);
}

void pqr(struct fsm_object *obj, int val,void **arg)
{
    // state -> qwerty
    printf("%d\n",val);
    printf("%s\n",obj->fsm_cur_state_name);
    fsm_to_state(obj,"default",0,NULL);
}


void xyz(struct fsm_object *obj, int val,void **arg)
{
    // state -> hello
    printf("%d\n",val);
    printf("%s\n",obj->fsm_cur_state_name);
//    fsm_terminate(obj);
    fsm_to_state(obj,"qwerty",0,NULL);
}


int main()
{
    // initialise the FSM
    struct fsm_object obj;
    fsm_init(&obj);
    fsm_default(&obj,abc);
    fsm_add(&obj,"qwerty",pqr);
    fsm_add(&obj,"hello",xyz);
    //fsm_remove(&obj,"qwerty");
    fsm_main(&obj);
    return 0;
}

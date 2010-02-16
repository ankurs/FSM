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
//  fsm_terminate(obj);
    fsm_to_state(obj,"qwerty",0,NULL);
}


int main()
{
    // create FSM object
    struct fsm_object obj;
    // initialize it
    fsm_init(&obj);
    // set default function
    fsm_default(&obj,abc);
    // add moe states
    fsm_add(&obj,"qwerty",pqr);
    fsm_add(&obj,"hello",xyz);
    // starte the main FSM loop
    fsm_main(&obj);
    return 0;
}

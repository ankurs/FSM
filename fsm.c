/**
 * @file fsm.c
 * @brief an implementation for a FSM in C, this file contains 
 * implementation of definations.
 * @author Ankur Shrivastava
 */

#include "fsm.h"
#include<stdlib.h>
#include<string.h>

/**
 * Function to initialize the FSM
 * @param obj pointer to structure of type fsm_object, which defines the FSM
 */
int fsm_init(struct fsm_object *obj)
{
    //initialize everything to Null or 0
    obj->fsm_base = NULL;
    obj->fsm_cur_state_name = NULL;
    obj->fsm_arg_num = 0;
    obj->fsm_arg_value = NULL;
    return 0;
}

/**
 * The FSM entry point, this is where execution of code begins in FSM.
 * @param obj pointer to structure of type fsm_object, which defines the FSM
 */
int fsm_main(struct fsm_object *obj)
{
    struct fsm_state *tmp;
    while (1)
    {
        tmp = obj->fsm_base;
        if ((obj->fsm_base==NULL)||(obj->fsm_cur_state_name==NULL))
        {        
            return -1;
        }
        while ((tmp->name != obj->fsm_cur_state_name)&&(tmp!=NULL))
            tmp = tmp->next;
        if (tmp == NULL)
            return -1;
        tmp->function(obj,obj->fsm_arg_num,obj->fsm_arg_value);
    }
    return 0;
}

/**
 * Function to add a new state to the FSM.
 * @param obj pointer to structure of type fsm_object, which defines the FSM
 * @param state name of the state to be added.
 * @param fun name of the function to be executed for this state
 */
int fsm_add(struct fsm_object *obj, char *state, void (*fun)(struct fsm_object *, int ,void **) )
{
    struct fsm_state *tmp = obj->fsm_base;
    struct fsm_state *new_state = malloc(sizeof(struct fsm_state));
    while(tmp->next)
        tmp = tmp->next;
    new_state->name = state;
    new_state->function = fun;
    new_state->next=NULL;
    tmp->next=new_state;
    return 0;
}

/**
 * Function to remove a state from the FSM.
 * @param state name of state to be removed
 * @param obj pointer to structure of type fsm_object, which defines the FSM
 */
int fsm_remove(struct fsm_object *obj,char *state)
{
    if (!strcmp(state,"default"))
        return -1;
    struct fsm_state *to_del;
    struct fsm_state *tmp=obj->fsm_base;
    while((tmp->next!=NULL)&&(strcmp(tmp->next->name,state)))
        tmp=tmp->next;
    if (tmp == NULL)
        return -1;
    to_del = tmp->next;
    tmp->next = tmp->next->next;
    free(to_del);
    return 0;
}

/**
 * Function to change state.
 * @details changes state to the new specified state, if the state does not exist returns error,
 * state change is not triggered till function calling fsm_to_state returns
 * @param obj pointer to structure of type fsm_object, which defines the FSM
 * @param state name of state to chnage to
 * @param num number of arguments
 * @param arg arguments
 */
int fsm_to_state(struct fsm_object *obj, char *state, int num, void** arg)
{
    struct fsm_state *tmp=obj->fsm_base;
    while((tmp!=NULL)&&(strcmp(tmp->name,state)))
        tmp=tmp->next;
    if (tmp == NULL)
        return -1;
    obj->fsm_cur_state = tmp;
    obj->fsm_cur_state_name = tmp->name;
    obj->fsm_arg_num = num;
    obj->fsm_arg_value=arg;
    return 0;
}

/**
 * Function to add a default state to FSM.
 * @details Adds a default state to FSM, this is the function called at the start of the FSM
 * or in case of error, with the appropriate error code
 * @param obj pointer to structure of type fsm_object, which defines the FSM
 * @param fun name of the function to be executed for this state
 */
int fsm_default(struct fsm_object *obj, void (*fun)(struct fsm_object *, int ,void **) )
{
    obj->fsm_base = malloc(sizeof(struct fsm_state));
    obj->fsm_base->name="default";
    obj->fsm_base->function = fun;
    obj->fsm_base->next = NULL;
    // set current state to default
    obj->fsm_cur_state = obj->fsm_base;
    obj->fsm_cur_state_name = obj->fsm_base->name;
    return 0;
}

/**
 * Function for FSM termination
 * @param obj pointer to structure of type fsm_object, which defines the FSM
 */
void fsm_terminate(struct fsm_object *obj)
{
    // reset FSM base to NULL causes while loop in fsm_main to quit
    // terminating the program
    obj->fsm_cur_state = NULL;
    obj->fsm_cur_state_name = NULL;
    obj->fsm_base = NULL;
}

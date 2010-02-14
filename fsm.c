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
 */
int fsm_init()
{
    //initialize everything to Null or 0
    fsm_base = NULL;
    fsm_cur_state = NULL;
    fsm_arg_num = 0;
    fsm_arg_value = NULL;
    return 0;
}

/**
 * The FSM entry point, this is where execution of code begins in FSM.
 * @param def_state the default state of FSM
 */
int fsm_main(char* def_state)
{
    struct fsm_state *tmp;
    while (1)
    {
        tmp = fsm_base;
        if ((fsm_base==NULL)||(fsm_cur_state==NULL))
        {        
            return -1;
        }
        while ((tmp->name != fsm_cur_state)&&(tmp!=NULL))
            tmp = tmp->next;
        if (tmp == NULL)
            return -1;
        tmp->function(fsm_arg_num,fsm_arg_value);
    }
    return 0;
}

/**
 * Function to add a new state to the FSM.
 * @param state name of the state to be added.
 * @param fun name of the function to be executed for this state
 */
int fsm_add(char *state, void (*fun)(int ,void **) )
{
    struct fsm_state *tmp = fsm_base;
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
 */
int fsm_remove(char *state)
{
    if (!strcmp(state,"default"))
        return -1;
    struct fsm_state *to_del;
    struct fsm_state *tmp=fsm_base;
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
 * @param state name of state to chnage to
 * @param num number of arguments
 * @param arg arguments
 */
int fsm_to_state(char *state, int num, void** arg)
{
    struct fsm_state *tmp=fsm_base;
    while((tmp!=NULL)&&(strcmp(tmp->name,state)))
        tmp=tmp->next;
    if (tmp == NULL)
        return -1;
    fsm_cur_state = tmp->name;
    fsm_arg_num = num;
    fsm_arg_value=arg;
    return 0;
}

/**
 * Function to add a default state to FSM.
 * @details Adds a default state to FSM, this is the function called at the start of the FSM
 * or in case of error, with the appropriate error code
 * @param state name of the state to be added.
 * @param fun name of the function to be executed for this state
 */
int fsm_default(char *state, void (*fun)(int ,void **) )
{
    fsm_base = malloc(sizeof(struct fsm_state));
    fsm_base->name="default";
    fsm_base->function = fun;
    fsm_base->next = NULL;
    // set current state to default
    fsm_cur_state = fsm_base->name;
    return 0;
}

/**
 * Function for FSM termination
 */
void fsm_terminate()
{
    // reset FSM base to NULL causes while loop in fsm_main to quit
    // terminating the program
    fsm_base = NULL;
}

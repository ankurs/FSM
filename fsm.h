/**
 * @file fsm.h
 * @brief an implementation for a FSM in C, this file contains 
 * all definations required for FSM.
 * @author Ankur Shrivastava
 */

/**
 * @struct fsm_state fsm.h "fsm.h"
 * @brief Stores information regarding state
 */
struct fsm_state{
    /**
     * Stores the name of the state
     */
    char *name;
    /**
     * stores the function pointer for the state
     */
    void (*function)(int,void**);
    /**
     * pointer to the next state
     */
    struct fsm_state *next;
} 
/**
 * base pointer, storing the default state information
 */
* fsm_base;

/**
 * stores pointer of current FSM state
 */
char * fsm_cur_state;
/**
 * stores the number of argument passed to the nest state
 */
int fsm_arg_num;
/**
 * stores the values of arguments passed to the next state
 */
void ** fsm_arg_value;

/**
 * Function to initialize the FSM
 */
int fsm_init();

/**
 * The FSM entry point, this is where execution of code begins in FSM.
 */
int fsm_main();

/**
 * Function to add a new state to the FSM.
 * @param state name of the state to be added.
 * @param fun name of the function to be executed for this state
 */
int fsm_add(char *state, void (*fun)(int ,void **) );

/**
 * Function to add a default state to FSM.
 * @details Adds a default state to FSM, this is the function called at the start of the FSM
 * or in case of error, with the appropriate error code
 * @param state name of the state to be added.
 * @param fun name of the function to be executed for this state
 */
int fsm_default(char *state, void (*fun)(int ,void **) );

/**
 * Function to remove a state from the FSM.
 * @param state name of state to be removed
 */
int fsm_remove(char *state);

/**
 * Function to change state.
 * @details changes state to the new specified state, if the state does not exist returns error,
 * state change is not triggered till function calling fsm_to_state returns
 * @param state name of state to chnage to
 * @param num number of arguments
 * @param arg arguments
 */
int fsm_to_state(char *state, int num, void** arg);

/**
 * Function for FSM termination
 */
void fsm_terminate();

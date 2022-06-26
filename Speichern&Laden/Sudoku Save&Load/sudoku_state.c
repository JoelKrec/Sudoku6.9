#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "sudoku_state.h"

// returns a state in its default position (start state (0))
Game_state initialize_game_state()
{
    Game_state emptyState;

    emptyState.state = 0;

    return emptyState;
}

// params: current state
// returns true if the current state is of start state (0)
bool is_start_state(Game_state state)
{
    return state.state == 0;
}

// params: current state
// returns true if the current state is of control state (1)
bool is_control_state(Game_state state)
{
    return state.state == 1;
}

// params: current state
// returns true if the current state is of game state (2)
bool is_game_state(Game_state state)
{
    return state.state == 2;
}

// params: current state
// returns true if the current state is of end state (3)
bool is_end_state(Game_state state)
{
    return state.state == 3;
}

// params: a pointer with the game_state you want to change and your desired target state from 0 to 3
// changes the value of the pointer to the desired target state with the following rules:
// from: 0 to: 1
// from: 1 to: 2
// from: 2 to: 1, 3
// from: 3 to 1
void try_change_state(Game_state* state, int targetState)
{
    switch(state->state)
    {
    case 0:
        if(targetState == 1)
        {
            state->state = targetState;
        }
        else
        {
            //Print Error or do nothing
        }
        break;
    case 1:
        if(targetState == 2)
        {
            state->state = targetState;
        }
        else
        {
            //Print Error or do nothing
        }
        break;
    case 2:
        if(targetState <= 2 && targetState >= 1)
        {
            state->state = targetState;
        }
        else
        {
            //Print Error or do nothing
        }
        break;
    case 3:
        if(targetState == 0)
        {
            state->state = targetState;
        }
        else
        {
            //Print Error or do nothing
        }
        break;
    default:
        //Print Error or do nothing
        break;
    }

}

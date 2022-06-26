#pragma once
#include "sudoku_state.h"

int get_input_game_state(Game_state* state, int* posBig, int* posSmall, bool* detail, int (*sudoku)[9][9], int timeInSecs, clock_t loopStartClock);

void get_input_control_state(Game_state* state);

void get_input_start_state(Game_state* state, int (*sudoku)[9][9], int* timeInSecs);

int get_input_end_state(Game_state* state, int* timeInSecs);

int get_state_input(Game_state* state, int* posBig, int* posSmall, bool* detail, int (*sudoku)[9][9], int* timeInSecs, clock_t loopStartClock);



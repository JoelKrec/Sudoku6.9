#pragma once
#include "sudoku_state.h"

#define HEADING_MAIN "Sudoku V6.9"

void get_input_game_state(Game_state* state, int* posBig, int* posSmall, bool* detail, int (*sudoku)[9][9]);

void get_input_control_state(Game_state* state);

void get_input_start_state(Game_state* state, clock_t* time);

void get_input_end_state(Game_state* state, clock_t* time);

void get_state_input(Game_state* state, int* posBig, int* posSmall, bool* detail, int (*sudoku)[9][9], clock_t* time);

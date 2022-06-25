#pragma once

typedef struct game_state
{
    int state;
} Game_state;

typedef struct game_state Game_state;

Game_state initialize_game_state();

void try_change_state(Game_state* state, int targetState);

bool is_start_state(Game_state state);

bool is_control_state(Game_state state);

bool is_game_state(Game_state state);

bool is_end_state(Game_state state);

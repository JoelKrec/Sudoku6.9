#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include "game_input.h"
#include "sudoku_state.h"
#include "saveload.h"



void increase_vertical(int* position)
{
    *position -= 3;
    if(*position <= -1)
    {
        *position += 9;
    }
}

void go_up(int* posSmall, int* posBig, bool* detail)
{
    if(*detail)
    {
        increase_vertical(posSmall);
    }
    else
    {
        increase_vertical(posBig);
    }
}

void decrease_vertical(int* position)
{
    *position += 3;
    if(*position >= 9)
    {
        *position -= 9;
    }
}

void go_down(int* posSmall, int* posBig, bool* detail)
{
    if(*detail)
    {
        decrease_vertical(posSmall);
    }
    else
    {
        decrease_vertical(posBig);
    }
}

void increase_horizontal(int* position)
{
    *position += 1;
    switch(*position)
    {
    case 3:
        *position = 0;
        break;
    case 6:
        *position = 3;
        break;
    case 9:
        *position = 6;
        break;
    }
}

void go_right(int* posSmall, int* posBig, bool* detail)
{
    if(*detail)
    {
        increase_horizontal(posSmall);
    }
    else
    {
        increase_horizontal(posBig);
    }
}

void decrease_horizontal(int* position)
{
    *position -= 1;
    switch(*position)
    {
    case -1:
        *position = 2;
        break;
    case 2:
        *position = 5;
        break;
    case 5:
        *position = 8;
        break;
    }
}

void go_left(int* posSmall, int* posBig, bool* detail)
{
    if(*detail)
    {
        decrease_horizontal(posSmall);
    }
    else
    {
        decrease_horizontal(posBig);
    }
}

void get_input_game_state(Game_state* state, int* posBig, int* posSmall, bool* detail, int (*sudoku)[9][9])
{

    int input_number = 0;
    bool change_number = false;

    int c = getch();
    switch(c)
    {

    // Handling movement

    case 119: // = W
    case 72:  // = Arrow up
        printf("UP\n");

        go_up(posSmall, posBig, detail);

        break;
    case 115:  // = S
    case 80:   // = Arrow down
        printf("DOWN\n");

        go_down(posSmall, posBig, detail);

        break;
    case 100:  // = D
    case 77:   // = Arrow right
        printf("RIGHT\n");

        go_right(posSmall, posBig, detail);

        break;
    case 97:   // = A
    case 75:   // = Arrow left
        printf("LEFT\n");

        go_left(posSmall, posBig, detail);

        break;
    case 32:   // = Spacebar
        printf("Array Switch!\n");
        if(*detail)
        {
            *detail = false;
        }
        else
        {
            *detail = true;
        }
        break;

    case 'c':  // = C
        try_change_state(state, 1);
        break;

    // Handling number input

    case 49:
        input_number = 1;
        change_number = true;
        break;
    case 50:
        input_number = 2;
        change_number = true;
        break;
    case 51:
        input_number = 3;
        change_number = true;
        break;
    case 52:
        input_number = 4;
        change_number = true;
        break;
    case 53:
        input_number = 5;
        change_number = true;
        break;
    case 54:
        input_number = 6;
        change_number = true;
        break;
    case 55:
        input_number = 7;
        change_number = true;
        break;
    case 56:
        input_number = 8;
        change_number = true;
        break;
    case 57:
        input_number = 9;
        change_number = true;
        break;
    default:
        printf("%i", c);
        break;
    }

    if(change_number)
    {
        (*sudoku)[*posBig][*posSmall] = input_number;
    }
}

void get_input_control_state(Game_state* state)
{
    show_control_screen();

    char c = getch();

    try_change_state(state, 2);
}

void get_input_start_state(Game_state* state, clock_t* time)
{
    // Struktur, in die ein Spielstand geladen werden soll
    Savegame game;
    if (loadScreen(&game)) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                printf("%d", game.sudoku[i][j]);
            }
            printf("\n");
        }
    } else {
         generateNewSudoku(&game);

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                printf("%d", game.sudoku[i][j]);
            }
            printf("\n");
        }
    }

    char c = getch();

    try_change_state(state, 1);
}

void get_input_end_state(Game_state* state, clock_t* time)
{
    char c = getch();

    try_change_state(state, 1);
}

void get_state_input(Game_state* state, int* posBig, int* posSmall, bool* detail, int (*sudoku)[9][9], clock_t* time)
{
    switch(state->state)
    {
    case 0:
        get_input_start_state(state, time);
        break;
    case 1:
        get_input_control_state(state);
        break;
    case 2:
        get_input_game_state(state, posBig, posSmall, detail, sudoku);
        break;
    case 3:
        get_input_end_state(state, time);
        break;
    }
}

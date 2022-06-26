#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include "game_input.h"
#include "sudoku_state.h"
#include "displayGame.h"
#include "control_screen.h"
#include "saveload.h"
#include "saveScreen.h"



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

int get_input_game_state(Game_state* state, int* posBig, int* posSmall, bool* detail, int (*sudoku)[9][9], int timeInSecs, clock_t loopStartClock)
{
    int returnInt = 1;
    int checkInt = 0;
    int input_number = 0;
    bool change_number = false;

    int screenSize = get_screen_width();


    screenSize = screenSize / 5;

    int overflowScreenSize = screenSize % 18;
    screenSize -= overflowScreenSize;

    grid(screenSize * 2, screenSize, *posBig, *posSmall, *detail);    //Startwert kommt von Nikita nach
    fillGrid(*sudoku, screenSize * 2, screenSize);

    int c = getch();
    switch(c)
    {

    // Handling movement

    case 119: // = W
    case 72:  // = Arrow up
        go_up(posSmall, posBig, detail);

        break;
    case 115:  // = S
    case 80:   // = Arrow down
        go_down(posSmall, posBig, detail);

        break;
    case 100:  // = D
    case 77:   // = Arrow right
        go_right(posSmall, posBig, detail);

        break;
    case 97:   // = A
    case 75:   // = Arrow left
        go_left(posSmall, posBig, detail);

        break;
    case 32:   // = Spacebar
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

    case 13:    // = Return
        checkInt = sudokuCheck(*sudoku);

        switch(checkInt)
        {
        case -1:
            // board not filled / contains zeros!
            setCursor(0, screenSize + 1);   // Sets the cursor to the end of the Board

            printf("\nBoard not filled completly. Fill every field slot and try again!");

            break;
        case 0:
            // board not solved but filled completly
            setCursor(0, screenSize + 1);   // Sets the cursor to the end of the Board

            printf("\nBoard not correct. Change some values and try again!                ");   // added more spaces to overwrite potential other messages like the one above this one

            break;
        case 1:
            try_change_state(state, 3);
            break;
        default:
            break;
        }
        break;

    case 27:    // = ESC
        saveSudoku(loopStartClock, timeInSecs, sudoku);

        returnInt = 0;
        break;

    // Handling number input

    case 48:
        input_number = 0;
        change_number = true;
        break;
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
        break;
    }

    if(change_number)
    {
        (*sudoku)[*posBig][*posSmall] = input_number;
    }

    return returnInt;
}

void get_input_control_state(Game_state* state)
{
    system("cls");

    show_control_screen();

    switch(getch())
    {
    default:
        printf("continue!");  //Waits for Input and continues after any button press!
        break;
    }

    system("cls");

    try_change_state(state, 2);
}

void get_input_start_state(Game_state* state, int (*sudoku)[9][9], int* timeInSecs)
{
    Savegame game;

    game.timePlayed = 0;
    if (loadScreen(&game)) {

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                (*sudoku)[i][j] = game.sudoku[i][j];
            }
        }

        *timeInSecs = game.timePlayed;
    }
    else{
        *timeInSecs = 0;
    }

    try_change_state(state, 1);
}

int get_input_end_state(Game_state* state, int* timeInSecs)
{
    show_end_screen(*timeInSecs);

    return 0;
}

int get_state_input(Game_state* state, int* posBig, int* posSmall, bool* detail, int (*sudoku)[9][9], int* timeInSecs, clock_t loopStartClock)
{
    int returnInt = 1;
    switch(state->state)
    {
    case 0:
        get_input_start_state(state, sudoku, timeInSecs);
        break;
    case 1:
        get_input_control_state(state);
        break;
    case 2:
        returnInt = get_input_game_state(state, posBig, posSmall, detail, sudoku, *timeInSecs, loopStartClock);
        break;
    case 3:
        returnInt = get_input_end_state(state, timeInSecs);
        break;
    }
    return returnInt;
}

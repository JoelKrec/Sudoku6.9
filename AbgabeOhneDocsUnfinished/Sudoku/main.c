#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include "game_input.h"
#include "sudoku_state.h"
#include "end_screen.h"
#include "sudoku_time.h"


int main()
{
    system("chcp 437");
    system("cls");

    Game_state state = initialize_game_state();

    int sudoku[9][9] = {{0,1,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}};

    int timeInSecs = 0;
    double loopTime = 0;

    int posX = 0;
    int posY = 0;
    bool detail = false;

    clock_t st = clock();


    while(1)
    {
        loopTime += get_current_sudoku_time_in_secs(st);

        if(loopTime >= 1)
        {
            timeInSecs += (int) loopTime;
            loopTime = 0;
        }

        st = clock();

        //int* pointerToTimeInt = &timeInSecs;

        int playCondition = get_state_input(&state, &posX, &posY, &detail, &sudoku, &timeInSecs, st);

        if(!playCondition)
        {
            return 0;
        }


    }
    return 0;
}

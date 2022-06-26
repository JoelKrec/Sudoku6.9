#include "end_screen.h"
#include <stdio.h>
#include <time.h>
#include "sudoku_time.h"


void show_end_screen(bool isWin, clock_t start_time)
{
    system("cls");

    printf("\n\n\n\n");

    int time_in_secs = get_current_sudoku_time_in_secs(start_time);

    if(isWin)
    {
        printf("WIN   -   You finished in %i", time_in_secs);
    }
    else
    {
        printf("LOSE   -    You finished in %i", time_in_secs);
    }

    printf("\n\n\n\n");

    printf("Press any key to continue!");
}

#include <time.h>
#include "sudoku_time.h"
#include <stdbool.h>

struct sudoku_timer
{
    clock_t st;
};

//params: clock_t created at the beginning of the game
//returns the difference in time since the beginning of the game in seconds
int get_current_sudoku_time_in_secs(clock_t startTime)
{
    int timeInTicks = clock() - startTime;

    return timeInTicks / CLOCKS_PER_SEC;
}

//params: Any time in
clock_t create_clock_from_saved_time(int sudokuTimeInSecs)
{
    clock_t timeInTicks = sudokuTimeInSecs * CLOCKS_PER_SEC;

    clock_t startClock = clock() - timeInTicks;

    return startClock;
}

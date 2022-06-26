#pragma once

#include "saveload.h"
#include <stdio.h>
#include "sudoku_time.h"
#include "control_screen.h"
#include <stdbool.h>
#include <time.h>

void saveSudoku(clock_t loopStartTime, int timeInSecs,int (*sudoku)[9][9]);


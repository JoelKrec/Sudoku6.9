#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "displayGame.h"
#include "solveSudoku.h"

int main()
{
    const int BREITE = 36, HOEHE = 18;

    int Sudoku [9][9] = {
        {7,8,2,1,4,5,6,9,3},
        {9,1,3,8,7,6,4,5,2},
        {4,5,6,9,2,3,7,1,8},
        {2,7,9,5,6,4,3,1,8},
        {5,3,1,2,9,8,7,6,4},
        {8,6,4,1,3,7,5,9,2},
        {4,5,1,9,2,7,8,3,6},
        {6,2,7,3,8,5,1,4,9},
        {3,8,9,6,4,1,2,7,5},
        };

    system("chcp 437");
    system("cls");

    grid(BREITE, HOEHE, 5 , 5, false);
    fill_grid(Sudoku, BREITE, HOEHE);

    if(sudoku_check(Sudoku)){
        printf("valid");
    }
    else{
        printf("not valid");
    }

    getchar();
    return 0;
}

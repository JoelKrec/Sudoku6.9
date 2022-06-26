#include <stdio.h>
#include <stdbool.h>
#include "solveSudoku.h"


/******************************
* Function to check if the Sudoku is Solved.
*
* Parameter:
* int Sudoku[9][9]: Give the funktion the Sudoku Array that he should check.
*
* If it finds a number that is double he will return 0, by a solved Sudoku he will return 1 and by a not finished Sudoku it will return -1;
*******************************/

int sudokuCheck (int Sudoku[9][9]) {
    int x = 0, y = 0, i = 0, j = 0, k = 0;
    int check[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    if(!sudokuFinished(Sudoku)){
        return -1;
    }

    for(y = 0; y < 9; y++){
        for(x = 0; x < 9; x++){
            check[(Sudoku[y][x] - 1)] = 1;
        }
        if(check[0] && check[1] && check[2] && check[3] && check[4] && check[5] && check[6] && check[7] && check[8]){
            for(i = 0; i < 9; i++){
                check[i] = 0;
            }
        }
        else {
            return 0;
        }
    }

    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            for(y = 3 * i; y < 3  * ( i +1); y++){
                for(x = 3 * j ; x < 3 * ( j +1); x++){
                    check[Sudoku[y][x] -1] = 1;
                }
            }
            if(check[0] && check[1] && check[2] && check[3] && check[4] && check[5] && check[6] && check[7] && check[8]) {
                for(k = 0; k < 9; k++){
                    check[k] = 0;
                }
            }
            else
                return 0;
        }
    }

    for(i = 0; i < 3; i++){
        for(j = 0; j < 3;j++){
            for(y = 0 + i; y < 9; y += 3){
                for(x = 0 + j; x < 9; x += 3){
                    check[Sudoku[y][x] -1] = 1;
                }
            }
            if(check[0] && check[1] && check[2] && check[3] && check[4] && check[5] && check[6] && check[7] && check[8]) {
                for(k = 0; k < 9; k++){
                    check[k] = 0;
                }
            }
            else
                return 0;
        }
    }

    return 1;

}

/******************************
* Function to check if the Sudoku is compleatly filled.
*
* Parameter:
* int Sudoku[9][9]: Give the funktion the Sudoku Array that he should check.
*
* If the Array is fully filled it will return true, if not it will return false;
*******************************/

bool sudokuFinished (int Sudoku[9][9]){
    for (int y = 0; y < 9; y++){
        for(int x = 0; x < 9; x++){
            if(!Sudoku[y][x]){
                return false;
            }
        }
    }
    return true;
}



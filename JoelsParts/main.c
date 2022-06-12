#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include "eingabe.h"

void get_input(int* posBig, int* posSmall, bool* detail, int (*sudoku)[9][9])
{

    // 0 Indexing bei positionen beachten!!!
    int c = getch();
    switch(c)
    {
    case 119:
    case 72:
        printf("UP\n");
        if(*detail)
        {
            *posSmall -= 3;
            if(*posSmall <= 0)
            {
                *posSmall += 9;
            }
        }
        else
        {
            *posBig -= 3;
            if(*posBig <= 0)
            {
                *posBig += 9;
            }
        }
        break;
    case 115:
    case 80:
        printf("DOWN\n");
        if(*detail)
        {
            *posSmall += 3;
            if(*posSmall >= 10)
            {
                *posSmall -= 9;
            }
        }
        else
        {
            *posBig += 3;
            if(*posBig >= 10)
            {
                *posBig -= 9;
            }
        }
        break;
    case 100:
    case 77:
        printf("RIGHT\n");
        if(*detail)
        {
            *posSmall += 1;
            switch(*posSmall)
            {
            case 4:
                *posSmall = 1;
                break;
            case 7:
                *posSmall = 4;
                break;
            case 10:
                *posSmall = 7;
                break;
            }
        }
        else
        {
            *posBig += 1;
            switch(*posBig)
            {
            case 4:
                *posBig = 1;
                break;
            case 7:
                *posBig = 4;
                break;
            case 10:
                *posBig = 7;
                break;
            }
        }
        break;
    case 97:
    case 75:
        printf("LEFT\n");
        if(*detail)
        {
            *posSmall -= 1;
            switch(*posSmall)
            {
            case 0:
                *posSmall = 3;
                break;
            case 3:
                *posSmall = 6;
                break;
            case 6:
                *posSmall = 9;
                break;
            }
        }
        else
        {
            *posBig -= 1;
            switch(*posBig)
            {
            case 0:
                *posBig = 3;
                break;
            case 3:
                *posBig = 6;
                break;
            case 6:
                *posBig = 9;
                break;
            }
        }
        break;
    case 32:
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
    case 49:
        (*sudoku)[*posBig][*posSmall] = 1;
        break;
    case 50:
        (*sudoku)[*posBig][*posSmall] = 2;
        break;
    case 51:
        (*sudoku)[*posBig][*posSmall] = 3;
        break;
    case 52:
        (*sudoku)[*posBig][*posSmall] = 4;
        break;
    case 53:
        (*sudoku)[*posBig][*posSmall] = 5;
        break;
    case 54:
        (*sudoku)[*posBig][*posSmall] = 6;
        break;
    case 55:
        (*sudoku)[*posBig][*posSmall] = 7;
        break;
    case 56:
        (*sudoku)[*posBig][*posSmall] = 8;
        break;
    case 57:
        (*sudoku)[*posBig][*posSmall] = 9;
        break;
    default:
        printf("%i", c);
        break;
    }
}

int main()
{
    printf("Hello world!\n");

    int sudoku[9][9] = {{0,1,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}};
    clock_t st, et;
    int frame = 0;

    int posX = 0;
    int posY = 0;
    bool detail = false;

    st = clock();

    while(1)
    {
        if((clock() - st) >= (CLOCKS_PER_SEC / 30))
        {
            system("cls");

            st = clock();

            printf("%i", frame);

            printf("\n\n");

            printf("%i, %i, %i, %i, %i, %i, %i, %i, %i \n", sudoku[0][0], sudoku[0][1], sudoku[0][2], sudoku[1][0], sudoku[1][1], sudoku[1][2], sudoku[2][0], sudoku[2][1], sudoku[2][2]);
            printf("%i, %i, %i, %i, %i, %i, %i, %i, %i \n", sudoku[0][3], sudoku[0][4], sudoku[0][5], sudoku[1][3], sudoku[1][4], sudoku[1][5], sudoku[2][3], sudoku[2][4], sudoku[2][5]);
            printf("%i, %i, %i, %i, %i, %i, %i, %i, %i \n", sudoku[0][6], sudoku[0][7], sudoku[0][8], sudoku[1][6], sudoku[1][7], sudoku[1][8], sudoku[2][6], sudoku[2][7], sudoku[2][8]);
            printf("%i, %i, %i, %i, %i, %i, %i, %i, %i \n", sudoku[3][0], sudoku[3][1], sudoku[3][2], sudoku[4][0], sudoku[4][1], sudoku[4][2], sudoku[5][0], sudoku[5][1], sudoku[5][2]);
            printf("%i, %i, %i, %i, %i, %i, %i, %i, %i \n", sudoku[3][3], sudoku[3][4], sudoku[3][5], sudoku[4][3], sudoku[4][4], sudoku[4][5], sudoku[5][3], sudoku[5][4], sudoku[5][5]);
            printf("%i, %i, %i, %i, %i, %i, %i, %i, %i \n", sudoku[3][6], sudoku[3][7], sudoku[3][8], sudoku[4][6], sudoku[4][7], sudoku[4][8], sudoku[5][6], sudoku[5][7], sudoku[5][8]);
            printf("%i, %i, %i, %i, %i, %i, %i, %i, %i \n", sudoku[6][0], sudoku[6][1], sudoku[6][2], sudoku[7][0], sudoku[7][1], sudoku[7][2], sudoku[8][0], sudoku[8][1], sudoku[8][2]);
            printf("%i, %i, %i, %i, %i, %i, %i, %i, %i \n", sudoku[6][3], sudoku[6][4], sudoku[6][5], sudoku[7][3], sudoku[7][4], sudoku[7][5], sudoku[8][3], sudoku[8][4], sudoku[8][5]);
            printf("%i, %i, %i, %i, %i, %i, %i, %i, %i \n", sudoku[6][6], sudoku[6][7], sudoku[6][8], sudoku[7][6], sudoku[7][7], sudoku[7][8], sudoku[8][6], sudoku[8][7], sudoku[8][8]);

            printf("\n");

            printf("\nx: %i \ny: %i", posX, posY);
            printf("\nSmall array = %d", detail);

            get_input(&posX, &posY, &detail, &sudoku);

            frame++;
        }
    }

    return 0;
}

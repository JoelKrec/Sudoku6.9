#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include "eingabe.h"


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

void get_input(int* posBig, int* posSmall, bool* detail, int (*sudoku)[9][9])
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

int main()
{
    printf("Hello world!\n");

    int sudoku[9][9] = {{0,1,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}, {0,1,2,3,4,5,6,7,8}};
    clock_t st;
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

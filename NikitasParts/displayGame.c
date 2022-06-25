#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include "displayGame.h"

/******************************
* Build the Sudoku grid and color the selected grid Red.
*
* Parameter:
* int BREITE:           Giving over the width of the Sudoku grid.
* int HOEHE:            Giving over the hight of the Sudoku grid.
* int sel_big_grid:     Giving over which one of the 9 of the big grids is selected.
* int sel_small_grid:   Giving over which one of the 9 of the small grids int a selected big grid is selected.
* bool move_grid:       Giving over if the player is moving in the big grid or small grid.
*
* Moving in the big grid will remove the red selection border on the small grid and put it back when small grid is being selected.
* The hight and with should be a divider of 18. The widht should be double the hight.
*******************************/

void grid (int BREITE, int HOEHE, int sel_big_grid, int sel_small_grid, bool move_grid) {

    int BREITE_SMALL = BREITE / 3, HOEHE_SMALL = HOEHE / 3;

    for (int i = 0; i < HOEHE + 1; i++){
        for (int j = 0; j < BREITE + 1; j++){
            set_color(sel_grid_color(sel_big_grid, sel_small_grid, BREITE, HOEHE, j, i, move_grid));

            if (i == 0 && j == 0)
                printf("\xC9");
            else if (i == 0 && j == BREITE)
                printf("\xBB");
            else if (i == HOEHE && j == 0)
                printf("\xC8");
            else if (i == HOEHE && j == BREITE)
                printf("\xBC");
            else if (i == 0 || i == HOEHE)
                printf("\xCD");
            else if (j == 0 || j == BREITE)
                printf("\xBA");

            else if (j == (BREITE / 3))
                printf("\xBA");
            else if (j == (BREITE / 3)*2)
                printf("\xBA");
            else if (i == (HOEHE / 3))
                printf("\xCD");
            else if (i == (HOEHE / 3)*2)
                printf("\xCD");

            else if (j == BREITE_SMALL / 3)
                printf("\xBA");
            else if (j == (BREITE_SMALL / 3) * 2)
                printf("\xBA");
            else if (j == BREITE_SMALL / 3 + BREITE_SMALL)
                printf("\xBA");
            else if (j == (BREITE_SMALL / 3) * 2 + BREITE_SMALL)
                printf("\xBA");
            else if (j == BREITE_SMALL / 3 + BREITE_SMALL * 2)
                printf("\xBA");
            else if (j == (BREITE_SMALL / 3) * 2 + BREITE_SMALL * 2)
                printf("\xBA");

            else if (i == HOEHE_SMALL / 3)
                printf("\xCD");
            else if (i == (HOEHE_SMALL / 3) * 2)
                printf("\xCD");
            else if (i == HOEHE_SMALL / 3 + HOEHE_SMALL)
                printf("\xCD");
            else if (i == (HOEHE_SMALL / 3) * 2 + HOEHE_SMALL)
                printf("\xCD");
            else if (i == HOEHE_SMALL / 3 + HOEHE_SMALL * 2)
                printf("\xCD");
            else if (i == (HOEHE_SMALL / 3) * 2 + HOEHE_SMALL * 2)
                printf("\xCD");


            else
                printf(" ");
        }
        printf("\n");
    }
    set_color(7);
}

/******************************
* Fills the Sudoku grid with the numbers in the Sudoku Array
*
* Parameter:
* int Sudoku[9]9]:  Giving over the Array on with the number that should fill the grid.
* int BREITE:       Giving over the width of the Sudoku grid.
* int HOEHE:        Giving over the hight of the Sudoku grid.
*******************************/

void fill_grid(int Sudoku[9][9], int BREITE, int HOEHE){
    int PosX = BREITE / 18;
    int PosY = HOEHE / 18;
    int x_B, x_S, y_B, y_S, x = 0, y = 0;

    for(y_B = 0; y_B < 3; y_B++){
        for(x_B = 0; x_B < 3; x_B++){
            for(y_S = 0; y_S < 3; y_S++){
                for(x_S = 0; x_S < 3; x_S++){
                    set_cursor(BREITE / 3 * x_B + PosX * x_S * 2 + PosX, HOEHE / 3 * y_B + PosY * y_S * 2 + PosY);
                    if(Sudoku[y][x]){
                        printf("%i", Sudoku[y][x]);
                    }
                    x++;
                }
            }
            y++;
            x = 0;
        }
    }

    return;
}

/******************************
* Returns of the color of the grid based on what is selected.
*
* Parameter:
* int sel_big_grid:     Gives over what of the 9 big grids is being selected.
* int sel_small_grid:   Giving over which one of the 9 of the small grids int a selected big grid is selected.
* int BREITE:           Giving over the width of the Sudoku grid.
* int HOEHE:            Giving over the hight of the Sudoku grid.
* int posX:             Gives over the current X position of the Courser while he is building the grid.
* int posY:             Gives over the current Y position of the Courser while he is building the grid.
* bool move_grid:       Gives over if whe move in the big grid or the small grid in the selected big grid.
*
* Function returns 4 for the color red and 7 for the color white.
*******************************/

int sel_grid_color(int sel_big_grid, int sel_small_grid, int BREITE, int HOEHE, int posX, int posY, bool move_grid){
    int PosX_big = BREITE / 3;
    int PosX_small =  BREITE / 9;
    int PosY_big = HOEHE / 3;
    int PosY_small = HOEHE / 9;
    int x_B = 0, y_B = 0, x_S = 0, y_S = 0;

    grid_coord(&x_B, &y_B, sel_big_grid);
    grid_coord(&x_S, &y_S, sel_small_grid);

    if((posX >= x_B * PosX_big && posX <= (x_B + 1) * PosX_big && (posY == y_B * PosY_big || posY == (y_B + 1) * PosY_big)) || (posY >= y_B * PosY_big && posY <= (y_B + 1) * PosY_big && (posX == x_B * PosX_big || posX == (x_B + 1) * PosX_big))) {
        return 4;

    }
    if(move_grid && ((posX >= x_B * PosX_big + x_S * PosX_small && posX <= x_B * PosX_big + (x_S +1) * PosX_small && (posY == y_B * PosY_big + y_S * PosY_small || posY == y_B * PosY_big + (y_S + 1) * PosY_small)) || (posY >= y_B * PosY_big + y_S * PosY_small && posY <= y_B * PosY_big + (y_S +1) * PosY_small && (posX == x_B * PosX_big + x_S * PosX_small || posX == x_B * PosX_big + (x_S + 1) * PosX_small)))) {

        return 4;
    }
    return 7;
}

void grid_coord(int* x, int* y, int pos) {
    switch (pos){
        case 0:
            *x = 0;
            *y = 0;
            break;
        case 1:
            *x = 1;
            *y = 0;
            break;
        case 2:
            *x = 2;
            *y = 0;
            break;
        case 3:
            *x = 0;
            *y = 1;
            break;
        case 4:
            *x = 1;
            *y = 1;
            break;
        case 5:
            *x = 2;
            *y = 1;
            break;
        case 6:
            *x = 0;
            *y = 2;
            break;
        case 7:
            *x = 1;
            *y = 2;
            break;
        case 8:
            *x = 2;
            *y = 2;
            break;
    }
}

/******************************
* Sets the cursor position in the terminal.
*
* Parameter:
* int x:    Gives over the x coordinate on where the cursor should be set.
* int y:    Gives over the y coordinate on where the cursor should be set.
*******************************/

int set_cursor(int x, int y)
{
    COORD koordinaten;
    koordinaten.X= x;
    koordinaten.Y= y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), koordinaten);
    return 0;
}

/******************************
* Farbattribute werden durch ZWEI hexadezimale Ziffern angegeben - die erste
*   bezieht sich auf den Hintergrund, die zweite auf den Vordergrund. Jede Ziffer
*   kann einen der folgenden Werte annehmen:
*
*   0 = Schwarz        8 = Dunkelgrau
*   1 = Dunkelblau     9 = Blau
*   2 = Dunkelgruen    A = Gruen
*   3 = Blaugruen      B = Zyan
*   4 = Dunkelrot      C = Rot
*   5 = Lila           D = Magenta
*   6 = Ocker          E = Gelb
*   7 = Hellgrau       F = Weiss
*
*   Wenn der COLOR-Befehl ohne Argument aufgerufen wird, werden die Farbein-
*   stellungen wiederhergestellt, mit denen CMD.EXE gestartet wurde. Diese werden
*   durch das aktuelle Konsolenfenster, die /T-Befehlszeilenoption oder durch den
*   Registrierungswert "DefaultColor" bestimmt.
*******************************/

int set_color(char color)
{
    /*

    */
    HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo( hstdout, &csbi );

    SetConsoleTextAttribute( hstdout, color );

    return 0;
}

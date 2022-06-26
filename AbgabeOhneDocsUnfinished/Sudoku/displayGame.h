#pragma once

void grid (int BREITE, int HOEHE, int selBigGrid, int selSmallGrid, bool moveGrid);
void fillGrid(int Sudoku[9][9], int BREITE, int HOEHE);

int setCursor(int x, int y);
int setColor(char color);
int selGridColor(int selBigGrid, int selSmallGrid, int BREITE, int HOEHE, int posX, int posY, bool moveGrid);
void gridCoord(int* x, int* y, int pos);

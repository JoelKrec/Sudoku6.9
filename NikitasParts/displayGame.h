#pragma once

int set_cursor(int x, int y);
int set_color(char color);
void grid (int BREITE, int HOEHE, int sel_big_grid, int sel_small_grid, bool move_grid);
void fill_grid(int Sudoku[9][9], int BREITE, int HOEHE);
int sel_grid_color(int sel_big_grid, int sel_small_grid, int BREITE, int HOEHE, int posX, int posY, bool move_grid);
void grid_coord(int* x, int* y, int pos);

/**
* Testprogramm für das Speichern und Laden von Sudoku-Spielständen
* Autor: Lukas Tetzlaff
* Erstellt am 20.06.2022
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "saveload.h"

int main()
{
    Savegame savegame1 = {
        .id = 0,
        .sudoku = {{1,2,3,4,5,6,7,8,9}, {1,2,3,4,5,6,7,8,9}, {1,2,3,4,5,6,7,8,9}, {1,2,3,4,5,6,7,8,9}, {1,2,3,4,5,6,7,8,9}, {1,2,3,4,5,6,7,8,9}, {1,2,3,4,5,6,7,8,9}, {1,2,3,4,5,6,7,8,9}, {1,2,3,4,5,6,7,8,9}},
        .timePlayed = 300
    };
    //save(savegame1);

    struct Savegame savegame2;

    if(load(1655926418, &savegame2)) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                printf("%d", savegame2.sudoku[i][j]);
            }
            printf("\n");
        }
        printf("%d", savegame2.timePlayed);
    }

    return 0;
}

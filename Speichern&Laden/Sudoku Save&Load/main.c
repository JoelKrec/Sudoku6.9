/**
* Sudoku Testprogramm
* Autor: Lukas Tetzlaff
* Erstellt am 20.06.2022
*
*/

#include "control_screen.h"
#include "end_screen.h"
#include "game_input.h"
#include "saveload.h"
#include "sudoku_state.h"
#include "sudoku_time.h"

int main()
{
    printHeadingMain(HEADING_MAIN);

    Game_state game_state = initialize_game_state();

    while (1) {
        get_state_input(&game_state, NULL, NULL, NULL, NULL, NULL);
    }

    return 0;
}

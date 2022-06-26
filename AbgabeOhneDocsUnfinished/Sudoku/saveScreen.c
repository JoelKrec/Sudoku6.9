#include "saveScreen.h"

void saveSudoku(clock_t loopStartTime, int timeInSecs,int (*sudoku)[9][9])
{
    Savegame game;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            game.sudoku[i][j] = (*sudoku)[i][j];
        }
    }

    game.timePlayed = timeInSecs + get_current_sudoku_time_in_secs(loopStartTime);

    cls();

    printHeadingMain("Save Game");

    printf("\n\n\n");

    printf("            Name your savegame file: ");

    char name[128];

    bool isCorrectName = false;
    do
    {
        scanf("%s", name);



        printf("\n\nAre you sure you want to name your savegame file '%s'?    -   Press Y to confirm or any other key to decline", name);

        char c = getch();

        if(c == 'y' || c == 'Y')
        {
            isCorrectName = true;
        }
        else
        {
            isCorrectName = false;
        }

    }while(!isCorrectName);

    game.name = name;

    char* savedName = save(game);

    printf("\n\n");

    if(savedName == "-1")
    {
        printHeadingSub("Could not save the game    -    Try to check your 'savegames' folder permission!");
    }
    else
    {
        char* saveMessage;

        asprintf(&saveMessage, "Saved game as %s    -    Press any key to quit!", savedName);

        printHeadingSub(saveMessage);
    }
}

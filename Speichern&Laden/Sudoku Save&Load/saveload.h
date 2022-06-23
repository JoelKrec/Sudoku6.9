#ifndef SAVELOAD_H_INCLUDED
#define SAVELOAD_H_INCLUDED

// Spielstand-Struktur
typedef struct Savegame
{
    int id;
    int sudoku[9][9];
    int timePlayed;
} Savegame;

int save(struct Savegame savegame);
int load(int saveId, struct Savegame* savegame);
int checkIntegrity(int saveId);
char* getFileContentsAsString(char* fileName);

#endif // SAVELOAD_H_INCLUDED

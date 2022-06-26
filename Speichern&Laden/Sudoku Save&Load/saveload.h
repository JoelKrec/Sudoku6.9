#ifndef SAVELOAD_H_INCLUDED
#define SAVELOAD_H_INCLUDED

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>

// Spielstand-Struktur
typedef struct Savegame
{
    char* name;
    int sudoku[9][9];
    int timePlayed;
} Savegame;

// Verzeichnis-Struktur
typedef struct FileArray
{
    char* fileNames[1024];
    int fileCount;
} FileArray;

int loadScreen(Savegame* game);
void generateNewSudoku(Savegame* savegame);
char* save(struct Savegame savegame);
int load(char* saveName, struct Savegame* savegame);
int checkIntegrity(char* saveName);
char* getFileContentsAsString(char* fileName);
int listDirectoryContents(char* sDir, char* fileType, struct FileArray* files, int includeWholePath, int includeFileType);
void cls();

#endif // SAVELOAD_H_INCLUDED

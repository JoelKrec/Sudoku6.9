#ifndef SAVELOAD_H_INCLUDED
#define SAVELOAD_H_INCLUDED
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

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

char* save(struct Savegame savegame);
int load(char* saveName, struct Savegame* savegame);
int checkIntegrity(char* saveName);
char* getFileContentsAsString(char* fileName);
int listDirectoryContents(char* sDir, char* fileType, struct FileArray* files, int includeWholePath, int includeFileType);
void cls();

#endif // SAVELOAD_H_INCLUDED

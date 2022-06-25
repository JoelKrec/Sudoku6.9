/**
* Testprogramm für das Speichern und Laden von Sudoku-Spielständen
* Autor: Lukas Tetzlaff
* Erstellt am 20.06.2022
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "saveload.h"

#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80

int main()
{
    Savegame savegame = {
        .name = "Spielstand 1",
        .sudoku = {{1,2,3,4,5,6,7,8,9}, {1,2,3,4,5,6,7,8,9}, {1,2,3,4,5,6,7,8,9}, {1,2,3,4,5,6,7,8,9}, {1,2,3,4,5,6,7,8,9}, {1,2,3,4,5,6,7,8,9}, {1,2,3,4,5,6,7,8,9}, {1,2,3,4,5,6,7,8,9}, {1,2,3,4,5,6,7,8,9}},
        .timePlayed = 300
    };
    //save(savegame);

    // Struktur, in die ein Spielstand geladen werden soll
    struct Savegame game;

    // Lade alle im Spielstandverzeichnis existierenden Spielstanddateien
    struct FileArray saves;
    if (! listDirectoryContents("savegames", "sudokusave", &saves, 0, 0)) {
        return 1;
    }

    int maxDisplayCount = 12; // So viele Speicherdateien werden angezeigt (Länge der Liste)
    int maxCount = saves.fileCount;
    int displayOffset = (saves.fileCount + 1) / 2 + (maxDisplayCount - 1) / 2;
    int i, counter;

    int saveLoaded = 0;

    while (! (saveLoaded == 1)) {
        // Ausgabe der Spielstandauswahl mit scrollender Auswahl
        printf("---Spielstand laden--\n");
        printf("|\n|  #     Name\n|\n");
        counter = 0;
        // Wenn die Anzahl Speicherstände größer ist, als maximal angezeigt werden sollen, bekommt die Liste oben ein Offset, welches nicht angezeigt wird
        if (saves.fileCount > maxDisplayCount) {
            counter = saves.fileCount - maxDisplayCount;
            //displayOffset = (saves.fileCount + 1) / 2 + (saves.fileCount - maxDisplayCount) / 2;
        }
        for (; counter < maxCount; counter++) {
            i = counter + displayOffset;
            if (i > maxCount - 1) {
                i -= maxCount;
            }
            // Aktuell gewählter Spielstand ist in der Mitte und mit Pfeilen angezeigt
            if (counter == (saves.fileCount / 2) + (saves.fileCount - maxDisplayCount) / 2) {
                printf("| >%3d: ", i + 1);
            } else {
                printf("|  %3d: ", i + 1);
            }
            printf("%s", saves.fileNames[i]);
            if (counter == (saves.fileCount / 2) + (saves.fileCount - maxDisplayCount) / 2) {
                printf("<\n");
            } else {
                printf(" \n");
            }
        }
        printf("|\n|\n* HOCH, RUNTER zum waehlen\n* EINGABE zum laden\n* ESC zum beenden");

        int loadFailed = 0;
        // Tastendrücke erkennen
        int key = getch();
        switch (key) {
            case KEY_ENTER:
                i -= (maxDisplayCount - 2) / 2;
                if (i < 0) {
                    i += saves.fileCount;
                }
                saveLoaded = load(saves.fileNames[i], &game);
                loadFailed = ! saveLoaded;
                //return loadFailed; // remove after debugging
                break;
            case KEY_ESC:
                return 0;
            case 224:
                switch(getch()) {
                    case KEY_ARROW_UP: // Pfeiltaste nach oben
                        displayOffset--;
                        break;
                    case KEY_ARROW_DOWN: // Pfeiltaste nach unten
                        displayOffset++;
                        break;
                }
                break;
            case 'w':
                displayOffset--;
                break;
            case 's':
                displayOffset++;
                break;
        }

        // Wraparound des Offsets
        if (displayOffset < 0) {
            displayOffset = maxCount - 1;
        }
        if (displayOffset > maxCount - 1) {
            displayOffset = 0;
        }
        // Fenster leeren
        cls();
        //system("cls");
        // Meldung anzeigen, wenn laden eines Sopelstandes fehlgeschlagen ist
        if (loadFailed) {
            printf("\n[FEHLER] Laden von Spielstand '%s' ist fehlgeschlagen!\n\n", saves.fileNames[i]);
        }
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d", game.sudoku[i][j]);
        }
        printf("\n");
    }

    return 0;
}

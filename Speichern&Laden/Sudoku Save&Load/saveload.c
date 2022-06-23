#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "saveload.h"

/**
* Funktion zum speichern eines Sudoku-Spielstandes in einer Texttdatei
*
* @param struct Savegame savegame
*
* @return int Id des Speicherstandes bei Erfolg, sonst -1
*/
int save(struct Savegame savegame) {
    FILE* out;
    char buffer_out[512], fileName[64];
    time_t now = time(NULL);

    // Wenn keine Id übergeben wurde, neue setzen (Unix Timestamp)
    if (savegame.id == 0) {
        savegame.id = now;
    }

    // Namen der Speicherdatei zusammensetzen und diese im Schreibmodus öffnen
    sprintf_s(fileName, sizeof(fileName), "savegames/%d.sudokusave", savegame.id);
    fopen_s(&out, fileName, "w");
    // Wenn die Datei nicht erstellt werden konnte, gib -1 zurück
    if (out == NULL) {
        return -1;
    }

    // Hinweis zur direkten Bearbeitung
    sprintf_s(buffer_out, sizeof(buffer_out), "Hinweis: Leeres Feld = '.'\n\n");
    fwrite(buffer_out, sizeof(char), strlen(buffer_out), out);

    /* Spielfeld Zeile für Zeile in die Speicherdatei schreiben
    * (Da das Spielfeld im Array in 9er-Blöcken und nicht zeilenweise gespeichert ist,
    * bedarf es ein wenig "Iterationsmagie" um das Spielfeld für Menschen gut lesbar abzuspeichern)
    * Speicherfolge: |01|02|03||04|05|06||07|08|09|
    *                |10|11|12||13|14|15||16|17|18|
    *                |19|20|21||22|23|24||25|26...usw.
    */
    sprintf_s(buffer_out, sizeof(buffer_out), "playingfield#\n");
    fwrite(buffer_out, sizeof(char), strlen(buffer_out), out);
    int block = 0;
    int field = 0;
    while (block < 6 && field < 6) {
        for (int i = 0; i < 3; i++) {
            block = i * 3;
            for (int j = 0; j < 3; j++) {
                field = j * 3;
                for (int k = 0; k < 3; k++) {
                    for (int l = 0; l < 3; l++) {
                        if (savegame.sudoku[block][field] == 0) {
                            sprintf_s(buffer_out, sizeof(buffer_out), "| ");
                        } else {
                            sprintf_s(buffer_out, sizeof(buffer_out), "|%d", savegame.sudoku[block][field]);
                        }
                        fwrite(buffer_out, sizeof(char), strlen(buffer_out), out);
                        field++;
                    }
                    sprintf_s(buffer_out, sizeof(buffer_out), "|");
                    fwrite(buffer_out, sizeof(char), strlen(buffer_out), out);
                    field = j * 3;
                    block++;
                }
                sprintf_s(buffer_out, sizeof(buffer_out), "\n");
                fwrite(buffer_out, sizeof(char), strlen(buffer_out), out);
                block = i * 3;
            }
            if (block < 6) {
                sprintf_s(buffer_out, sizeof(buffer_out), "\n");
                fwrite(buffer_out, sizeof(char), strlen(buffer_out), out);
            }
        }
    }
    sprintf_s(buffer_out, sizeof(buffer_out), ";\n");
    fwrite(buffer_out, sizeof(char), strlen(buffer_out), out);

    // Gespielte Zeit speichern
    sprintf_s(buffer_out, sizeof(buffer_out), "timeplayed#\n%d\n;\n", savegame.timePlayed);
    fwrite(buffer_out, sizeof(char), strlen(buffer_out), out);

    // File-Stream schließen
    fclose(out);

    return savegame.id;
}

/**
* Funktion zum laden eines Sudoku-Spielstandes aus einer Texttdatei
*
* @param int saveId Id des zu ladenden Spielstandes
* @param struct Savegame* Spielstand-Struktur-Pointer, in den der Spielstand geladen werden soll
*
* @return int 1 bei Erfolg, 0 bei Misserfolg
*/
int load(int saveId, struct Savegame* savegame) {
    char fileName[64];
    // Namen der Speicherdatei zusammensetzen
    sprintf_s(fileName, sizeof(fileName), "savegames/%d.sudokusave", saveId);

    char* fileContents;
    if ((fileContents = getFileContentsAsString(fileName)) != NULL) {
        if (checkIntegrity(saveId)) {
            /* Verarbeiten des Dateiinhaltes (Ende des jeweiligen Keywords suchen und bis zum nächsten Semikolon lesen,
            * dann das Verfahren aus der save-Funktion funktional rückwärts abspielen, um ein korrekt angeordnetes Sudoku-Array zu bekommen)
            */
            char* playingField = strstr(fileContents, "playingfield#\n");
            int block, field, fieldInBlock = 0;
            for (int i = strlen("playingfield#\n"); i < strlen(playingField); i++) {
                if (playingField[i] == ';') {
                    break;
                }
                /* Prüfen, ob char aus dem aus der Datei gelesenen String eine Ziffer ist, da zusätzliche Zeichen,
                * wie die vertikalen Balken '|' nur zur schöneren Anzeige in der Speicherdatei dienen und hier verworfen werden können
                */
                if (isdigit(playingField[i])) {
                    block = ((field / 3) % 3) + (((field / 3) / 9) * 3);
                    fieldInBlock = ((field % 3) + ((field / 9) * 3)) - ((field / 27) * 9);
                    // char in int konvertieren und speichern an der entsprechenden Stelle im Struct-Pointer
                    savegame->sudoku[block][fieldInBlock] = playingField[i] - '0';
                    field++;
                }
            }

            savegame->id = saveId;
            savegame->timePlayed = 0;

            // Speicher freigeben
            free(fileContents);

            return 1;
        }
    }
    return 0;
}

/**
* Funktion zum überprüfen der Integrität eines Sudoku-Spielstandes in einer Texttdatei
*
* @param int saveId Id des zu überprüfenden Spielstandes
*
* @return int 1 bei Erfolg, 0 bei Misserfolg
*/
int checkIntegrity(int saveId) {
    char fileName[64];
    // Namen der Speicherdatei zusammensetzen
    sprintf_s(fileName, sizeof(fileName), "savegames/%d.sudokusave", saveId);

    char* fileContents;
    if ((fileContents = getFileContentsAsString(fileName)) != NULL) {
        /* Integrität der Speicherdatei überprüfen, indem nach den "Schlüsseln",
        * welche den Beginn der einzulesenden Daten anzeigen, gesucht wird
        *
        * TODO nach Semikolons suchen
        */
        char* mustBeIncluded[2] = {"playingfield#", "timeplayed#"};
        for (int i = 0; i < 2; i++) {
            if (! strstr(fileContents, mustBeIncluded[i])) {
                return 0;
            }
        }
        // TODO check: Prüfen, ob nach entfernen aller '|' und '\n' nur noch Ziffern im Bereich playingfield# stehen

        return 1;
    }
    return 0;
}

/**
* Funktion zum holen des Inhaltes einer Datei als Zeichenkette
*
* @param char* Name der Datei
*
* @return char* Inhalt der Datei
*/
char* getFileContentsAsString(char* fileName) {
    FILE* in;

    // Speicherdatei im Lesemodus öffnen
    in = fopen(fileName, "r");
    if (in == NULL) {
        return NULL;
    }
    // Zeiger ans Ende der Datei setzen
    fseek(in, 0, SEEK_END);
    // Länge des Inaltes der Datei ermitteln
    int length = ftell(in);
    // Zeiger an den Anfang der Datei setzen
    fseek(in, 0, SEEK_SET);

    // Zeichenkette zum speichern des Dateinhaltes, mit dynamisch zugewiesenem Speicherplatz
    char *fileContents = malloc(sizeof(char) * (length + 1));

    char c;
    int i = 0;
    /* Lese einzelne Zeichen aus Datei nacheinander, bis das Ende der Datei erreicht ist,
    * und speichere sie in der Zeichenkette
    */
    while((c = fgetc(in)) != EOF) {
        fileContents[i] = c;
        i++;
    }
    // Ende der Zeichenkette festlegen
    fileContents[i] = '\0';

    // File-Stream schließen
    fclose(in);

    return fileContents;
}

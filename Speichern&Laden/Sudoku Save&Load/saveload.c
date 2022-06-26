#include "saveload.h"

/**
* Funktion zum anzeigen des Spielstand-Laden-Bildschirmes
*
* @param Savegame* game | Spielstand-Struktur, in die der Spielstand geladen werden soll
*
* @return int | 1 bei Erfolg, 0
*/
int loadScreen(Savegame* game) {
    // Lade alle im Spielstandverzeichnis existierenden Spielstanddateien
    FileArray saves;
    if (! listDirectoryContents("savegames", "sudokusave", &saves, 0, 0)) {
        return 0;
    }

    int maxDisplayCount = 12; // So viele Speicherdateien werden angezeigt (Länge der Liste)
    int maxCount = saves.fileCount;
    int displayOffset = (saves.fileCount + 1) / 2 + (maxDisplayCount - 1) / 2;
    int i, counter;

    int saveLoaded = 0;

    while (! (saveLoaded == 1)) {
        // Ausgabe der Spielstandauswahl mit scrollender Auswahl
        printHeadingSub("Load Game");
        printf("\n Num    Name\n\n");
        counter = 0;
        // Wenn die Anzahl Speicherstände größer ist, als maximal angezeigt werden sollen, bekommt die Liste oben ein Offset, welches nicht angezeigt wird
        if (saves.fileCount > maxDisplayCount) {
            counter = saves.fileCount - maxDisplayCount;
        }
        for (; counter < maxCount; counter++) {
            i = counter + displayOffset;
            if (i > maxCount - 1) {
                i -= maxCount;
            }
            // Aktuell gewählter Spielstand ist in der Mitte und mit Pfeilen angezeigt
            if (counter == (saves.fileCount / 2) + (saves.fileCount - maxDisplayCount) / 2) {
                printf(" >%3d: ", i + 1);
            } else {
                printf("  %3d: ", i + 1);
            }
            printf("%s", saves.fileNames[i]);
            if (counter == (saves.fileCount / 2) + (saves.fileCount - maxDisplayCount) / 2) {
                printf("< \n");
            } else {
                printf("  \n");
            }
        }
        printf("\n\n");
        printf(" Navigate - ARROW UP & ARROW DOWN OR W & S\n");
        printf(" Load     - ENTER\n");
        printf(" Exit     - ESC\n");
        print_full_line();

        int loadFailed = 0;
        // Tastendrücke erkennen
        int key = getch();
        switch (key) {
            case KEY_ENTER:
                i -= (maxDisplayCount - 2) / 2;
                if (i < 0) {
                    i += saves.fileCount;
                }
                saveLoaded = load(saves.fileNames[i], game);
                loadFailed = ! saveLoaded;
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
        // Meldung anzeigen, wenn laden eines Spielstandes fehlgeschlagen ist
        if (loadFailed) {
            printf("\n[ERROR] Loading of save '%s' failed!\n\n", saves.fileNames[i]);
        }
    }
    printf("\n[SUCCESS] Save %s loaded!\n\n", saves.fileNames[i]);

    return 1;
}

/**
* Funktion zum speichern eines Sudoku-Spielstandes in einer Texttdatei
*
* @param Savegame savegame | Der zu speichernde Spielstand
*
* @return char* | Name des Speicherstandes bei Erfolg, sonst "-1"
*/
char* save(Savegame savegame)
{
    FILE* out;
    FILE* duplicate;
    char buffer_out[512];
    char* fileName;
    time_t now = time(NULL);

    // Wenn kein Name übergeben wurde, neue setzen (Unix Timestamp)
    if (strlen(savegame.name) == 0) {
        sprintf(savegame.name, "%d", (int)now);
    }

    // Namen der Speicherdatei zusammensetzen und bei bereits vorhandener Datei mit gleichem Namen '_x' anhängen, wobei x eine aufsteigende Zahl ist
    asprintf(&fileName, "savegames/%s.sudokusave", savegame.name);
    fopen_s(&duplicate, fileName, "r");
    int appendNum = 0;
    while (! (duplicate == NULL)) {
        asprintf(&fileName, "savegames/%s_%d.sudokusave", savegame.name, appendNum);
        fopen_s(&duplicate, fileName, "r");
        appendNum++;
    }

    // Speicherdatei im Schreibmodus öffnen
    fopen_s(&out, fileName, "w");
    // Wenn die Datei nicht erstellt werden konnte, gib -1 zurück
    if (out == NULL) {
        return "-1";
    }

    /* Spielfeld Zeile für Zeile in die Speicherdatei schreiben
    * (Da das Spielfeld im Array in 9er-Blöcken und nicht zeilenweise gespeichert ist,
    * bedarf es ein wenig "Iterationsmagie" um das Spielfeld für Menschen gut lesbar abzuspeichern)
    * Speicherfolge: |01|02|03| |04|05|06| |07|08|09|
    *                |10|11|12| |13|14|15| |16|17|18|
    *                |19|20|21| |22|23|24| |25|26...usw.
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

    // Dateistrom schließen
    fclose(out);

    return savegame.name;
}

/**
* Funktion zum laden eines Sudoku-Spielstandes aus einer Sudoku-Spielstand-Datei(.sudokusave)
*
* @param char* saveName | Name des zu ladenden Spielstandes
* @param struct Savegame* savegame | Spielstand-Struktur, in die der Spielstand geladen werden soll
*
* @return int | 1 bei Erfolg, 0 wenn kein Dateiinhalt geladen werden konnte, -1 wenn die Integrität der Speicherdatei nicht gegeben ist
*/
int load(char* saveName, Savegame* savegame)
{
    char* fileName;
    // Namen der Speicherdatei zusammensetzen
    asprintf(&fileName, "savegames/%s.sudokusave", saveName);

    char* fileContents;
    if ((fileContents = getFileContentsAsString(fileName)) != NULL) {
        if (checkIntegrity(saveName)) {
            /* Verarbeiten des Dateiinhaltes (Ende des jeweiligen Keywords suchen und bis zum nächsten Semikolon lesen,
            * dann das Verfahren aus der save-Funktion funktional rückwärts abspielen, um ein korrekt angeordnetes Sudoku-Array zu bekommen).
            */
            char* playingField = strstr(fileContents, "playingfield#");
            int block, field, fieldInBlock = 0;
            for (int i = strlen("playingfield#"); i < strlen(playingField); i++) {
                if (playingField[i] == ';') {
                    break;
                }
                /* Prüfen, ob das aktuelle Zeichen aus dem aus der Datei gelesenen String eine Ziffer ist, da zusätzliche Zeichen,
                * wie die vertikalen Balken '|' nur zur schöneren Anzeige in der Speicherdatei dienen und hier verworfen werden können.
                * Leerzeichen werden zu 0, da leere Felder im Spielfeld-Array mit einer Null repräsentiert werden.
                */
                block = ((field / 3) % 3) + (((field / 3) / 9) * 3);
                fieldInBlock = ((field % 3) + ((field / 9) * 3)) - ((field / 27) * 9);
                if (isdigit(playingField[i])) {
                    // char in int konvertieren und speichern an der entsprechenden Stelle im Struct-Pointer
                    savegame->sudoku[block][fieldInBlock] = playingField[i] - '0';
                    field++;
                } else if (playingField[i] == ' ') {
                    savegame->sudoku[block][fieldInBlock] = 0;
                }
            }
            // Gespielte Zeit einlesen
            char* substr = strstr(fileContents, "timeplayed#");
            char timeplayed[16];
            for (int i = strlen("timeplayed#"); i < strlen(substr); i++) {
                if (substr[i] == ';') {
                    break;
                }
                if (isdigit(substr[i])) {
                    timeplayed[i - strlen("timeplayed#")] = substr[i];
                }
            }

            savegame->name = saveName;
            sscanf(timeplayed, "%d", &savegame->timePlayed);

            // Speicher freigeben
            free(fileContents);

            return 1;
        }
        return -1;
    }
    return 0;
}

/**
* Funktion zum überprüfen der Integrität eines Sudoku-Spielstandes
*
* @param char* saveName | Name des zu überprüfenden Spielstandes
*
* @return int | 1 bei Erfolg, 0 bei Misserfolg
*/
int checkIntegrity(char* saveName)
{
    char* fileName;
    // Namen der Speicherdatei zusammensetzen
    asprintf(&fileName, "savegames/%s.sudokusave", saveName);

    char* fileContents;
    if ((fileContents = getFileContentsAsString(fileName)) != NULL) {
        /* Integrität der Speicherdatei überprüfen, indem nach den "Schlüsseln",
        * welche den Beginn des jweiligen Speicherbereiches der einzulesenden Daten anzeigen gesucht wird
        * und geprüft wird, ob der Bereich mit einem Semikolon abgeschlossen ist.
        */
        char* mustBeIncluded[2] = {"playingfield#", "timeplayed#"};
        int sectionEnd = 0;
        for (int i = 0; i < 2; i++) {
            char* section;
            if (! (section = strstr(fileContents, mustBeIncluded[i]))) {
                return 0;
            }
            int sectionStart = (int)(section - fileContents);

            if (! (section = strstr(section, ";"))) {
                return 0;
            }
            if ((int)(section - fileContents) <= sectionEnd) {
                return 0;
            }
            sectionEnd = (int)(section - fileContents);
        }
        /* Prüfen, ob die Summe aller Ziffern und Leerzeichen im Bereich playingfield# genau 81(9x9) beträgt,
        * um sicherzustellen, dass beim laden nicht auf nicht-existente Array-Keys zugegriffen wird,
        * oder dass das Spielfeld nicht vollständig gefüllt wird.
        */
        int counter = 0;
        char* playingField = strstr(fileContents, "playingfield#");
        for (int i = strlen("playingfield#"); i < strlen(playingField); i++) {
            if (playingField[i] == ';') {
                break;
            }
            if (isdigit(playingField[i]) || playingField[i] == ' ') {
                counter++;
            }
        }
        if (counter != 81) {
            return 0;
        }

        return 1;
    }
    return 0;
}

/**
* Funktion zum holen des Inhaltes einer Datei als Zeichenkette
*
* @param char* fileName | Name der Datei
*
* @return char* | Inhalt der Datei
*/
char* getFileContentsAsString(char* fileName)
{
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

/**
* Funktion zum auflisten aller Dateien in einem Verzeichnis
*
* @param char* sDir | Name des Verzeichnisses, in dem gesucht werden soll
* @param char* fileType | Endung der Dateien, nach denen gesucht werden soll
* @param struct FileArray* files | Struktur, in der Namen und Anzahl gefundener Dateien gespeichert werden
* @param int includeWholePath | 1 = sDir ist im Dateinamen enthalten, 0 = nur Dateiname + ggf. Endung
* @param int includeFileType | 1 = Endung ist im Dateinamen enthalten, 0 = nur ggf. Verzeichnis + Dateiname
*
* @return int | 1 bei Erfolg, 0 bei Misserfolg
*
* (Abgewandelt von: https://stackoverflow.com/questions/2314542/listing-directory-contents-using-c-and-windows)
*/
int listDirectoryContents(char* sDir, char* fileType, FileArray* files, int includeWholePath, int includeFileType)
{
    // Datei- und Handle-Struktur
    WIN32_FIND_DATA fdFile;
    HANDLE hFind = NULL;

    // Zwischenspeicher
    int index = 0;
    char* fileName;

    // In sPath wird der jeweils gefundene Dateiname gespeichert
    char sPath[2048];

    //Dateimaske (Alle Dateien mit Endung .sudokusave)
    sprintf(sPath, "%s\\*.%s", sDir, fileType);

    if((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
    {
        printf("Path not found: [%s]\n", sDir);
        return 0;
    }

    do {
        //Die ersten beiden von FindFirstFile gefundenen Verzeichnisse sind immer "." und "..", daher überspringen
        if(strcmp(fdFile.cFileName, ".") != 0 && strcmp(fdFile.cFileName, "..") != 0) {
            //Pfad aus übergebenem Verzeichnis und Dateiname zusammensetzen
            sprintf(sPath, "%s\\%s", sDir, fdFile.cFileName);

            // Unterverzeichnisse werden ignoriert
            if(! (fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)) {
                // Speichern des Dateinamen, um diesen in der Speicherstand-Auswahl anzeigen zu können
                if (includeWholePath) {
                    asprintf(&fileName, "%s", sPath);
                } else {
                    asprintf(&fileName, "%s", fdFile.cFileName);
                }
                if (! includeFileType) {
                    // Dateinamen von Endung trennen
                    asprintf(&fileName, "%s", strtok(fileName, "."));
                }
                files->fileNames[index] = fileName;
                index++;
            }
        }
    } while(FindNextFile(hFind, &fdFile)); // Wiederhole, solange weitere Dateien gefunden werden

    // Werte übergeben
    files->fileCount = index;

    // Schließen der Datei-Such-Handle
    FindClose(hFind);

    return 1;
}

/**
* Eigene schnellere implementation von system("cls")
*
* Quelle: https://stackoverflow.com/questions/34842526/update-console-without-flickering-c#answer-34843392
*/
void cls()
{
    // Get the Win32 handle representing standard output.
    // This generally only has to be done once, so we make it static.
    const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD topLeft = { 0, 0 };

    // Figure out the current width and height of the console window
    if (GetConsoleScreenBufferInfo(hOut, &csbi)) {
        DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

        DWORD written;

        // Flood-fill the console with spaces to clear it
        FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

        // Reset the attributes of every character to the default.
        // This clears all background colour formatting, if any.
        FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

        // Move the cursor back to the top left for the next sequence of writes
        SetConsoleCursorPosition(hOut, topLeft);
    }
}

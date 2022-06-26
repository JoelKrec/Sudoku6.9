#include "control_screen.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <windows.h>

void show_control_screen()
{
   printHeadingSub("Control");

   print_controls();
}

void print_controls()
{
    int controls_arrays_length = 4;

    char* controls_keys_array[4] = {"WASD or arrow keys",
    "space bar",
    "C",
    "check"};

    char* controls_definition_array[4] = {"Move in fields or blocks",
    "Switch between blocks and fields",
    "Shows controls screen",
    "Checks your board for completion"};

    char* filler = "    <-->   ";

    for(int i = 0; i < controls_arrays_length; i++)
    {
        printf("\n");

        int padding = 60 - strlen(controls_keys_array[i]) - 7;

        for(int j = 0; j < padding; j++)
        {
            printf(" ");
        }

        printf("%s%s%s\n", controls_keys_array[i], filler, controls_definition_array[i]);
    }
}

void print_heading(char* header, char frameChar, int borderWidth)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int ret;
    ret = GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&csbi);

    int screen_width = csbi.dwSize.X;

    print_full_line(screen_width, frameChar);

    print_border_line(screen_width, frameChar, borderWidth);

    for(int i = 0; i < borderWidth; i++) {
        printf("%c", frameChar);
    }

    int header_length = strlen(header);

    if(header_length % 2 != 0)
    {
        printf(" ");
    }

    int empty_space_next_to_header = (screen_width - (borderWidth * 2) - header_length) / 2;

    for(int i = 0; i < empty_space_next_to_header; i++)
    {
        printf(" ");
    }

    printf("%s", header);

    for(int i = 0; i < empty_space_next_to_header; i++)
    {
        printf(" ");
    }

    for(int i = 0; i < borderWidth; i++) {
        printf("%c", frameChar);
    }

    print_border_line(screen_width, frameChar, borderWidth);

    print_full_line(screen_width, frameChar);
}

void printHeadingMain(char* header)
{
    print_heading(header, '#', 2);
}

void printHeadingSub(char* header)
{
    print_heading(header, '.', 1);
}

void print_full_line(int screen_width, char frameChar)
{
    for(int i = 0; i < screen_width; i++)
    {
        printf("%c", frameChar);
    }
}

void print_border_line(int screen_width, char frameChar, int borderWidth)
{
    for(int i = 0; i < borderWidth; i++) {
        printf("%c", frameChar);
    }
    for(int i = 0; i < screen_width - borderWidth * 2; i++) {
        printf(" ");
    }
    for(int i = 0; i < borderWidth; i++) {
        printf("%c", frameChar);
    }
}

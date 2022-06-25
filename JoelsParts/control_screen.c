#include "control_screen.h"
#include <stdlib.h>

void show_control_screen()
{
   print_heading("Controls");

   print_controls();
}

void print_controls()
{
    int controls_array_length = 4;

    char* controls_array[4] = {"WASD or arrow keys  -   Move in fields or blocks",
    "space bar   -   Switch between blocks and fields",
    "C   -   Shows controls screen",
    "check   -   Checks your board for completion"};

    for(int i = 0; i < controls_array_length; i++)
    {
        printf("\n");

        int padding = (120 - strlen(controls_array[i])) / 2;

        for(int j = 0; j < padding; j++)
        {
            printf(" ");
        }

        printf("%s\n", controls_array[i]);
    }
}

void print_heading(char* header)
{
    print_full_line();

    print_border_line();

    printf("##");

    int header_length = strlen(header);

    int empty_space_next_to_header = (120 - 4 - header_length) / 2;

    for(int i = 0; i < empty_space_next_to_header; i++)
    {
        printf(" ");
    }



    printf("%s", header);

    for(int i = 0; i < empty_space_next_to_header; i++)
    {
        printf(" ");
    }

    printf("##");

    print_border_line();

    print_full_line();
}

void print_full_line()
{
    for(int i = 0; i < 120; i++)
    {
        printf("#");
    }
}

void print_border_line()
{
    printf("##");
    for(int i = 0; i < 116; i++)
    {
        printf(" ");
    }
    printf("##");
}

#include "IntroImage.h"
#include <curses.h>
#include <iostream>
#include <fstream>

#define CO_1     1
#define CO_2     2
#define CO_3     3
#define CO_4     4
#define CO_5     5
#define CO_6     6
#define CO_7     7
#define CO_8     8

#define CO_11     11
#define CO_12     12
#define CO_13     13
#define CO_14     14
#define CO_15     15
#define CO_16     16
#define CO_17     17
#define CO_18     18


IntroImage::IntroImage()
{
    //ctor
}

IntroImage::~IntroImage()
{
    //dtor
}

void IntroImage::display(WINDOW* gameWindow)
{
    FILE *src;
    char znak;

    char** image = new char*[15];
    for (int i = 0; i < 15; i++)
    {
        image[i] = new char[77];
    }
    src = fopen ("files/intro_image.txt", "r");

    std::cout << "intro file loading" << std::endl;

    znak = fgetc(src);

    for (int i=0; i < 15; i++)
    {
        for (int j=0; j < 77; j++)
        {
            if(znak != EOF)
            {
                if(znak == '\n' || znak == '\r')
                {
                    j=-1;
                }
                else
                {
                    image[i][j] = znak;
                }
                znak = fgetc(src);
            }
        }
    }
    fclose(src); //zamykamy plik


    if (has_colors() == FALSE)
    {
        printf("Your terminal does not support color.\n");
        printf("Cannot display the intro.\n");
    }
    else
    {
        start_color();
        init_pair(CO_1, COLOR_BLACK, COLOR_BLACK);
        init_pair(CO_2, COLOR_BLACK, COLOR_RED);
        init_pair(CO_3, COLOR_BLACK, COLOR_GREEN);
        init_pair(CO_4, COLOR_BLACK, COLOR_YELLOW);
        init_pair(CO_5, COLOR_BLACK, COLOR_BLUE);
        init_pair(CO_6, COLOR_BLACK, COLOR_MAGENTA);
        init_pair(CO_7, COLOR_BLACK, COLOR_CYAN);
        init_pair(CO_8, COLOR_BLACK, COLOR_WHITE);

        init_pair(CO_11, COLOR_WHITE, COLOR_BLACK);
        init_pair(CO_12, COLOR_WHITE, COLOR_RED);
        init_pair(CO_13, COLOR_WHITE, COLOR_GREEN);
        init_pair(CO_14, COLOR_WHITE, COLOR_YELLOW);
        init_pair(CO_15, COLOR_WHITE, COLOR_BLUE);
        init_pair(CO_16, COLOR_WHITE, COLOR_MAGENTA);
        init_pair(CO_17, COLOR_WHITE, COLOR_CYAN);
        init_pair(CO_18, COLOR_WHITE, COLOR_WHITE);


        wattron(gameWindow, COLOR_PAIR(CO_3));
        mvwaddch(gameWindow, 1, 1, 'x');
        wattroff(gameWindow, COLOR_PAIR(CO_3));
        wattron(gameWindow, COLOR_PAIR(CO_2));
        mvwaddch(gameWindow, 1, 2, 'X');
        wattroff(gameWindow, COLOR_PAIR(CO_2));

        wattron(gameWindow, COLOR_PAIR(CO_13));
        mvwaddch(gameWindow, 1, 3, 'x');
        wattroff(gameWindow, COLOR_PAIR(CO_13));
        wattron(gameWindow, COLOR_PAIR(CO_12));
        mvwaddch(gameWindow, 1, 4, 'X');
        wattroff(gameWindow, COLOR_PAIR(CO_12));

        wrefresh(gameWindow);

        for (int i = 0; i<15; i++)
        {
            for (int j = 0; j<77; j++)
            {
                wattron(gameWindow, COLOR_PAIR(CO_13));
                mvwaddch(gameWindow, i, j, image[i][j]);
                wattroff(gameWindow, COLOR_PAIR(CO_13));
            }
        }
        wrefresh(gameWindow);

    }
}

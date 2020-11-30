#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <clocale>
#include <vector>

#include "Menu.h"
#include "Game.h"
#include "View.h"
#include "ViewText.h"
#include "ViewGraphic.h"
#include "CoursesList.h"
#include "Window.h"
#include "WindowText.h"

using namespace std;

int main()
{
    /* mode 0 -> tekstowy, mode 1 -> graficzny */
    int mode = 0;
    int quit = 0;

    View* view_pointer;
    Menu* menu;
    Window* window;

    while (!quit)
    {
        if ( mode == 0 )
        {
            view_pointer = new ViewText();
            window = new WindowText();
        }
        else
        {
            view_pointer = new ViewGraphic();
            window = new WindowText(); // temp
        }

        menu = new Menu(window, &mode, &quit);
        menu->run_menu();

        view_pointer->test();

        Game* game = new Game(view_pointer, window);
        game->setup_window();
        game->play_game();

    }
}
/*

1) meni

*/





/*int main()
{
    CoursesList* courses = new CoursesList();

    return 0;
}*/


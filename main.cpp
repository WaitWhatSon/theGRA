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
    // mode 0 -> tekstowy, mode 1 -> graficzny
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
            /// NIEZAIMPLEMENTOWANE ///
        //else
        //{
        //    view_pointer = new ViewGraphic();
        //    window = new WindowGraphic();
        //}

        menu = new Menu(window, &mode, &quit);
        menu->run_menu();

        if (!quit)
        {
            Game* game = new Game(view_pointer, window);
            game->setup_window();
            game->play_game();
        }
    }
}


/*
int main()
{
    CoursesList* courses = new CoursesList();

    std::cout << endl << endl << endl;
    vector<Course> rand = courses->get_random_courses_list(1);

    for (int i = 0; i < rand.size(); i++)
    {
        std::cout << rand[i].get_name() << endl;
    }

    return 0;
}
*/

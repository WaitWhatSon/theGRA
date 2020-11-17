#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <iostream>
#include <thread>

#include "Menu.h"
#include "Game.h"
#include "View.h"
#include "ViewText.h"
#include "ViewGraphic.h"

using namespace std;

/*void foo()
{
    for (int i = 0; i < 10; i++)
    {
        usleep(2000000);
        cout << "elo" << endl;
    }
}
*/


int main()
{
    View* view_pointer;
    ViewText view;
    view_pointer = &view;
    view_pointer->test();

    Game* game = new Game(view_pointer);
    game->create_window();
    game->play_game();


    /*std::thread thread_obj(foo);

    thread_obj.join();*/
}

#include <stdio.h>
#include <curses.h>
#include "Menu.h"
#include "Game.h"
#include "View.h"
#include "ViewText.h"
#include "ViewGraphic.h"


using namespace std;

int main()
{
    View* view_pointer;
    ViewText view;
    view_pointer = &view;
    view_pointer->test();

    Game* game = new Game(view_pointer);
    game->create_window();
    game->play_game();
}

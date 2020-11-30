#include "ViewText.h"
#include "View.h"
#include "Window.h"

#include <clocale>

#include <curses.h>

ViewText::ViewText()
{
    //ctor
}

void ViewText::test()
{

}

void ViewText::clockUpdate(Window* window, char decSec, char sec)
{
        window->add_ch(16, 70, decSec);
        window->add_ch(16, 71, sec);
        window->refresh();
}

void ViewText::mapFragmentUpdate(Window* window, int x, int y, char current_map_char)
{
    window->add_ch(y, x, current_map_char);
}

void ViewText::playerPositionUpdate(Window* window, int x, int y, char player_character)
{
    window->add_ch(y, x, player_character);
}

ViewText::~ViewText()
{
    //dtor
}

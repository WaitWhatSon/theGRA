#include "ViewText.h"
#include "View.h"

#include <curses.h>
#include <iostream>
using namespace std;

ViewText::ViewText()
{
    //ctor
}

void ViewText::test()
{
    cout << "tekstowy\n";
}

void ViewText::mapFragmentUpdate(WINDOW* window, int x, int y, char current_map_char)
{
    mvwaddch(window, y, x, current_map_char);
    //cout << "map x: " << x << " y: " << y << "\n";  //debug
}

void ViewText::playerPositionUpdate(WINDOW* window, int x, int y, char player_character)
{
    mvwaddch(window, y, x, player_character);
    //cout << "player x: " << x << " y: " << y << "\n";  //debug
}

ViewText::~ViewText()
{
    //dtor
}

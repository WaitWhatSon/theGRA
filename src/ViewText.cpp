#include "ViewText.h"
#include "View.h"
#include "Window.h"

#include <clocale>
#include <string>

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
        window->add_ch(16, 72, decSec);
        window->add_ch(16, 73, sec);
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

void ViewText::gameBar(Window* window)
{
    window->add_str_colour(15,  0, " semester: next course:       room number:  week:            score:    time: ", 5);
    window->add_str_colour(16,  0, "|         |                  |             |                |         |   s |", 2);
}

void ViewText::gameBarUpdate(Window* window, int semester, const char* course_name, const char* room_number, int week, int score)
{
    window->add_ch(16, 2, semester+48);
    window->add_str(16, 12, course_name);
    window->add_str(16, 31, room_number);
    std::string week_string = std::to_string(week);
    window->add_str(16, 45, week_string.c_str());
    std::string score_string = std::to_string(score);
    window->add_str(16, 62, score_string.c_str());
}

ViewText::~ViewText()
{
    //dtor
}

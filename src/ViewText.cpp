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
    //window->add_str_colour(16,  0, "|         |                  |             |                |         |   s |", 2);
}

void ViewText::gameBarUpdate(Window* window, int semester, const char* course_name, const char* room_number, int week, int score)
{
    window->add_str_colour(16,  0, "|         |                  |             |                |         |   s |", 2);
    window->add_ch(16, 2, semester+48);
    window->add_str(16, 12, course_name);
    window->add_str(16, 31, room_number);
    std::string week_string = std::to_string(week);
    window->add_str(16, 45, week_string.c_str());
    std::string score_string = std::to_string(score);
    window->add_str(16, 62, score_string.c_str());
}

void ViewText::gameOver(Window* window)
{
    window->add_str_colour(16, 72, "!!!", 4);
    window->add_str_colour(8, 34, "GAME OVER", 6);
}

void ViewText::playerNameChoice(Window* window)
{
    window->add_str_colour(5, 33, "PLAYER NAME:", 1);
    window->add_str_colour(7, 33, ">          <", 1);
    window->add_str_colour(9, 30, "(max 10 characters)", 2);
}

void ViewText::updatePlayerName(Window* window, std::string name)
{
    window->add_str_colour(7, 34, name.c_str(), 2);
    if(name.size()<10)
    {
        window->add_ch(7, 34+name.size(), ' ');
    }
}

ViewText::~ViewText()
{
    //dtor
}

#include "View.h"

View::View()
{

}

View::View(Window* _window)
{
    this->window = _window;
}

void View::clockUpdate(char decSec, char sec)
{

}

void View::mapFragmentUpdate(int x, int y, char current_map_char)
{

}

void View::playerPositionUpdate(int x, int y, char player_character)
{

}

void View::gameBarUpdate(int semester, const char* course_name, const char* room_number, int week, int score)
{

}

void View::gameBar()
{

}

void View::gameOver()
{

}

void View::playerNameChoice()
{

}

void View::updatePlayerName(std::string name)
{

}

const void View::display_logo()
{

}

const void View::display_options(int position, std::string best_player, int best_score)
{

}

const void View::controls_display()
{

}

const void View::display_quit()
{

}

const void View::menu_move_up_clear(int position)
{

}

const void View::menu_move_up_draw(int position)
{

}

const void View::menu_move_down_clear(int position)
{

}

const void View::menu_move_down_draw(int position)
{

}


View::~View()
{
    //dtor
}

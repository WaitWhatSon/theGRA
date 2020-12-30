#include "ViewGraphic.h"

#define X_ 9
#define y_ 18

#define MENU_POS_X1 100

ViewGraphic::ViewGraphic()
{

}

ViewGraphic::ViewGraphic(Window* _window)
{
    this->window = _window;
}

void ViewGraphic::clockUpdate(char decSec, char sec)
{
        //this->window->add_ch(500, 300, decSec);
        //this->window->add_ch(510, 300, sec);
        //this->window->refresh();
}

void ViewGraphic::mapFragmentUpdate(int x, int y, char current_map_char)
{
    //this->window->add_ch(y*10, x*10, current_map_char);
}

void ViewGraphic::playerPositionUpdate(int x, int y, char player_character)
{
    this->window->add_ch(y*18+10, x*9+10, player_character);
}

void ViewGraphic::gameBar()
{
    this->window->add_str(400, 50, "semester: next course: room number: week: score: time:");
}

void ViewGraphic::gameBarUpdate(int semester, const char* course_name, const char* room_number, int week, int score)
{
    this->window->add_str_colour(16,  0, "|         |                  |             |                |         |   s |", 2);
    this->window->add_ch(16, 2, semester+48);
    this->window->add_str(16, 12, course_name);
    this->window->add_str(16, 31, room_number);
    std::string week_string = std::to_string(week);
    this->window->add_str(16, 45, week_string.c_str());
    std::string score_string = std::to_string(score);
    this->window->add_str(16, 62, score_string.c_str());
}

void ViewGraphic::gameOver()
{
    //this->window->add_str_colour(16, 72, "!!!", 4);
    //this->window->add_str_colour(8, 34, "GAME OVER", 6);
}

void ViewGraphic::playerNameChoice()
{
    this->window->add_str(5, 33, "PLAYER NAME:");
    this->window->add_str(7, 33, ">          <");
    this->window->add_str(9, 30, "(max 10 characters)");
}

void ViewGraphic::updatePlayerName(std::string name)
{
    const char * const_name = name.c_str();
    this->window->add_str(100, 100, const_name);
}

const void ViewGraphic::display_quit()
{
    this->window->add_str(100,  300, "Are you sure you want to exit PB?");
    this->window->add_str(100,  500, "(press X if you are sure)");
}

////////MENU///////

const void ViewGraphic::display_logo()
{

}

const void ViewGraphic::display_options(int position, std::string best_player, int best_score)
{
    this->window->add_str(MENU_POS_X1*1, 100, "(P) PLAY GAME");
    this->window->add_str(MENU_POS_X1*2, 100, "(M) SWITCH MODE");
    this->window->add_str(MENU_POS_X1*3, 100, "(C) CONTROLS");
    this->window->add_str(MENU_POS_X1*4, 100, "(X) EXIT");

    this->window->add_str(MENU_POS_X1*2, 300, "--> BEST PLAYER <--");

    this->window->add_str(MENU_POS_X1*3, 300, (best_player).c_str());
    const char * score = (std::to_string(best_score)).c_str();
    this->window->add_str(MENU_POS_X1*3, 350, score);
}

const void ViewGraphic::controls_display()
{
    this->window->add_str(1,  26, "------> CONTROLS <------");
    this->window->add_str(3,  10, "--> PLAYER CONTROLS <--");
    this->window->add_str(5,  10, "move up");
    this->window->add_str(5,  28+3, "UP");
    this->window->add_str(6,  10, "move down");
    this->window->add_str(6,  28+1, "DOWN");
    this->window->add_str(7,  10, "move left");
    this->window->add_str(7,  28+1, "LEFT");
    this->window->add_str(8,  10, "move right");
    this->window->add_str(8,  28, "RIGHT");
    this->window->add_str(10, 10, "floor up");
    this->window->add_str(10, 28+4, "W");
    this->window->add_str(11, 10, "floor down");
    this->window->add_str(11, 28+4, "S");
    this->window->add_str(12, 10, "admit");
    this->window->add_str(12, 28+4, "A");
    this->window->add_str(14, 30, "back to menu");
    this->window->add_str(14, 45, "X");
}

const void ViewGraphic::menu_move_up_clear(int position)
{
    // unused in this mode
}

const void ViewGraphic::menu_move_up_draw(int position)
{
    // used for player choice position displaying
    this->window->add_ch(MENU_POS_X1*(1+position), 50, 'b');
}

const void ViewGraphic::menu_move_down_clear(int position)
{
    // unused in this mode
}

const void ViewGraphic::menu_move_down_draw(int position)
{
    // unused in this mode
}

ViewGraphic::~ViewGraphic()
{
    //dtor
}



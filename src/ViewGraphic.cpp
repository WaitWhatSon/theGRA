#include "ViewGraphic.h"
#include <cstring>

#define X_ 9
#define y_ 18


ViewGraphic::ViewGraphic() {}

ViewGraphic::ViewGraphic(Window* _window) {this->window = _window; this->display_quit_var = false;}

void ViewGraphic::clockUpdate(char decSec, char sec)
{
    std::string time = std::to_string(decSec) + std::to_string(sec);
    this->window->add_str_colour(300, 650, time.c_str(), 'g');
}

void ViewGraphic::mapFragmentUpdate(int x, int y, char current_map_char)
{
    // impossible to implement with this library
}

void ViewGraphic::playerPositionUpdate(int x, int y, char player_character)
{
    this->window->add_ch(y*18+10, x*9+10, player_character);
}

void ViewGraphic::gameBar()
{
    this->window->add_str_colour(300, 20, "semester:\nweek:", 'w');
    this->window->add_str_colour(300, 250, "next course:\nroom number:", 'w');
    this->window->add_str_colour(300, 550, "time:\nscore:", 'w');
}

void ViewGraphic::gameBarUpdate(int semester, const char* course_name, const char* room_number, int week, int score)
{
    this->gameBar();

    std::string semester_week = std::to_string(semester) + "\n" + std::to_string(week);
    std::string score_string = std::to_string(score);

    this->window->add_str_colour(300, 150, semester_week.c_str(), 'g');
    this->window->add_str_colour(300, 400, course_name, 'g');
    this->window->add_str_colour(325, 400, room_number, 'g');
    this->window->add_str_colour(325, 650, score_string.c_str(), 'g');

}

void ViewGraphic::gameOver()
{
    this->window->add_str_colour(300, 650, "!!!", 'r');
    this->window->add_str_colour(150, 260, "GAME OVER", 'q');
}

void ViewGraphic::playerNameChoice()
{
    this->window->add_str(150, 100, "PLAYER NAME:");
    this->window->add_str(175, 100, "(max 10 characters)");
}

void ViewGraphic::updatePlayerName(std::string name)
{
    const char * const_name = name.c_str();
    this->window->add_str_colour(200, 100, const_name, 'g');
    if(!name.empty())
    {
        this->window->add_str(225, 100, "(press ENTER to play)");
    }
}

const void ViewGraphic::display_quit()
{
    this->window->add_str_colour(360,  100, "Are you sure you want to exit PB? (press X if you are sure)", 'r');
}

////////MENU///////

const void ViewGraphic::display_logo()
{
    // unused - logo displaying in loop
}

const void ViewGraphic::display_options(int position, std::string best_player, int best_score)
{
    this->window->add_str(     200, 100, "(P) PLAY GAME");
    this->window->add_str(50*1+200, 100, "(M) SWITCH MODE");
    this->window->add_str(50*2+200, 100, "(C) CONTROLS");
    this->window->add_str(50*3+200, 100, "(X) EXIT");

    this->window->add_str(50*1+200, 350, "BEST PLAYER:");
    this->window->add_str_colour(50*1+200, 500, (best_player).c_str(), 'g');

    this->window->add_str(50*2+200, 410, "SCORE:");
    const char * score = (std::to_string(best_score)).c_str();
    this->window->add_str_colour(50*2+200, 500, score, 'g');
}

const void ViewGraphic::controls_display()
{
    this->window->add_str(50,  300, "CONTROLS");
    this->window->add_str_colour(75,  265, "PLAYER CONTROLS", 'g');
    this->window->add_str(125,  100, "move up");
    this->window->add_str_colour(125,  300, "UP", 'g');
    this->window->add_str(150,  100, "move down");
    this->window->add_str_colour(150,  300, "DOWN", 'g');
    this->window->add_str(175,  100, "move left");
    this->window->add_str_colour(175,  300, "LEFT", 'g');
    this->window->add_str(200,  100, "move right");
    this->window->add_str_colour(200,  300, "RIGHT", 'g');
    this->window->add_str(250, 100, "floor up");
    this->window->add_str_colour(250,  300, "W", 'g');
    this->window->add_str(275, 100, "floor down");
    this->window->add_str_colour(275,  300, "S", 'g');
    this->window->add_str(300, 100, "admit");
    this->window->add_str_colour(300,  300, "A", 'g');
    this->window->add_str(350, 260, "back to menu");
    this->window->add_str_colour(350,  430, "X", 'g');
    this->window->add_str_colour(350,  500, "sound on/of  N", 'g');
}

const void ViewGraphic::menu_move_up_clear(int position)
{
    // used for color text at player choice
    if (position == 0)
    {
        this->window->add_str_colour(200, 100, "(P) PLAY GAME", 'g');
    }
    else if (position == 1)
    {
        this->window->add_str_colour(250, 100, "(M) SWITCH MODE", 'g');
    }
    else if (position == 2)
    {
        this->window->add_str_colour(300, 100, "(C) CONTROLS", 'g');
    }
    else if (position == 3)
    {
        this->window->add_str_colour(350, 100, "(X) EXIT", 'g');
    }
}

const void ViewGraphic::menu_move_up_draw(int position)
{
    // used for player choice position displaying
    this->window->add_ch(50*position+200, 70, 'g');
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



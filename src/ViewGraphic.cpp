#include "ViewGraphic.h"

ViewGraphic::ViewGraphic()
{

}


ViewGraphic::ViewGraphic(Window* _window)
{
    this->window = _window;
}

void ViewGraphic::clockUpdate(char decSec, char sec)
{
        this->window->add_ch(16, 72, decSec);
        this->window->add_ch(16, 73, sec);
        this->window->refresh();
}

void ViewGraphic::mapFragmentUpdate(int x, int y, char current_map_char)
{
    this->window->add_ch(y, x, current_map_char);
}

void ViewGraphic::playerPositionUpdate(int x, int y, char player_character)
{
    this->window->add_ch(y, x, player_character);
}

void ViewGraphic::gameBar()
{
    this->window->add_str_colour(15,  0, " semester: next course:       room number:  week:            score:    time: ", 5);
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
    this->window->add_str_colour(16, 72, "!!!", 4);
    this->window->add_str_colour(8, 34, "GAME OVER", 6);
}

void ViewGraphic::playerNameChoice()
{
    this->window->add_str_colour(5, 33, "PLAYER NAME:", 1);
    this->window->add_str_colour(7, 33, ">          <", 1);
    this->window->add_str_colour(9, 30, "(max 10 characters)", 2);
}

void ViewGraphic::updatePlayerName(std::string name)
{
    this->window->add_str_colour(7, 34, name.c_str(), 2);
    if(name.size()<10)
    {
        this->window->add_ch(7, 34+name.size(), ' ');
    }
}

const void ViewGraphic::display_logo()
{
    this->window->add_str_colour(1, 16,    " ________ __            _______ _______ ____", 1);
    this->window->add_str_colour(2, 16,    "/__   __// /           / _____// ___  // _  |", 1);
    this->window->add_str_colour(3, 16,    "  /  /  / /__  _____  / / ___ / /__/_// /_| |", 1);
    this->window->add_str_colour(4, 16,    " /  /  / __  // '__/ / /__/ // ___ \\ / ___  |", 1);
    this->window->add_str_colour(5, 16,    "/__/  /_/ /_//____/ /______//_/  /_//_/   |_|", 1);
}

const void ViewGraphic::display_options(int position, std::string best_player, int best_score)
{
    this->window->add_str(8,  10, "(P) PLAY GAME");
    this->window->add_str(10, 10, "(M) SWITCH MODE");
    this->window->add_str(12, 10, "(C) CONTROLS");
    this->window->add_str(14, 10, "(X) EXIT");

    this->window->add_str_colour((8 + position*2), 8, ">", 1);

    this->display_logo();
    this->window->add_str_colour(6, 16, "-----------------> TheGRA <-----------------", 1);

    this->window->add_str_colour(9, 50, "--> BEST PLAYER <--", 1);

    this->window->add_str(11, 50, (best_player).c_str());
    const char * score = (std::to_string(best_score)).c_str();
    this->window->add_str(11, 50+15, score);
}

const void ViewGraphic::controls_display()
{
    this->window->window_clear();

    this->window->add_str_colour(1,  26, "------> CONTROLS <------", 1);
    this->window->add_str_colour(3,  10, "--> PLAYER CONTROLS <--", 1);
    this->window->add_str_colour(5,  10, "move up", 1);
    this->window->add_str_colour(5,  28+3, "UP", 2);
    this->window->add_str_colour(6,  10, "move down", 1);
    this->window->add_str_colour(6,  28+1, "DOWN", 2);
    this->window->add_str_colour(7,  10, "move left", 1);
    this->window->add_str_colour(7,  28+1, "LEFT", 2);
    this->window->add_str_colour(8,  10, "move right", 1);
    this->window->add_str_colour(8,  28, "RIGHT", 2);
    this->window->add_str_colour(10, 10, "floor up", 1);
    this->window->add_str_colour(10, 28+4, "W", 2);
    this->window->add_str_colour(11, 10, "floor down", 1);
    this->window->add_str_colour(11, 28+4, "S", 2);
    this->window->add_str_colour(12, 10, "admit", 1);
    this->window->add_str_colour(12, 28+4, "A", 2);
    this->window->add_str_colour(14, 30, "back to menu", 1);
    this->window->add_str_colour(14, 45, "X", 2);

}

const void ViewGraphic::display_quit()
{
    this->window->add_str(17,  9, "Are you sure you want to exit PB?");
    this->window->add_str_colour(17,  43, "(press X if you are sure)", 1);
}


ViewGraphic::~ViewGraphic()
{
    //dtor
}



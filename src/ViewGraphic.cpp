#include "ViewGraphic.h"

#define X_ 9
#define y_ 18


ViewGraphic::ViewGraphic() {}

ViewGraphic::ViewGraphic(Window* _window) {this->window = _window;}

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
    this->window->add_str(100,  300, "Are you sure you want to exit PB?");
    this->window->add_str(100,  500, "(press X if you are sure)");
}

////////MENU///////

const void ViewGraphic::display_logo()
{

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
}

const void ViewGraphic::menu_move_up_clear(int position)
{
    // used for color text
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
    this->window->add_ch(50*position+200, 50, 'b');
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



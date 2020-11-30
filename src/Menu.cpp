#include "Menu.h"
#include "Window.h"

#include <stdio.h>
#include <curses.h>
#include <fstream>
#include <string.h>


Menu::Menu()
{
    //ctor
}

Menu::Menu(Window* _win, int* _mode, int* _quit)
{
    //ctor
    this->win = _win;
    this->mode = _mode;
    this->quit = _quit;
    this->position = 0;
    this->loop = 1;

    update_best_player();
}

void Menu::display_options()
{
    this->win->add_str(8,  10, "(P) PLAY GAME");
    this->win->add_str(10, 10, "(M) SWITCH MODE");
    this->win->add_str(12, 10, "(C) CONTROLS");
    this->win->add_str(14, 10, "(X) EXIT");

    this->win->add_str_colour((8 + this->position*2), 8, ">", 1);

    this->win->display_logo();
    this->win->add_str_colour(6, 16, "-----------------> TheGRA <-----------------", 1);

    this->win->add_str_colour(9, 50, "--> BEST PLAYER <--", 1);

    this->win->add_str(11, 50, this->best_player);
    const char * score = (std::to_string(this->best_score)).c_str();
    this->win->add_str(11, 50+15, score);
}

void Menu::run_menu()
{
    this->win->window_clear();
    this->display_options();

    while (this->loop)
    {
        this->get_choice();
    }
}

int Menu::get_choice()
{
    int choice = this->win->get_ch();//wgetch(win);
    switch(choice)
    {
        case KEY_UP:
            move_up();
            break;
        case KEY_DOWN:
            move_down();
            break;
        case 10:
            if (this->position == 0)
                play_game();
            else if (this->position == 1)
                change_mode();
            else if (this->position == 2)     //
                controls_display();
            else if (this->position == 3)     //
                quit_game();
            break;
        case 'p':     //
            play_game();
            break;
        case 'm':     //
            change_mode();
            break;
        case 'c':     //
            controls_display();
            break;
        case 'x':     //
            quit_game();
            break;
        default:
            break;
    }
    return choice;
}

void Menu::move_up()
{
    if(this->position <= 0)
    {
        return; // wy¿ej sie nie da
    }
    else
    {
        this->win->add_ch((8 + this->position*2), 8, ' ');
        this->position--;
        this->win->add_str_colour((8 + this->position*2), 8, ">", 1);
    }
}

void Menu::move_down()
{
    if(this->position >= 3)
    {
        return; // ni¿ej sie nie da
    }
    else
    {
        this->win->add_ch((8 + this->position*2), 8, ' ');
        this->position++;
        this->win->add_str_colour((8 + this->position*2), 8, ">", 1);
    }
}

void Menu::quit_game()
{
    *(this->quit) = 1;
    this->loop = 0;
}

void Menu::play_game()
{
    this->loop = 0;
}

void Menu::change_mode()
{
    *(this->mode) = (*(this->mode)+1) %2;
    this->win->add_ch(10, 30, *(this->mode)+48); //temp
}

void Menu::controls_display()
{
    this->win->window_clear();

    this->win->add_str_colour(1,  26, "------> CONTROLS <------", 1);
    this->win->add_str_colour(3,  10, "--> PLAYER CONTROLS <--", 1);
    this->win->add_str_colour(5,  10, "move up", 1);
    this->win->add_str_colour(5,  28+3, "UP", 2);
    this->win->add_str_colour(6,  10, "move down", 1);
    this->win->add_str_colour(6,  28+1, "DOWN", 2);
    this->win->add_str_colour(7,  10, "move left", 1);
    this->win->add_str_colour(7,  28+1, "LEFT", 2);
    this->win->add_str_colour(8,  10, "move right", 1);
    this->win->add_str_colour(8,  28, "RIGHT", 2);
    this->win->add_str_colour(10, 10, "floor up", 1);
    this->win->add_str_colour(10, 28+4, "W", 2);
    this->win->add_str_colour(11, 10, "floor down", 1);
    this->win->add_str_colour(11, 28+4, "S", 2);
    this->win->add_str_colour(12, 10, "admit", 1);
    this->win->add_str_colour(12, 28+4, "A", 2);
    this->win->add_str_colour(14, 30, "back to menu", 1);
    this->win->add_str_colour(14, 45, "X", 2);


    while (this->win->get_ch() != 'x')
    {
        ;
    }
    this->win->window_clear();
    this->display_options();
    this->win->add_str_colour((8 + this->position*2), 8, ">", 1);
}

void Menu::update_best_player()
{
    std::ifstream file( "files/best_player.txt", std::ios::in );
    std::string name;
    int score;

    if( !file )
        exit(-1);

    while( file >> name >> score )
    {
        best_player = name.c_str();
        best_score = score;
    }

    file.close();
}


Menu::~Menu()
{
    //dtor
}

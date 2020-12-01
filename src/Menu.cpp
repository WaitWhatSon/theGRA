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

void Menu::run_menu()
{
    this->win->window_clear();
    this->win->display_options(this->position, this->best_player, this->best_score);

    while (this->loop)
    {
        this->get_choice();
    }
}

int Menu::get_choice()
{
    int choice = this->win->get_ch();
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
                this->controls_display();
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
        return; // wy�ej sie nie da
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
        return; // ni�ej sie nie da
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
    this->win->controls_display();

    while (this->win->get_ch() != 'x')
    {
        ;
    }
    this->win->window_clear();
    this->win->display_options(this->position, this->best_player, this->best_score);
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
        best_player = name;
        best_score = score;
    }

    file.close();
}


Menu::~Menu()
{
    //dtor
}

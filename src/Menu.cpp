#include "Menu.h"
#include "Window.h"

#include <stdio.h>
#include <curses.h>


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
}

void Menu::run_menu()
{
    while (this->get_choice() != 'x')
    {

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

}

void Menu::move_down()
{

}

void Menu::quit_game()
{

}



Menu::~Menu()
{
    //dtor
}

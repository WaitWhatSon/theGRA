#include "MenuText.h"

MenuText::MenuText()
{
    //ctor
}

MenuText::MenuText(View* _view, int* _mode, int* _quit)
{
    //ctor
    this->view = _view;
    this->mode = _mode;
    this->quit = _quit;
    this->position = 0;
    this->loop = 1;

    update_best_player();
}

void MenuText::run_menu()
{
    this->view->window->window_clear();
    this->view->display_options(this->position, this->best_player, this->best_score);
    int old_mode = *(this->mode);

    while (this->loop)
    {
        this->get_choice();
        if(*(this->mode) != old_mode)
        {
            return;
        }
    }
}

int MenuText::get_choice()
{
    int choice = this->view->window->get_ch();
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

void MenuText::move_up()
{
    if(this->position <= 0)
    {
        return; // wy¿ej sie nie da
    }
    else
    {
        this->view->menu_move_up_clear(position);
        this->position--;
        this->view->menu_move_up_draw(position);
    }
}

void MenuText::move_down()
{
    if(this->position >= 3)
    {
        return; // ni¿ej sie nie da
    }
    else
    {
        this->view->menu_move_down_clear(position);
        this->position++;
        this->view->menu_move_down_draw(position);
    }
}

void MenuText::quit_game()
{
    *(this->quit) = 1;
    this->loop = 0;
}

void MenuText::play_game()
{
    this->loop = 0;
}

void MenuText::change_mode()
{
    *(this->mode) = (*(this->mode)+1) %2;
    this->view->window->add_ch(10, 30, *(this->mode)+48); //temp
}

void MenuText::controls_display()
{
    this->view->controls_display();

    while (this->view->window->get_ch() != 'x')
    {
        ;
    }
    this->view->window->window_clear();
    this->view->display_options(this->position, this->best_player, this->best_score);
}

void MenuText::update_best_player()
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


MenuText::~MenuText()
{
    //dtor
}

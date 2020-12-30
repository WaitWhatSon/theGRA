#include "MenuGraphic.h"
#include "WindowGraphic.h"

#define SFML_STATIC
#include <SFML/Graphics.hpp>

#include <iostream>


sf::Texture texture_background;
sf::Texture texture_logo;

sf::Sprite background_menu;
sf::Sprite logo;

MenuGraphic::MenuGraphic(View* _view, int* _mode, int* _quit, sf::RenderWindow& win):win(win)
{
    //ctor
    this->view = _view;
    this->mode = _mode;
    this->quit = _quit;
    this->position = 0;
    this->loop = 1;

    update_best_player();

    if (!texture_background.loadFromFile("files/background_photo.png")) exit -1;
    if (!texture_logo.loadFromFile("files/logo.png")) exit -1;

    background_menu.setTexture(texture_background);
    logo.setTexture(texture_logo);
}

using namespace sf;

void MenuGraphic::run_menu()
{
    /*  "This clear/draw/display cycle is the only good way to draw things.
    Don't try other strategies, such as keeping pixels from the previous frame,
    "erasing" pixels, or drawing once and calling display multiple times.
    You'll get strange results due to double-buffering.
        Modern graphics hardware and APIs are really made for repeated
    clear/draw/display cycles where everything is completely refreshed at each
    iteration of the main loop. Don't be scared to draw 1000 sprites 60 times
    per second, you're far below the millions of triangles that your computer
    can handle."

    ~ https://www.sfml-dev.org/tutorials/2.5/graphics-draw.php
    */

    // run the program as long as the window is open
    while (this->win.isOpen() && this->loop)
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (this->win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                this->win.close();
            }
            else if(event.type == sf::Event::KeyPressed)
            {
                if      (event.key.code == sf::Keyboard::Up)    move_up();
                else if (event.key.code == sf::Keyboard::Down)  move_down();
                else if (event.key.code == sf::Keyboard::Enter) get_choice();
                else if (event.key.code == sf::Keyboard::P)     play_game();
                else if (event.key.code == sf::Keyboard::M)     change_mode();
                else if (event.key.code == sf::Keyboard::C)     controls_display();
                else if (event.key.code == sf::Keyboard::X)     quit_game();
            }
        }
        // clear the window with black color
        this->win.clear(sf::Color::Black);
        this->win.draw(background_menu);
        this->win.draw(logo);
        this->view->display_options(this->position, this->best_player, this->best_score);
        this->view->menu_move_up_draw(this->position);
        this->view->menu_move_up_clear(this->position);
        // end the current frame
        this->win.display();
    }
    return;
}

int MenuGraphic::get_choice()
{
    if (this->position == 0)
        this->play_game();
    else if (this->position == 1)
        this->change_mode();
    else if (this->position == 2)
        this->controls_display();
    else if (this->position == 3)
        this->quit_game();

    return 0;
}

void MenuGraphic::move_up()
{
    if(this->position <= 0)
    {
        return; // wy¿ej sie nie da
    }
    else
    {
        this->position--;
    }
}

void MenuGraphic::move_down()
{
    if(this->position >= 3)
    {
        return; // ni¿ej sie nie da
    }
    else
    {
        this->position++;
    }
}

void MenuGraphic::quit_game()
{
    *(this->quit) = 1;
    this->loop = 0;

    this->win.close();
}

void MenuGraphic::play_game()
{
    this->loop = 0;
}

void MenuGraphic::change_mode()
{
    *(this->mode) = (*(this->mode)+1) %2;
    this->loop = 0;
}

void MenuGraphic::controls_display()
{
    this->win.clear(sf::Color::Black);
    this->win.draw(background_menu);
    this->view->controls_display();
    this->win.display();

    int escape = 0;

    while (this->win.isOpen() && !escape)
    {
        sf::Event event;
        while (this->win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                this->win.close();
            }
            else if(event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::X) escape=1;
            }
        }
    }
}

void MenuGraphic::update_best_player()
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


MenuGraphic::~MenuGraphic()
{
    //dtor
}

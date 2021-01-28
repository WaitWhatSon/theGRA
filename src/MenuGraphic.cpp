#include "MenuGraphic.h"
#include "WindowGraphic.h"

#include "Common.h"

#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

/* muzyczki ze strony: */
/* https://freesound.org/search/ */

sf::Texture texture_background;
sf::Texture texture_logo;

sf::Sprite background_menu;
sf::Sprite logo;

sf::SoundBuffer buffer;
sf::Sound bad;

sf::SoundBuffer buffer2;
sf::Sound good;

sf::Music music;

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
    logo.setPosition(205, 35);

    if (!buffer.loadFromFile("files/music/bad.wav"))
        exit -1;
    bad.setBuffer(buffer);

    if (!buffer2.loadFromFile("files/music/good.wav"))
        exit -1;
    good.setBuffer(buffer2);

    if (!music.openFromFile("files/music/menu_music.wav"))
        exit -1;

    //music_on = false;

    music.setLoop(true);
    if(music_on) music.play();
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
    int display = 1;
    while (this->win.isOpen() && this->loop)
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (this->win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                *(this->quit) = 1;
                music.stop();
                this->win.close();
            }
            else if(event.type == sf::Event::KeyPressed)
            {
                if      (event.key.code == sf::Keyboard::Up)    {move_up();}
                else if (event.key.code == sf::Keyboard::Down)  move_down();
                else if (event.key.code == sf::Keyboard::Enter) get_choice();
                else if (event.key.code == sf::Keyboard::P)     play_game();
                else if (event.key.code == sf::Keyboard::M)     change_mode();
                else if (event.key.code == sf::Keyboard::N)     {if(music_on){music_on = false; music.stop();} else{music_on = true; music.play();}}
                else if (event.key.code == sf::Keyboard::C)     controls_display();
                else if (event.key.code == sf::Keyboard::X)     quit_game();
                display = 1;
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                if (event.mouseMove.x>=100 && event.mouseMove.x<=240 &&
                    event.mouseMove.y>=200 && event.mouseMove.y<=225){position=0; display = 1;}
                else if (event.mouseMove.x>=100 && event.mouseMove.x<=275 &&
                         event.mouseMove.y>=250 && event.mouseMove.y<=275){position=1; display = 1;}
                else if (event.mouseMove.x>=100 && event.mouseMove.x<=235 &&
                         event.mouseMove.y>=300 && event.mouseMove.y<=325){position=2; display = 1;}
                else if (event.mouseMove.x>=100 && event.mouseMove.x<=175 &&
                         event.mouseMove.y>=350 && event.mouseMove.y<=375){position=3; display = 1;}
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                    while(event.type != sf::Event::MouseButtonReleased)
                    {
                        this->win.pollEvent(event);
                        if (event.type == sf::Event::MouseButtonReleased){get_choice();}
                        else if (event.type == sf::Event::MouseButtonPressed &&
                                event.mouseButton.button == sf::Mouse::Right){display = 1; break;}
                    }
            }
            else if (event.type == sf::Event::Resized){display = 1;}
        }
        if(display)
        {
        // clear the window with black color
        this->win.clear(sf::Color::Black);
        this->win.draw(background_menu);
        this->win.draw(logo);
        this->view->display_options(this->position, this->best_player, this->best_score);
        this->view->menu_move_up_draw(this->position);
        this->view->menu_move_up_clear(this->position);
        // end the current frame
        this->win.display();
        display = 0;
        //std::cout << "display";
        }
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
        if(music_on)bad.play();
        return; // wy¿ej sie nie da
    }
    else
    {
        if(music_on)good.play();
        this->position--;
    }
}

void MenuGraphic::move_down()
{
    if(this->position >= 3)
    {
        if(music_on)bad.play();
        return; // ni¿ej sie nie da
    }
    else
    {
        if(music_on)good.play();
        this->position++;
    }
}

void MenuGraphic::quit_game()
{
    *(this->quit) = 1;
    this->loop = 0;
    if(music_on)music.stop();

    this->win.close();
}

void MenuGraphic::play_game()
{
    this->loop = 0;
    if(music_on)music.stop();
}

void MenuGraphic::change_mode()
{
    *(this->mode) = (*(this->mode)+1) %2;
    this->loop = 0;
    if(music_on)music.stop();
}

void MenuGraphic::controls_display()
{
    if(music_on)good.play();
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
                else if (event.key.code == sf::Keyboard::N)     {if(music_on){music_on = false; music.stop();} else{music_on = true; music.play();}}
                if(music_on) good.play();
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

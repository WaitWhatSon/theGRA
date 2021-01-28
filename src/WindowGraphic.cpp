#include "WindowGraphic.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define X_SIZE 15
#define Y_SIZE 10


using namespace sf;

sf::Font font;

sf::Texture texture_player;
sf::Sprite player;

sf::Texture texture_music_off;
sf::Sprite music_off;

WindowGraphic::WindowGraphic(sf::RenderWindow& _win):win(_win)
{
    win.setVisible(true);
    if(!win.isOpen())
    {
        exit(-1);
    }
    win.clear();
    if (!font.loadFromFile("files/open_sans/OpenSans-Regular.ttf"))
    {
        std::cout << "font not loaded";
        exit(-1);
    }

    if (!texture_player.loadFromFile("files/player.png")) exit -1;
    player.setTexture(texture_player);

    if (!texture_music_off.loadFromFile("files/musicoff.png")) exit -1;
    music_off.setTexture(texture_music_off);
}

WindowGraphic::~WindowGraphic()
{
    //dtor
}

int WindowGraphic::get_ch()
{
    return 0;
}

int WindowGraphic::add_ch(int x, int y, char c)
{
    if ( c == 'g' ) // menu choice
    {
        CircleShape shape(10.f);
        shape.setFillColor(Color::Green);
        shape.setPosition(y, x);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(3.f);
        win.draw(shape);
    }
    else if ( c == '@' ) // player
    {
        //RectangleShape rect;
        //rect.setSize(Vector2f(9, 18));
        //rect.setFillColor(Color::Green);
        //rect.setPosition(y, x);
        //win.draw(rect);
        CircleShape shape(15.f);
        shape.setOutlineThickness(3.f);
        shape.setOutlineColor(sf::Color::Green);
        shape.setFillColor(Color(0,0,0,0));
        shape.setPosition(y-10, x-6);
        win.draw(shape);
        player.setPosition(y, x);
        win.draw(player);
    }
    else if ( c == 'd' )
    {
        CircleShape shape(15.f);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(y-10, x-6);
        win.draw(shape);
        player.setPosition(y, x);
        win.draw(player);
    }
    else if ( c == 'n' )
    {
        CircleShape shape(15.f);
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(y-6, x-6);
        win.draw(shape);
        music_off.setPosition(y, x);
        win.draw(music_off);
    }
    return 0;
}

int WindowGraphic::add_str(int x, int y, const char* s)
{
    sf::Text text{ s, font, 18 };
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(3.f);
    text.setPosition(y, x);
    win.draw(text);
    return 0;
}

int WindowGraphic::add_str_colour(int x, int y, const char* s, int colour)
{
    sf::Text text{ s, font, 18 };
    if(colour == 'r')
    {
        text.setFillColor(sf::Color::Red);
    }
     else if(colour == 'g')
    {
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::Green);
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(3.f);
    }
    else if(colour == 'w')
    {
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::White);
    }
    else if(colour == 'q') // game over case
    {
        /*RectangleShape rect{Vector2f(197, 60)};
        rect.setFillColor(Color::Black);
        rect.setPosition(y, x);
        win.draw(rect);*/

        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Red);
        text.setStyle(sf::Text::Bold);
        text.setPosition(y+10, x+10);
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(5.f);
        win.draw(text);
        return 0;
    }
    text.setPosition(y, x);
    win.draw(text);

    return 0;
}

int WindowGraphic::refresh()
{
    win.display();
    return 0;
}

void WindowGraphic::window_clear()
{
    win.clear();
    return;
}

void WindowGraphic::get_str(char* name, int i)
{
     return; //unused
}

void WindowGraphic::window_destroy()
{
    win.setVisible(false); //win.close();
}

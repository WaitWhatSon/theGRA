#include "WindowGraphic.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define X_SIZE 15
#define Y_SIZE 10


using namespace sf;

sf::Font font;


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
    CircleShape shape(5.f);

    if( c == 'r' )
    {
        shape.setFillColor(Color::Red);
        shape.setPosition(y, x);
    }
    else if ( c == 'b' )
    {
        shape.setFillColor(Color::Blue);
        shape.setPosition(y, x);
    }
    else if ( c == '@' )
    {
        shape.setFillColor(Color::Green);
        shape.setPosition(y, x);
    }
    else if ( c == '#' )
    {
        shape.setFillColor(Color::Yellow);
        shape.setPosition(y, x);
    }
    else
    {
        shape.setFillColor(Color::Magenta);
        shape.setPosition(y, x);
    }
    win.draw(shape);
    return 0;
}

int WindowGraphic::add_str(int x, int y, const char* s)
{
    sf::Text text{ "temp", font, 30 };
    text.setString(s);
    // set the color
    text.setFillColor(sf::Color::Red);
    // set the text style
    //text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition(y, x);
    // inside the main loop, between window.clear() and window.display()
    win.draw(text);
    return 0;
}

int WindowGraphic::add_str_colour(int x, int y, const char* s, int colour)
{
    CircleShape shape(20.f);
    shape.setFillColor(Color::Cyan);
    shape.setPosition(y, x);

    if(!win.isOpen())
    {
        exit(-1);
    }
    win.draw(shape);

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
     //unused
}

void WindowGraphic::window_destroy()
{
    win.setVisible(false);
    //win.close();
}

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

    //CircleShape shape(100.f);
    //shape.setFillColor(Color::Green);

    if(!win.isOpen())
    {
        exit(-1);
    }

    win.clear();
    //win.draw(shape);
    //win.display();

    if (!font.loadFromFile("files/open_sans/OpenSans-Regular.ttf"))
    {
        std::cout << "font not loaded";
    }

}

WindowGraphic::~WindowGraphic()
{
    //dtor
}

int WindowGraphic::get_ch()
{
    //return wgetch(this->win);

    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        return KEY_LEFT;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Right))
    {
        return KEY_RIGHT;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Up))
    {
        return KEY_UP;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Down))
    {
        return KEY_DOWN;
    }
    else if (Keyboard::isKeyPressed(Keyboard::X))
    {
        return 'x';
    }
    else if (Keyboard::isKeyPressed(Keyboard::W))
    {
        return 'w';
    }
    else if (Keyboard::isKeyPressed(Keyboard::S))
    {
        //return 's';
    }
    else if (Keyboard::isKeyPressed(Keyboard::M))
    {
        return 'm';
    }
    else if (Keyboard::isKeyPressed(Keyboard::Enter))
    {
        //return 10;
    }

    return 0;
}

int WindowGraphic::add_ch(int x, int y, char c)
{
    //wattron(this->win, COLOR_PAIR(CO_2));
    //return mvwaddch(this->win, x, y, c);
    //wattroff(this->win, COLOR_PAIR(CO_2));

    sf::Text text{ "Meeting C++ 2018", font, 10 };

    // set the string to display
    text.setString(c);

    // set the color
    text.setFillColor(sf::Color::Red);

    // set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    text.setPosition(y*Y_SIZE, x*X_SIZE);

    // inside the main loop, between window.clear() and window.display()
    win.draw(text);


    return 0;
}

int WindowGraphic::add_str(int x, int y, const char* s)
{
    //wattron(this->win, COLOR_PAIR(CO_2));
    //return mvwaddstr(this->win, x, y, s);
    //wattroff(this->win, COLOR_PAIR(CO_2));

    sf::Text text{ "Meeting C++ 2018", font, 10 };

    // set the string to display
    text.setString(s);

    // set the color
    text.setFillColor(sf::Color::Red);

    // set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    text.setPosition(y*Y_SIZE, x*X_SIZE);

    // inside the main loop, between window.clear() and window.display()
    win.draw(text);



    return 0;
}

int WindowGraphic::add_str_colour(int x, int y, const char* s, int colour)
{
    //wattron(this->win, COLOR_PAIR(colour));
    //return mvwaddstr(this->win, x, y, s);
    //wattroff(this->win, COLOR_PAIR(colour));

    CircleShape shape(20.f);
    shape.setFillColor(Color::Cyan);
    shape.setPosition(y*Y_SIZE, x*X_SIZE);

    if(!win.isOpen())
    {
        exit(-1);
    }

    win.draw(shape);
    win.display();

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
    win.display();

    return;
}

void WindowGraphic::get_str(char* name, int i)
{
     //wgetnstr(this->win, name, i);
}

void WindowGraphic::window_destroy()
{
    win.close();
}

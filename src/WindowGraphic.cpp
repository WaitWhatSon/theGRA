#include "WindowGraphic.h"


#define CO_1     1
#define CO_2     2
#define CO_3     3
#define CO_4     4
#define CO_5     5
#define CO_6     6



#define SFML_STATIC
#include <SFML/Graphics.hpp>


WindowGraphic::WindowGraphic()
{
    //ctor
    initscr();
    start_color();
    noecho();
    cbreak();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    sf::RenderWindow window(sf::VideoMode(yMax,xMax), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    init_pair(CO_1, COLOR_GREEN, COLOR_BLACK);
    init_pair(CO_2, COLOR_WHITE, COLOR_BLACK);
    init_pair(CO_3, COLOR_BLACK, COLOR_WHITE);
    init_pair(CO_4, COLOR_BLACK, COLOR_RED  );
    init_pair(CO_5, COLOR_BLACK, COLOR_GREEN);
    init_pair(CO_6, COLOR_WHITE, COLOR_RED  );
}

WindowGraphic::~WindowGraphic()
{
    //dtor
}

int WindowGraphic::get_ch()
{
    return wgetch(this->win);
}

int WindowGraphic::add_ch(int x, int y, char c)
{
    wattron(this->win, COLOR_PAIR(CO_2));
    return mvwaddch(this->win, x, y, c);
    wattroff(this->win, COLOR_PAIR(CO_2));
}

int WindowGraphic::add_str(int x, int y, const char* s)
{
    wattron(this->win, COLOR_PAIR(CO_2));
    return mvwaddstr(this->win, x, y, s);
    wattroff(this->win, COLOR_PAIR(CO_2));
}

int WindowGraphic::add_str_colour(int x, int y, const char* s, int colour)
{
    wattron(this->win, COLOR_PAIR(colour));
    return mvwaddstr(this->win, x, y, s);
    wattroff(this->win, COLOR_PAIR(colour));

}

int WindowGraphic::refresh()
{
    return wrefresh(win);
}

void WindowGraphic::window_clear()
{
    wclear(this->win);
    wrefresh(win);
}

void WindowGraphic::get_str(char* name, int i)
{
     wgetnstr(this->win, name, i);
}

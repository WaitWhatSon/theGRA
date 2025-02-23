#ifndef WINDOWGRAPHIC_H
#define WINDOWGRAPHIC_H

#include "Window.h"

#define SFML_STATIC
#include <SFML/Graphics.hpp>

#include <curses.h>
#include <clocale>
#include <string>
#include <stdio.h>

class WindowGraphic: public Window
{
    public:
        /** Default constructor */
        WindowGraphic();
        WindowGraphic(sf::RenderWindow& win);

        int get_ch();
        int add_ch(int x, int y, char c);
        int add_str(int x, int y, const char* s);
        int add_str_colour(int x, int y, const char* s, int colour);
        int refresh();
        void window_clear();
        void get_str(char* name, int i);
        void window_destroy();

        /** Default destructor */
        virtual ~WindowGraphic();

    protected:

    private:
        sf::RenderWindow& win;
};

#endif // WINDOWGRAPHIC_H

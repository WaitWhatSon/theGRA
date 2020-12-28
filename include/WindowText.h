#ifndef WINDOWTEXT_H
#define WINDOWTEXT_H

#include "Window.h"

#include <curses.h>
#include <clocale>
#include <string>
#include <stdio.h>

class WindowText: public Window
{
    public:
        /** Default constructor */
        WindowText();

        int get_ch();
        int add_ch(int x, int y, char c);
        int add_str(int x, int y, const char* s);
        int add_str_colour(int x, int y, const char* s, int colour);
        int refresh();
        void window_clear();
        void get_str(char* name, int i);
        void window_destroy();

        /** Default destructor */
        virtual ~WindowText();

    protected:

    private:
        WINDOW* win;
};

#endif // WINDOWTEXT_H

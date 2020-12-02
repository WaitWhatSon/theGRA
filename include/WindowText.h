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
        void const display_logo();
        void const display_options(int position, std::string best_player, int best_score);
        void const controls_display();
        void const display_quit();

        /** Default destructor */
        virtual ~WindowText();

    protected:

    private:
        WINDOW* win;
};

#endif // WINDOWTEXT_H

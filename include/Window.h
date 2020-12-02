#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <stdio.h>

class Window
{
    public:
        /** Default constructor */
        Window();
        /** Default destructor */
        virtual ~Window();

        virtual int get_ch();
        virtual int add_ch(int x, int y, char c);
        virtual int add_str(int x, int y, const char* s);
        virtual int add_str_colour(int x, int y, const char* s, int colour);
        virtual int refresh();
        virtual void window_clear();
        virtual void get_str(char* name, int i);
        virtual const void display_logo();
        virtual const void display_options(int position, std::string best_player, int best_score);
        virtual const void controls_display();
        virtual const void display_quit();

    protected:

    private:
};

#endif // WINDOW_H

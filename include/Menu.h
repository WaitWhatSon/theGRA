#ifndef MENU_H
#define MENU_H

#include <curses.h>
#include "Window.h"


class Menu
{
    private:
        int* mode;
        int* quit;
        int position;
        Window* win;

    public:
        /** Default constructor */
        Menu();
        Menu(Window* win, int* mode, int* quit);
        /** Default destructor */
        virtual ~Menu();

        void run_menu();
        int get_choice();
        void move_up();
        void move_down();
        void quit_game();

    protected:

    private:
};

#endif // MENU_H

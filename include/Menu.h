#ifndef MENU_H
#define MENU_H

#include <curses.h>
#include <string>
#include "Window.h"


class Menu
{
    private:
        int* mode;
        int* quit;
        int position;
        int loop;
        Window* win;
        std::string best_player;
        int best_score;

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
        void play_game();
        void change_mode();
        void controls_display();
        void update_best_player();

    protected:

    private:
};

#endif // MENU_H

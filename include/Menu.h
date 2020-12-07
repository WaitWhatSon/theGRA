#ifndef MENU_H
#define MENU_H

#include <fstream>
#include <string.h>

#include "Window.h"
#include "View.h"

class Menu
{
    public:
        int best_score;

        Menu();
        Menu(View*, int*, int*);
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
        int* mode;
        int* quit;
        int position;
        int loop;
        View* view;
        std::string best_player;
};

#endif // MENU_H

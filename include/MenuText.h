#ifndef MENUTEXT_H
#define MENUTEXT_H

#include <fstream>
#include <string.h>

#include "Menu.h"
#include "Window.h"
#include "View.h"

class MenuText : public Menu
{
    public:

        MenuText();
        MenuText(View*, int*, int*);
        virtual ~MenuText();
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

#endif // MENUTEXT_H

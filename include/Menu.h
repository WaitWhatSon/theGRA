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
        virtual void run_menu();

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

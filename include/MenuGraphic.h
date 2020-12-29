#ifndef MENUGRAPHIC_H
#define MENUGRAPHIC_H

#include <fstream>
#include <string.h>

#include "Menu.h"
#include "Window.h"
#include "View.h"

#define SFML_STATIC
#include <SFML/Graphics.hpp>

class MenuGraphic : public Menu
{
    public:

        MenuGraphic();
        MenuGraphic(View*, int*, int*);
        MenuGraphic(View*, int*, int*, sf::RenderWindow&);
        virtual ~MenuGraphic();
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

        sf::RenderWindow& win;
};

#endif // MENUGRAPHIC_H

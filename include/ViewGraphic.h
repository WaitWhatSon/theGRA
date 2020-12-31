#ifndef VIEWGRAPHIC_H
#define VIEWGRAPHIC_H

#include "View.h"
#include "Window.h"

#include "View.h"
#include "Window.h"

#include <curses.h>
#include <string>

class ViewGraphic: public View
{
    public:
        bool display_quit_var;
        /** Default constructor */
        ViewGraphic();
        ViewGraphic(Window*);
        void clockUpdate(char, char);
        void mapFragmentUpdate(int, int, char);
        void playerPositionUpdate(int, int, char);
        void gameBarUpdate(int, const char*, const char*, int, int);
        void gameBar();
        void gameOver();
        void playerNameChoice();
        void updatePlayerName(std::string name);
        void const display_quit();
        ///////////////
        void const display_logo();
        void const display_options(int position, std::string best_player, int best_score);
        void const controls_display();
        void const menu_move_up_clear(int);
        void const menu_move_up_draw(int);
        void const menu_move_down_clear(int);
        void const menu_move_down_draw(int);

        /** Default destructor */
        virtual ~ViewGraphic();

    protected:

    private:
};

#endif // VIEWGRAPHIC_H

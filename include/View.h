#ifndef VIEW_H
#define VIEW_H

#include <curses.h>
#include <string>
#include <stdio.h>

#include "Window.h"

class View
{
    public:
        Window* window;

        /** Default constructor */
        View();
        View(Window*);
        virtual void clockUpdate(char, char);
        virtual void mapFragmentUpdate(int, int, char);
        virtual void playerPositionUpdate(int, int, char);
        virtual void gameBarUpdate(int, const char*, const char*, int, int);
        virtual void gameBar();
        virtual void gameOver();
        virtual void playerNameChoice();
        virtual void updatePlayerName(std::string);
        virtual const void display_logo();
        virtual const void display_options(int position, std::string best_player, int best_score);
        virtual const void controls_display();
        virtual const void display_quit();

        /** Default destructor */
        virtual ~View();

    protected:

    private:

};

#endif // VIEW_H

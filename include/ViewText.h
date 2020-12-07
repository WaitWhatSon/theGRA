#ifndef VIEWTEXT_H
#define VIEWTEXT_H

#include "View.h"
#include "Window.h"

#include <curses.h>
#include <string>

class ViewText: public View
{
    public:
        /** Default constructor */
        ViewText();
        ViewText(Window*);
        void clockUpdate(char, char);
        void mapFragmentUpdate(int, int, char);
        void playerPositionUpdate(int, int, char);
        void gameBarUpdate(int, const char*, const char*, int, int);
        void gameBar();
        void gameOver();
        void playerNameChoice();
        void updatePlayerName(std::string name);
        void const display_logo();
        void const display_options(int position, std::string best_player, int best_score);
        void const controls_display();
        void const display_quit();

        /** Default destructor */
        virtual ~ViewText();

    protected:

    private:
};

#endif // VIEWTEXT_H

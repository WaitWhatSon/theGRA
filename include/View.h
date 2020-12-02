#ifndef VIEW_H
#define VIEW_H

#include <curses.h>
#include <string>

#include "Window.h"


class View
{
    public:
        /** Default constructor */
        View();
        virtual void test();
        virtual void clockUpdate(Window*, char, char);
        virtual void mapFragmentUpdate(Window*, int, int, char);
        virtual void playerPositionUpdate(Window*, int, int, char);
        virtual void gameBarUpdate(Window*, int, const char*, const char*, int, int);
        virtual void gameBar(Window*);
        virtual void gameOver(Window*);
        virtual void playerNameChoice(Window*);
        virtual void updatePlayerName(Window*, std::string);

        /** Default destructor */
        virtual ~View();

    protected:

    private:
};

#endif // VIEW_H

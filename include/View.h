#ifndef VIEW_H
#define VIEW_H
#include <curses.h>
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

        /** Default destructor */
        virtual ~View();

    protected:

    private:
};

#endif // VIEW_H

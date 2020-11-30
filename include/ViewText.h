#ifndef VIEWTEXT_H
#define VIEWTEXT_H
#include "View.h"
#include <curses.h>


class ViewText: public View
{
    public:
        /** Default constructor */
        ViewText();
        void clockUpdate(Window*, char, char);
        void mapFragmentUpdate(Window*, int, int, char);
        void playerPositionUpdate(Window*, int, int, char);

        void test();

        /** Default destructor */
        virtual ~ViewText();

    protected:

    private:
};

#endif // VIEWTEXT_H

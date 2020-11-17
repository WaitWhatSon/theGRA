#ifndef VIEWTEXT_H
#define VIEWTEXT_H
#include "View.h"
#include <curses.h>


class ViewText: public View
{
    public:
        /** Default constructor */
        ViewText();
        void clockUpdate(WINDOW*, char, char);
        void test();
        void mapFragmentUpdate(WINDOW*, int, int, char);
        void playerPositionUpdate(WINDOW*, int, int, char);

        /** Default destructor */
        virtual ~ViewText();

    protected:

    private:
};

#endif // VIEWTEXT_H

#ifndef VIEW_H
#define VIEW_H
#include <curses.h>


class View
{
    public:
        /** Default constructor */
        View();
        virtual void test();
        virtual void clockUpdate(WINDOW*, char, char);
        virtual void mapFragmentUpdate(WINDOW*, int, int, char);
        virtual void playerPositionUpdate(WINDOW*, int, int, char);
        virtual void mapDisplay();
        /** Default destructor */
        virtual ~View();

    protected:

    private:
};

#endif // VIEW_H

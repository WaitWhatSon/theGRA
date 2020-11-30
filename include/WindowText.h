#ifndef WINDOWTEXT_H
#define WINDOWTEXT_H
#include "Window.h"
#include <curses.h>
#include <clocale>

class WindowText: public Window
{
    public:
        /** Default constructor */
        WindowText();

        int get_ch();
        int add_ch(int x, int y, char c);
        int refresh();

        /** Default destructor */
        virtual ~WindowText();

    protected:

    private:
        WINDOW* win;
};

#endif // WINDOWTEXT_H

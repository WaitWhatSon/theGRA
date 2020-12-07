#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <stdio.h>

class Window
{
    public:
        /** Default constructor */
        Window();
        /** Default destructor */
        virtual ~Window();

        virtual int get_ch();
        virtual int add_ch(int x, int y, char c);
        virtual int add_str(int x, int y, const char* s);
        virtual int add_str_colour(int x, int y, const char* s, int colour);
        virtual int refresh();
        virtual void window_clear();
        virtual void get_str(char* name, int i);

    protected:

    private:
};

#endif // WINDOW_H

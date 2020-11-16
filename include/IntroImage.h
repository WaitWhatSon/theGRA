#ifndef INTROIMAGE_H
#define INTROIMAGE_H
#include <curses.h>

class IntroImage
{
    public:
        /** Default constructor */
        IntroImage();
        /** Default destructor */
        virtual ~IntroImage();
        void display(WINDOW*);

    protected:

    private:
};

#endif // INTROIMAGE_H

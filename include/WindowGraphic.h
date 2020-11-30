#ifndef WINDOWGRAPHIC_H
#define WINDOWGRAPHIC_H

#include <Window.h>


class WindowGraphic : public Window
{
    public:
        /** Default constructor */
        WindowGraphic();
        /** Default destructor */
        virtual ~WindowGraphic();

        int get_ch();
        int add_ch(int x, int y, char c);
        int refresh();

    protected:

    private:
};

#endif // WINDOWGRAPHIC_H

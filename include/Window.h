#ifndef WINDOW_H
#define WINDOW_H


class Window
{
    public:
        /** Default constructor */
        Window();
        /** Default destructor */
        virtual ~Window();

        virtual int get_ch();
        virtual int add_ch(int x, int y, char c);
        virtual int refresh();

    protected:

    private:
};

#endif // WINDOW_H

#include "WindowText.h"
#include <curses.h>

WindowText::WindowText()
{
    //ctor
    setlocale(LC_ALL, "Polish");
    initscr();
    noecho();
    cbreak();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    win = newwin(yMax,xMax,0,0);
    keypad(win, true);
    refresh();
    wrefresh(win);
}

WindowText::~WindowText()
{
    //dtor
}

int WindowText::get_ch()
{
    return wgetch(this->win);
}

int WindowText::add_ch(int x, int y, char c)
{
    return mvwaddch(this->win, x, y, c);
}

int WindowText::refresh()
{
    return wrefresh(win);
}

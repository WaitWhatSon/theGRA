#include "WindowText.h"

#define CO_1     1
#define CO_2     2
#define CO_3     3
#define CO_4     4
#define CO_5     5
#define CO_6     6

WindowText::WindowText()
{
    //ctor
    initscr();
    start_color();
    noecho();
    cbreak();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    this->win = newwin(yMax,xMax,0,0);
    // nazwe ikna i ikonke
    keypad(win, true);
    curs_set(0);
    refresh();
    wrefresh(win);

    init_pair(CO_1, COLOR_GREEN, COLOR_BLACK);
    init_pair(CO_2, COLOR_WHITE, COLOR_BLACK);
    init_pair(CO_3, COLOR_BLACK, COLOR_WHITE);
    init_pair(CO_4, COLOR_BLACK, COLOR_RED  );
    init_pair(CO_5, COLOR_BLACK, COLOR_GREEN);
    init_pair(CO_6, COLOR_WHITE, COLOR_RED  );
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
    wattron(this->win, COLOR_PAIR(CO_2));
    return mvwaddch(this->win, x, y, c);
    wattroff(this->win, COLOR_PAIR(CO_2));
}

int WindowText::add_str(int x, int y, const char* s)
{
    wattron(this->win, COLOR_PAIR(CO_2));
    return mvwaddstr(this->win, x, y, s);
    wattroff(this->win, COLOR_PAIR(CO_2));
}

int WindowText::add_str_colour(int x, int y, const char* s, int colour)
{
    wattron(this->win, COLOR_PAIR(colour));
    return mvwaddstr(this->win, x, y, s);
    wattroff(this->win, COLOR_PAIR(colour));

}

int WindowText::refresh()
{
    return wrefresh(win);
}

void WindowText::window_clear()
{
    wclear(this->win);
    wrefresh(win);
}

void WindowText::get_str(char* name, int i)
{
     wgetnstr(this->win, name, i);
}

void WindowText::window_destroy()
{
    endwin();
}

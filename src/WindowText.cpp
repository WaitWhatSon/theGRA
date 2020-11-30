#include "WindowText.h"
#include <curses.h>

#define CO_1     1
#define CO_2     2
#define CO_3     3

WindowText::WindowText()
{
    //ctor
    initscr();
    start_color();
    noecho();
    cbreak();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    win = newwin(yMax,xMax,0,0);
    keypad(win, true);
    curs_set(0);
    refresh();
    wrefresh(win);

    init_pair(CO_1, COLOR_GREEN, COLOR_BLACK);
    init_pair(CO_2, COLOR_WHITE, COLOR_BLACK);
    init_pair(CO_3, COLOR_BLACK, COLOR_WHITE);

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

const void WindowText::display_logo()
{
    this->add_str_colour(1, 16,    " ________ __            _______ _______ ____", 1);
    this->add_str_colour(2, 16,    "/__   __// /           / _____// ___  // _  |", 1);
    this->add_str_colour(3, 16,    "  /  /  / /__  _____  / / ___ / /__/_// /_| |", 1);
    this->add_str_colour(4, 16,    " /  /  / __  // '__/ / /__/ // ___ \\ / ___  |", 1);
    this->add_str_colour(5, 16,    "/__/  /_/ /_//____/ /______//_/  /_//_/   |_|", 1);
}

#include "WindowText.h"
#include <curses.h>

#define CO_1     1
#define CO_2     2
#define CO_3     3
#define CO_4     4

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
    init_pair(CO_4, COLOR_BLACK, COLOR_RED  );
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

const void WindowText::display_options(int position, std::string best_player, int best_score)
{
    this->add_str(8,  10, "(P) PLAY GAME");
    this->add_str(10, 10, "(M) SWITCH MODE");
    this->add_str(12, 10, "(C) CONTROLS");
    this->add_str(14, 10, "(X) EXIT");

    this->add_str_colour((8 + position*2), 8, ">", 1);

    this->display_logo();
    this->add_str_colour(6, 16, "-----------------> TheGRA <-----------------", 1);

    this->add_str_colour(9, 50, "--> BEST PLAYER <--", 1);

    this->add_str(11, 50, (best_player).c_str());
    const char * score = (std::to_string(best_score)).c_str();
    this->add_str(11, 50+15, score);
}

const void WindowText::controls_display()
{
    this->window_clear();

    this->add_str_colour(1,  26, "------> CONTROLS <------", 1);
    this->add_str_colour(3,  10, "--> PLAYER CONTROLS <--", 1);
    this->add_str_colour(5,  10, "move up", 1);
    this->add_str_colour(5,  28+3, "UP", 2);
    this->add_str_colour(6,  10, "move down", 1);
    this->add_str_colour(6,  28+1, "DOWN", 2);
    this->add_str_colour(7,  10, "move left", 1);
    this->add_str_colour(7,  28+1, "LEFT", 2);
    this->add_str_colour(8,  10, "move right", 1);
    this->add_str_colour(8,  28, "RIGHT", 2);
    this->add_str_colour(10, 10, "floor up", 1);
    this->add_str_colour(10, 28+4, "W", 2);
    this->add_str_colour(11, 10, "floor down", 1);
    this->add_str_colour(11, 28+4, "S", 2);
    this->add_str_colour(12, 10, "admit", 1);
    this->add_str_colour(12, 28+4, "A", 2);
    this->add_str_colour(14, 30, "back to menu", 1);
    this->add_str_colour(14, 45, "X", 2);

}

const void WindowText::display_quit()
{
    this->add_str(16,  9, "Are you sure you want to exit PB?");
    this->add_str_colour(16,  43, "(press X if you are sure)", 1);
}

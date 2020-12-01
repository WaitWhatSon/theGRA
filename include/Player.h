#ifndef PLAYER_H
#define PLAYER_H

#include "Window.h"

#include <stdio.h>
#include <curses.h>

class Player
{
    private:
        int x, y, old_x, old_y, width, height;
        char character;
        Window * win;
        char** current_map;

        void update_xy();
        void move_up();
        void move_down();
        void move_left();
        void move_right();
        void next_floor();
        void prev_floor();

    public:
        Player (Window * _win, int _yc, int _xc, char _c, char** _cmap);
        bool check_if_not_wall(char character);
        void check_if_change_map(int next_x, int next_y);
        bool check_if_not_exit(int next_x, int next_y);
        int get_move();
        int get_x();
        int get_old_x();
        int get_y();
        int get_old_y();
        void set_current_map(char** cmap);
        ~Player();
};

#endif // PLAYER_H

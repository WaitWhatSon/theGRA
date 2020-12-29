#ifndef PLAYER_H
#define PLAYER_H

#include "Window.h"
#include "View.h"

#include <stdio.h>
#include <curses.h>
#include <iostream>
#include <string>
#include <cstring>

class Player
{
    private:
        int x, y, old_x, old_y, width, height;
        char character;
        Window * win;
        View* view;
        char** current_map;
        std::string player_name;
        int player_score;

        int* goal_x;
        int* goal_y;
        int* goal_map;
        int* current_flor;

    public:
        bool goal;

        Player (View* _view, int _yc, int _xc, char _c, char** _cmap,
                int* _goal_x, int* _goal_y, int* _goal_map, int* _current_flor);
        bool check_if_not_wall(char character);
        void check_if_change_map(int next_x, int next_y);
        bool check_if_not_exit(int next_x, int next_y);
        int get_move();
        int get_x();
        int get_old_x();
        int get_y();
        int get_old_y();
        void add_points(int points);
        int get_player_score();
        void set_name(std::string name);
        std::string get_player_name();
        void set_current_map(char** cmap);
        void check_position();

        void update_xy();
        void move_up();
        void move_down();
        void move_left();
        void move_right();
        void next_floor();
        void prev_floor();

        ~Player();
};

#endif // PLAYER_H

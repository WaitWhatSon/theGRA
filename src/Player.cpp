#include "Player.h"
#include "View.h"
#include "Game.h"
#include <stdio.h>
#include <curses.h>
#include <iostream>

#include "Window.h"

Player::Player (Window * _win, int _yc, int _xc, char _c, char** _cmap)
{
    win = _win;
    y = _yc;
    x = _xc;
    old_y = _yc;
    old_x = _xc;
    character = _c;
    current_map = _cmap;
}

bool Player::check_if_not_wall(char character)
{
    if (character == '#')
        return false;
    else
        return true;
}

void Player::check_if_change_map(int next_x, int next_y)
{
    if (next_x == -1)
    {
        Game::map_changed = true;
        Game::current_map = Game::map_change_array[Game::current_map][3];

        x = 76;
    }
    else if (next_x == 77)
    {
        Game::map_changed = true;
        Game::current_map = Game::map_change_array[Game::current_map][1];

        x = 0;
    }
    else if (next_y == -1)
    {
        Game::map_changed = true;
        Game::current_map = Game::map_change_array[Game::current_map][0];

        y = 14;
    }
    else if (next_y == 15)
    {
        Game::map_changed = true;
        Game::current_map = Game::map_change_array[Game::current_map][2];

        y = 0;
    }
}

void Player::move_up()
{
    check_if_change_map(x, y-1);
    if(check_if_not_wall(current_map[y-1][x]))
    {
        update_xy();
        y -= 1;
    }
}

void Player::move_down()
{
    check_if_change_map(x, y+1);
    if(check_if_not_wall(current_map[y+1][x]))
    {
        update_xy();
        y += 1;
    }
}

void Player::move_left()
{
    check_if_change_map(x-1, y);
    if(check_if_not_wall(current_map[y][x-1]))
    {
        update_xy();
        x -= 1;
    }
}

void Player::move_right()
{
    check_if_change_map(x+1, y);
    if(check_if_not_wall(current_map[y][x+1]))
    {
        update_xy();
        x += 1;
    }
}

void Player::next_floor()
{
    if ((x == 8 && y == 7) || (x == 61 && y == 11 ))
    {
        int new_map;
        if (Game::current_map == 4) // niski parter
        {
            new_map = 0;
        }
        else if (Game::current_map == 0) // parter
        {
            new_map = 6;
        }
        else if (Game::current_map == 6) // pierwsze pietro
        {
            new_map = 8;
        }
        else
        {
            return;
        }
        Game::map_changed = true;
        Game::current_map = new_map;
    }
}

void Player::prev_floor()
{
    if ((x == 10 && y == 7) || (x == 63 && y == 11 ))
    {
        int new_map;
        if (Game::current_map == 0) // parter
        {
            new_map = 4;
        }
        else if (Game::current_map == 6) // pierwsze pietro
        {
            new_map = 0;
        }
        else if (Game::current_map == 8) // drugie pietro
        {
            new_map = 6;
        }
        else
        {
            return;
        }
        Game::map_changed = true;
        Game::current_map = new_map;
    }
}

int Player::get_move()
{
    int choice = win->get_ch();
    switch(choice)
    {
        case KEY_UP:
            move_up();
            break;
        case KEY_DOWN:
            move_down();
            break;
        case KEY_LEFT:
            move_left();
            break;
        case KEY_RIGHT:
            move_right();
            break;
        case 'w':     //
            next_floor();
            break;
        case 's':     //
            prev_floor();
            break;
        default:
            break;
    }
    return choice;
}

int Player::get_x()
{
    return x;
}

int Player::get_old_x()
{
    return old_x;
}

int Player::get_y()
{
    return y;
}

int Player::get_old_y()
{
    return old_y;
}

void Player::update_xy()
{
    old_x = x;
    old_y = y;
}

void Player::set_current_map(char** cmap)
{
    current_map = cmap;
}

Player::~Player()
{
        //dtor
}



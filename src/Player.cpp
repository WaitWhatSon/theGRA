#include "Player.h"
#include "View.h"
#include "Game.h"
#include <stdio.h>
#include <curses.h>
#include <iostream>

Player::Player (WINDOW * win, int yc, int xc, char c, char** cmap)
{
    curwin = win;
    y = yc;
    x = xc;
    old_y = yc;
    old_x = xc;
    getmaxyx(curwin, height, width);
    keypad(curwin, true);
    character = c;
    current_map = cmap;
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
        std::cout << "elo x < 0";
        Game::map_changed = true;
        Game::current_map = Game::map_change_array[Game::current_map][3];

        x = 76;
    }
    else if (next_x == 77)
    {
        std::cout << "elo x > 0";
        Game::map_changed = true;
        Game::current_map = Game::map_change_array[Game::current_map][1];

        x = 0;
    }
    else if (next_y == -1)
    {
        std::cout << "elo y < 0";
        Game::map_changed = true;
        Game::current_map = Game::map_change_array[Game::current_map][0];

        y = 14;
    }
    else if (next_y == 15)
    {
        std::cout << "elo y > 0";
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

int Player::get_move()
{
    int choice = wgetch(curwin);
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



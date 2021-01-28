#include <SFML/Audio.hpp>

#include "Player.h"
#include "Game.h"

#include "Common.h"

sf::SoundBuffer buffer_player;
sf::Sound step;

sf::SoundBuffer buffer2_player;
sf::Sound not_step;

sf::SoundBuffer buffer3_player;
sf::Sound point;

Player::Player (View* _view, int _yc, int _xc, char _c, char** _cmap,
                int* _goal_x, int* _goal_y, int* _goal_map, int* _flor)
{
    view = _view;
    win = view->window;
    y = _yc;
    x = _xc;
    old_y = _yc;
    old_x = _xc;
    character = _c;
    current_map = _cmap;

    player_name = " ";
    player_score = 0;

    goal_x = _goal_x;
    goal_y = _goal_y;
    goal_map = _goal_map;
    current_flor = _flor;

    goal = false;

    if (!buffer_player.loadFromFile("files/music/step.wav"))
        exit -1;
    step.setBuffer(buffer_player);

    if (!buffer2_player.loadFromFile("files/music/not_step.wav"))
        exit -1;
    not_step.setBuffer(buffer2_player);

    if (!buffer3_player.loadFromFile("files/music/good.wav"))
        exit -1;
    point.setBuffer(buffer3_player);
}

bool Player::check_if_not_wall(char character)
{
    if (character == '#')
    {
        if(music_on)not_step.play();
        return false;
    }
    else
    {
        if(music_on)step.play();
        return true;
    }
}

void Player::check_if_change_map(int next_x, int next_y)
{
    if (next_x == -1)
    {
        Game::map_changed = true;
        *current_flor = Game::map_change_array[*current_flor][3];
        x = 76;
    }
    else if (next_x == 77)
    {
        Game::map_changed = true;
        *current_flor = Game::map_change_array[*current_flor][1];
        x = 0;
    }
    else if (next_y == -1)
    {
        Game::map_changed = true;
        *current_flor = Game::map_change_array[*current_flor][0];
        y = 14;
    }
    else if (next_y == 15)
    {
        Game::map_changed = true;
        *current_flor = Game::map_change_array[*current_flor][2];
        y = 0;
    }
}

bool Player::check_if_not_exit(int next_x, int next_y)
{
    if (next_x == -1)
    {
        if (Game::map_change_array[*current_flor][3] == -1)
        {
            this->view->display_quit();
            this->view->display_quit_var = true;
            return true;
        }
    }
    else if (next_x == 77)
    {
        if (Game::map_change_array[*current_flor][1] == -1)
        {
            this->view->display_quit();
            this->view->display_quit_var = true;
            return true;
        }
    }
    else if (next_y == -1)
    {
        if (Game::map_change_array[*current_flor][0] == -1)
        {
            this->view->display_quit();
            this->view->display_quit_var = true;
            return true;
        }
    }
    else if (next_y == 15)
    {
        if (Game::map_change_array[*current_flor][2] == -1)
        {
            this->view->display_quit();
            this->view->display_quit_var = true;
            return true;
        }
    }
    return false;
}

void Player::move_up()
{
    if(!check_if_not_exit(x, y-1))
    {
        check_if_change_map(x, y-1);
        if(check_if_not_wall(current_map[y-1][x]))
        {
            update_xy();
            y -= 1;
        }
    }
}

void Player::move_down()
{
    if (!check_if_not_exit(x, y+1))
    {
        check_if_change_map(x, y+1);
        if(check_if_not_wall(current_map[y+1][x]))
        {
            update_xy();
            y += 1;
        }
    }
}

void Player::move_left()
{
    if (!check_if_not_exit(x-1, y))
    {
        check_if_change_map(x-1, y);
        if(check_if_not_wall(current_map[y][x-1]))
        {
            update_xy();
            x -= 1;
        }
    }
}

void Player::move_right()
{
    if (!check_if_not_exit(x+1, y))
    {
        check_if_change_map(x+1, y);
        if(check_if_not_wall(current_map[y][x+1]))
        {
            update_xy();
            x += 1;
        }
    }
}

void Player::next_floor()
{
    if ((x == 8 && y == 7) || (x == 61 && y == 11 ))
    {
        int new_map;
        if (*current_flor == 4) // niski parter
        {
            new_map = 0;
        }
        else if (*current_flor == 0) // parter
        {
            new_map = 6;
        }
        else if (*current_flor == 6) // pierwsze pietro
        {
            new_map = 8;
        }
        else
        {
            return;
        }
        Game::map_changed = true;
        *current_flor = new_map;
    }
}

void Player::prev_floor()
{
    if ((x == 10 && y == 7) || (x == 63 && y == 11 ))
    {
        int new_map;
        if (*current_flor == 0) // parter
        {
            new_map = 4;
        }
        else if (*current_flor == 6) // pierwsze pietro
        {
            new_map = 0;
        }
        else if (*current_flor == 8) // drugie pietro
        {
            new_map = 6;
        }
        else
        {
            return;
        }
        Game::map_changed = true;
        *current_flor = new_map;
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
        case 'a':     //
            check_position();
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

void Player::add_points(int points)
{
    this->player_score += points;
    if(music_on)point.play();
}

int Player::get_player_score()
{
    return this->player_score;
}

std::string Player::get_player_name()
{
    return this->player_name;
}

void Player::check_position()
{
    if (*(this->goal_map) == *(this->current_flor) && *(this->goal_x) == (this->x) && *(this->goal_y) == (this->y))
    {
        this->goal = true;
    }
    else
    {
        this->goal = false;
    }
}

void Player::set_name(std::string _name)
{
    this->player_name = _name;
}

Player::~Player()
{
        //dtor
}



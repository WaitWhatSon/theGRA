#include <curses.h>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <clocale>

#include "Game.h"
#include "Player.h"
#include "MapsLoader.h"
#include "IntroImage.h"

void foo(View* view, Window* window)
{
    for (int i = 0; i < 0; i++)
    {
        for  (int j = 0; j < 1; j++)
        {
            usleep(1000000); // czekaj sekunde
            view->clockUpdate(window, i+48, j+48); // aktualizuj zegar
        }
    }
}

int Game::current_map = 0;
bool Game::map_changed = false;
const int Game::map_change_array[10][4];
const int Game::rooms_coordinates[13][4];

Game::Game(View* view_pointer, Window* window)
{
    view = view_pointer; // załadowanie widoku

    // miejsce na mapy init
    maps = new char**[10]; //to ca³e robi tablicê na mapy

    for (int i = 0; i < 10; i++)         // dla kazdej mapy
	{
		maps[i] = new char*[15];           // 15 znaczków pionowo - alokacja
		for (int j = 0; j < 15; j++)    // iteracja -> dla ka¿dego z 15 rzêdów
			{
			    maps[i][j] = new char[77]; // 77 znaczków poziomo
			}
	}

	gameWindow = window;
}

void Game::setup_window()
{
    this->gameWindow->refresh();
    //wrefresh(gameWindow);

    player = new Player(gameWindow, 14, 18, '@', maps[current_map]); // okno, x, y, znak, wskaznik do map
    loader = new MapsLoader();

    loader->load_maps(maps);

    load_current_map();
}

void Game::play_game()
{
    std::thread thread_obj(foo, view, gameWindow);
    while(player->get_move()!='x')
    {
        if (map_changed)
        {
            load_current_map();
            map_changed = false;
        }

        view->mapFragmentUpdate(gameWindow, player->get_old_x(), player->get_old_y(),
                                maps[current_map][player->get_old_y()][player->get_old_x()]);
        view->playerPositionUpdate(gameWindow, player->get_x(), player->get_y(), '@');
        this->gameWindow->refresh();

    }
    thread_obj.join();
    endwin();
}

void Game::load_current_map()
{
    for (int i = 0; i<15; i++)
    {
        for (int j = 0; j<77; j++)
        {
            view->mapFragmentUpdate(gameWindow, j, i, maps[current_map][i][j]);
            player->set_current_map(maps[current_map]);
        }
    }
    for (int i = 0; i<13; i++)
    {
        if (current_map == this->rooms_coordinates[i][1])
        {
            view->mapFragmentUpdate(gameWindow, rooms_coordinates[i][2], rooms_coordinates[i][3], '*');
        }
    }
    view->playerPositionUpdate(gameWindow, player->get_x(), player->get_y(), '@');
    this->gameWindow->refresh();
}

Game::~Game()
{
    //dtor
}

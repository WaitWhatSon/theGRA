#include <curses.h>
#include "Game.h"
#include "Player.h"
#include "MapsLoader.h"

#include <iostream>

int Game::current_map = 0;
bool Game::map_changed = false;
const int Game::map_change_array[10][4];

Game::Game(View* view_pointer)
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
}

void Game::create_window()
{
    initscr();
    noecho();
    cbreak();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    gameWindow = newwin(yMax,xMax,0,0);
    refresh();
    wrefresh(gameWindow);

    player = new Player(gameWindow, 14, 18, '@', maps[current_map]); // okno, x, y, znak, wskaznik do map
    loader = new MapsLoader();

    loader->load_maps(maps);

    load_current_map();
}

void Game::play_game()
{
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
        wrefresh(gameWindow);

    }
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
    view->playerPositionUpdate(gameWindow, player->get_x(), player->get_y(), '@');
    wrefresh(gameWindow);
    std::cout << std::endl << "current map " << current_map << std::endl;
}

Game::~Game()
{
    //dtor
}

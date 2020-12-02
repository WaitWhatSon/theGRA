#include <curses.h>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <clocale>
#include <atomic>
#include <vector>
#include <string>
#include <fstream>

#include "Game.h"
#include "Player.h"
#include "MapsLoader.h"
#include "IntroImage.h"
#include "CoursesList.h"

std::atomic<bool> x (1);
std::atomic<bool> restart_clock (1);

void foo(View* view, Window* window)
{
    for (int i = 160; i >= 0; i--)
    {
        usleep(100000);
        view->clockUpdate(window, (i/100)+48, ((i/10)%10)+48); // aktualizuj zegar
        if(!x)
        {
            view->clockUpdate(window, 0+48, 0+48);
            return;
        }
        if (restart_clock)
        {
            i = 150;
            restart_clock = false;
        }
    }
    view->clockUpdate(window, 0+48, 0+48);
    view->gameOver(window);
    window->refresh();
    x = false;
}

bool Game::map_changed = false;
const int Game::map_change_array[10][4];
const int Game::rooms_coordinates[13][4];

Game::Game(View* view_pointer, Window* window, int _best_score)
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
	current_map = 0;
	allCourses = new CoursesList();
	this->best_score = _best_score;

	x = true;
}

void Game::choose_player_name()
{
    gameWindow->window_clear();
    view->playerNameChoice(gameWindow);

    int choice = '.';
    std::string temp_name = "PLAYER";
    view->updatePlayerName(gameWindow, temp_name);

    while (choice != '\n' || temp_name.empty())
    {
        choice = gameWindow->get_ch();
        if (temp_name.size() < 10)
        {
            if (choice >= ' ' && choice <= '{' && choice != '\\' && choice != ' ')
            {
                temp_name += choice;
                view->updatePlayerName(gameWindow, temp_name);
            }
        }
        if (choice == 8)
        {
            temp_name = temp_name.substr(0, temp_name.size()-1);
            view->updatePlayerName(gameWindow, temp_name);
        }

    }

    player->set_name(temp_name);
}

void Game::setup_window()
{
    this->gameWindow->refresh();
    //wrefresh(gameWindow);

    player = new Player(gameWindow, 14, 18, '@', maps[current_map],
                        &goal_x, &goal_y, &goal_map, &current_map); // okno, x, y, znak, wskaznik do map

    choose_player_name();

    loader = new MapsLoader();

    loader->load_maps(maps);

    load_current_map();
}

void Game::play_game()
{
    std::thread thread_clock(foo, view, gameWindow);
    view->gameBar(gameWindow);

    // variables for game //
    bool sth_changed = true;
    int semester = 1;
    int week = 1;
    int course = -1;
    vector<Course> courses;
    courses = allCourses->get_random_courses_list(semester);
    // ------------------ //

    while(x)
    {
        if(sth_changed)
        {
            course++;
            if (course >= courses.size())
            {
                courses = allCourses->get_random_courses_list(semester);
                course = 0;
                week++;
                if (week > 15)
                {
                    week = 1;
                    semester++;
                    if (semester > 5)
                    {
                        // GAME OVER
                        x = false;
                    }
                }
            }

            for (int i = 0; i < 13; i++)
            {
                if (Game::rooms_coordinates[i][0] == courses[course].get_room())
                {
                    goal_map = Game::rooms_coordinates[i][1];
                    goal_x = Game::rooms_coordinates[i][2];
                    goal_y = Game::rooms_coordinates[i][3];
                }
            }

            view->gameBarUpdate(gameWindow, semester, courses[course].get_name().c_str(),
                                to_string(courses[course].get_room()).c_str(),
                                week, player->get_player_score());
            sth_changed = false;
        }

        int player_choice = player->get_move();
        if (player_choice == 'x')
        {
            x = false;
        }

        if (map_changed)
        {
            load_current_map();
            map_changed = false;
        }

        if (player->goal)
        {
            add_points(1, &sth_changed);
            restart_clock = true;
            player->goal = false;
        }

        view->mapFragmentUpdate(gameWindow, player->get_old_x(), player->get_old_y(),
                                maps[current_map][player->get_old_y()][player->get_old_x()]);
        view->playerPositionUpdate(gameWindow, player->get_x(), player->get_y(), '@');
        //this->gameWindow->refresh();

    }
    thread_clock.join();

    // jeśli wynik większy niż w pliku to nadpisać
    if (best_score < player->get_player_score())
    {
        std::ofstream file( "files/best_player.txt", ios::out | ios::trunc );
        if( !file )
            exit(-1);

        file << player->get_player_name() << ' ' << player->get_player_score();

        file.close();
    }
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

void Game::add_points(int points, bool* sth_changed)
{
    // do zrobienia sposob przyznawania punktów
    this->player->add_points(points);
    *sth_changed = true;
}

Game::~Game()
{
    //dtor
}

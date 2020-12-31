#include "Game.h"

std::atomic<bool> x (1);
std::atomic<bool> restart_clock (1);

std::atomic<int> decSecG (1);
std::atomic<int> secG (1);

// tekstury tła //
sf::Texture background_texture;
sf::Sprite background;
// tekstury map //
sf::Texture maps_textures[10];
sf::Sprite map_sprite;

int mode;

void fooTimer(View* view, Window* window)
{
    for (int i = 160; i >= 0; i--)
    {
        usleep(100000);
        decSecG = i/100;
        secG = (i/10)%10;

        if(!mode) view->clockUpdate(decSecG+48, secG+48); // aktualizuj zegar
        if(!x)
        {
            if(!mode) view->clockUpdate(0+48, 0+48);
            return;
        }
        if (restart_clock)
        {
            i = 150;
            restart_clock = false;
        }
    }
    if(!mode)
    {
        view->clockUpdate(0+48, 0+48);
        view->gameOver();
    }
    x = false;
}

bool Game::map_changed = false;
const int Game::map_change_array[10][4];
const int Game::rooms_coordinates[13][4];

Game::Game(View* view_pointer, int _best_score, sf::RenderWindow& win, int _mode):win(win)
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
	gameWindow = view->window;
	current_map = 0;
	allCourses = new CoursesList();
	this->best_score = _best_score;
	mode = _mode;
	x = true;

    if(mode == 1)
    {
        load_maps_graphic();
    }
}

void Game::choose_player_name()
{
    gameWindow->window_clear();
    view->playerNameChoice();

    int choice = '.';
    std::string temp_name = "";
    view->updatePlayerName(temp_name);

    if(mode == 0)   /** TEKSTOWY **/
    {
        while (choice != '\n' || temp_name.empty())
        {
            choice = gameWindow->get_ch();
            if (temp_name.size() < 10)
            {
                if (choice >= ' ' && choice <= '{' && choice != '\\' && choice != ' ')
                {
                    temp_name += choice;
                    view->updatePlayerName(temp_name);
                }
            }
            if (choice == 8)
            {
                temp_name = temp_name.substr(0, temp_name.size()-1);
                view->updatePlayerName(temp_name);
            }
        }
    }
    else    /** GRAFICZNY **/
    {
        if (!background_texture.loadFromFile("files/background_photo.png")) exit -1;
        background.setTexture(background_texture);
        while (this->win.isOpen())
        {
            // check all the window's events that were triggered since the last iteration of the loop
            sf::Event event;
            while (this->win.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    this->win.close();
                }
                else if(event.type == sf::Event::KeyPressed)
                {
                    if(event.key.code == sf::Keyboard::Backspace)
                    {
                        temp_name = temp_name.substr(0, temp_name.size()-1);
                    }
                    else if(event.key.code == sf::Keyboard::Enter)
                    {
                        if(!temp_name.empty())
                        {
                            player->set_name(temp_name);
                            return;
                        }
                    }
                }
                else if (event.type == sf::Event::TextEntered)
                {
                    if (event.text.unicode < 128)
                    choice = event.text.unicode;

                    if (temp_name.size() < 10)
                    {
                        if (choice >= ' ' && choice <= '{' && choice != '\\' && choice != ' ')
                        {
                            temp_name += choice;
                        }
                    }
                }
            }
            // clear the window with black color
            this->win.clear(sf::Color::Black);
            this->win.draw(background);
            view->playerNameChoice();
            view->updatePlayerName(temp_name);
            this->win.display();
        }
    }
}

void Game::setup_window()
{
    this->gameWindow->refresh();

    player = new Player(view, 14, 18, '@', maps[current_map],
                        &goal_x, &goal_y, &goal_map, &current_map); // okno, x, y, znak, wskaznik do map

    choose_player_name();

    loader = new MapsLoader();

    loader->load_maps(maps);

    load_current_map();
}

void Game::play_game()
{
    std::thread thread_clock(fooTimer, view, gameWindow);
    view->gameBar();

    // variables for game //
    bool sth_changed = true;
    int semester = 1;
    int week = 1;
    int course = -1;
    vector<Course> courses;
    courses = allCourses->get_random_courses_list(semester);
    // ------------------ //
    if(mode==0) /** TEKSTOWY **/
    {
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

                view->gameBarUpdate(semester, courses[course].get_name().c_str(),
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

            view->mapFragmentUpdate(player->get_old_x(), player->get_old_y(),
                                    maps[current_map][player->get_old_y()][player->get_old_x()]);
            view->playerPositionUpdate(player->get_x(), player->get_y(), '@');
        }
    }
    else /** GRAFICZNY **/
    {
        while (this->win.isOpen() && x)
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
                sth_changed = false;
            }

            // check all the window's events that were triggered since the last iteration of the loop
            sf::Event event;
            while (this->win.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                this->win.close();
                }
                else if(event.type == sf::Event::KeyPressed)
                {
                    if     (event.key.code == sf::Keyboard::Up)     this->player->move_up();
                    else if(event.key.code == sf::Keyboard::Down)   this->player->move_down();
                    else if(event.key.code == sf::Keyboard::Left)   this->player->move_left();
                    else if(event.key.code == sf::Keyboard::Right)  this->player->move_right();
                    else if(event.key.code == sf::Keyboard::W) this->player->next_floor();
                    else if(event.key.code == sf::Keyboard::S) this->player->prev_floor();
                    else if(event.key.code == sf::Keyboard::A) this->player->check_position();
                    else if(event.key.code == sf::Keyboard::X) x = false;
                }
            }
            if (map_changed)
            {
                load_current_map();
                map_sprite.setTexture(maps_textures[current_map]);
                map_changed = false;
            }
            if (player->goal)
            {
                add_points(1, &sth_changed);
                restart_clock = true;
                player->goal = false;
            }
            // clear the window with black color
            this->win.clear(sf::Color::Black);
            // draw game
            this->win.draw(map_sprite);
            view->gameBarUpdate(semester, courses[course].get_name().c_str(),
                 to_string(courses[course].get_room()).c_str(),week, player->get_player_score());
            view->playerPositionUpdate(player->get_x(), player->get_y(), '@');
            if(this->view->display_quit_var) {view->display_quit();}
            view->clockUpdate(decSecG, secG);
            // display
            this->win.display();
        }
        x = 1;
        // wyrysowanie tła do gameover
        this->win.clear(sf::Color::Black);
        // draw game
        this->win.draw(map_sprite);
        view->gameBarUpdate(semester, courses[course].get_name().c_str(),
                 to_string(courses[course].get_room()).c_str(),week, player->get_player_score());
        view->playerPositionUpdate(player->get_x(), player->get_y(), '@');
        if(this->view->display_quit_var) {view->display_quit();}
        this->view->gameOver();
        // display
        this->win.display();
        while (this->win.isOpen() && x)
        {
            // check all the window's events that were triggered since the last iteration of the loop
            sf::Event event;
            while (this->win.pollEvent(event))
            {
                if (event.type == sf::Event::Closed){this->win.close();}
                else if(event.type == sf::Event::KeyPressed){ x=0; }
            }
        }
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
            view->mapFragmentUpdate(j, i, maps[current_map][i][j]);
            player->set_current_map(maps[current_map]);
        }
    }
    for (int i = 0; i<13; i++)
    {
        if (current_map == this->rooms_coordinates[i][1])
        {
            view->mapFragmentUpdate(rooms_coordinates[i][2], rooms_coordinates[i][3], '*');
        }
    }
    view->playerPositionUpdate(player->get_x(), player->get_y(), '@');
    this->gameWindow->refresh();
}

void Game::add_points(int points, bool* sth_changed)
{
    this->player->add_points(points);
    *sth_changed = true;
}

Game::~Game()
{
    //dtor
}

// do trybu graficznego //
void Game::load_maps_graphic()
{
    char* map_names[] = {   "files/maps_graphic/mapA.png",     "files/maps_graphic/mapB.png",
                            "files/maps_graphic/mapC1.png",    "files/maps_graphic/mapC2.png",
                            "files/maps_graphic/mapAP0_1.png", "files/maps_graphic/mapAP0_2.png",
                            "files/maps_graphic/mapAP1_1.png", "files/maps_graphic/mapAP1_2.png",
                            "files/maps_graphic/mapAP2_1.png", "files/maps_graphic/mapAP2_2.png"};

    for (int i=0; i<10; i++)
    {
        maps_textures[i].loadFromFile(map_names[i]);
    }
    map_sprite.setTexture(maps_textures[0]);
    map_sprite.setPosition(10, 10);
}

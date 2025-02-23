#include <windows.h>

#include "Menu.h"
#include "MenuText.h"
#include "MenuGraphic.h"

#include "Game.h"

#include "Window.h"
#include "WindowText.h"
#include "WindowGraphic.h"

#include "View.h"
#include "ViewText.h"
#include "ViewGraphic.h"

#include "Common.h"

using namespace std;

bool music_on;

int main()
{
    int mode = 0;
    // tryb: 0 -> tekstowy, 1 -> graficzny
    int quit = 0;
    // 0 -> graj, 1-> wylacz

    music_on = true;

    Window* window_pointer; // okno
    View* view_pointer;     // widok
    Menu* menu;             // meni

    //ikonka
    sf::Image image;
    image.loadFromFile( "files/player.png" );

    SetConsoleTitle("TheGRA");


    sf::RenderWindow window(sf::VideoMode(713,400), "TheGRA");
    window.setIcon( image.getSize().x, image.getSize().y, image.getPixelsPtr() );
    window.setVisible(false);

    int old_mode = mode;

    while (!quit)   // nie wylaczono gry
    {
        /** TRYB TEKSTOWY **/
        if ( mode == 0 )
        {
            window_pointer = new WindowText();
            view_pointer = new ViewText(window_pointer);
            menu = new MenuText(view_pointer, &mode, &quit);
        }
        /** TRYB GRAFICZNY **/
        else
        {
            window_pointer = new WindowGraphic(window);
            view_pointer = new ViewGraphic(window_pointer);
            menu = new MenuGraphic(view_pointer, &mode, &quit, window);
        }

        menu->run_menu();

        if (!quit && old_mode==mode)  // nie wylaczono gry w meni
        {
            Game* game = new Game(view_pointer, menu->best_score, window, mode);
            game->setup_window();   // ustawienie okna
            game->play_game();      // gra
        }

        if (old_mode!=mode)
        {
            view_pointer->window->window_destroy();
        }

        old_mode = mode;
    }

    cout << "SEE YOU LATER!\n";
    cout << "\npodziekowania dla Krystka za pomoc w przerysowaniu map.";
}


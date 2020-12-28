#include "Menu.h"
#include "Game.h"

#include "Window.h"
#include "WindowText.h"
#include "WindowGraphic.h"

#include "View.h"
#include "ViewText.h"
#include "ViewGraphic.h"


using namespace std;

int main()
{
    int mode = 0;
    // tryb: 0 -> tekstowy, 1 -> graficzny
    int quit = 0;
    // 0 -> graj, 1-> wylacz

    Window* window_pointer; // okno
    View* view_pointer;     // widok
    Menu* menu;             // meni

    sf::RenderWindow window(sf::VideoMode(700,300), "TheGRA");
    window.setVisible(false);

    int old_mode = mode;

    while (!quit)   // nie wylaczono gry
    {
        /** TRYB TEKSTOWY **/
        if ( mode == 0 )
        {
            window_pointer = new WindowText();
            view_pointer = new ViewText(window_pointer);
        }
        /** TRYB GRAFICZNY **/
        else
        {
            window_pointer = new WindowGraphic(window);
            view_pointer = new ViewGraphic(window_pointer);
        }

        menu = new Menu(view_pointer, &mode, &quit);
        menu->run_menu();

        if (!quit && old_mode==mode)  // nie wylaczono gry w meni
        {
            Game* game = new Game(view_pointer, menu->best_score);
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
}


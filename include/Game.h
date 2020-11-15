#ifndef GAME_H
#define GAME_H
#include <curses.h>

#include "Player.h"
#include "MapsLoader.h"
#include "View.h"

class Game
{
    public:

        WINDOW* gameWindow;
        char*** maps;
        Player* player;
        MapsLoader* loader;
        View* view;

        static int current_map;
        static bool map_changed;

        static constexpr
          int map_change_array[10][4] = {//U,     R,      D,      L,
                                        {1,     NULL,   NULL,   NULL},   // parter, wejœcie g³ówne
                                        {2,     NULL,   0,      NULL},   // budynek B
                                        {NULL,  3,      1,      0   },   // budynek C1
                                        {NULL,  NULL,   NULL,   2   },   // budynek C2 (aule)
                                        {0,0,0,0,                   },   //...
                                        {0,0,0,0,                   },
                                        {0,0,0,0,                   },
                                        {0,0,0,0,                   },
                                        {0,0,0,0,                   },
                                        {0,0,0,0,                   }
                                        };

        Game(View*);
        void create_window();
        void play_game();
        virtual ~Game();

    protected:

    private:
        void load_current_map();
};

#endif // GAME_H

#ifndef GAME_H
#define GAME_H
#include <curses.h>
#include <string>

#include "Player.h"
#include "MapsLoader.h"
#include "View.h"
#include "Window.h"
#include "CoursesList.h"

using namespace std;

class Game
{
    public:

        Window* gameWindow;
        char*** maps;
        Player* player;
        MapsLoader* loader;
        View* view;
        int quit_game;
        int goal_x;
        int goal_y;
        int goal_map;
        int current_map;

        CoursesList* allCourses;

        static bool map_changed;

        static constexpr
          int map_change_array[10][4] = {//U,     R,      D,      L,
                               /*A*/    {1,     -1,     -1,     -1  },   // parter, wejscie glówne
                               /*B*/    {2,     -1,     0,      -1  },   // budynek B
                               /*C1*/   {-1,    3,      1,      -1  },   // budynek C1
                               /*C2*/   {-1,    -1,     -1,     2   },   // budynek C2 (aule)
                               /*AP0_1*/{-1,    5,      -1,     -1  },   // niski parter 1
                               /*AP0_2*/{-1,    -1,     -1,     4   },   // niski parter 2
                               /*AP1_1*/{-1,    7,      -1,     -1  },   // pierwsze pietro 1
                               /*AP1_2*/{-1,    -1,     -1,     6   },   // pierwsze pietro 2
                               /*AP2_1*/{-1,    9,      -1,     -1  },   // drugie pietro 1
                               /*AP2_2*/{-1,    -1,     -1,     8   }    // drugie pietro 2
                                        };

        static constexpr
          int rooms_coordinates[13][4] = {//nr, map,    x,  y,
                                        {15,    1,      24, 12  },  //PP
                                        {130,   6,      48, 12  },  //ALGEBRA, ANALIZA
                                        {116,   7,      10, 3   },  //WDI
                                        {32,    2,      20, 3   },  //LOGIKA
                                        {39,    5,      16, 12  },  //LINUX, PO, PS, ZTP, KCK
                                        {102,   6,      11, 3   },  //AK, PEiE
                                        {236,   9,      44, 12  },  //BD, IO, SBD
                                        {202,   8,      12, 3   },  //SIECI, SB
                                        {125,   6,      3,  12  },  //UEiTP
                                        {224,   8,      23, 12  },  //SO
                                        {209,   8,      58, 3   },  //SI, SM
                                        {6,     1,      49, 3   },  //MD, ASD
                                        {101,   6,      3 , 3   },  //TC,
                                        };


        Game(View*, Window*);
        void setup_window();
        void play_game();
        void add_points(int points, bool* sth_changed);
        virtual ~Game();

    protected:

    private:
        void load_current_map();
};

#endif // GAME_H

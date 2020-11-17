#include "View.h"
#include <stdio.h>


#include <iostream>
using namespace std;

View::View()
{
    //ctor
}

void View::test()
{
    cout << "no elo";
}

void View::clockUpdate(WINDOW* window, char decSec, char sec)
{

}

void View::mapFragmentUpdate(WINDOW* window, int x, int y, char current_map_char)
{

}

void View::playerPositionUpdate(WINDOW* window, int x, int y, char player_character)
{

}

void View::mapDisplay()
{

}

View::~View()
{
    //dtor
}

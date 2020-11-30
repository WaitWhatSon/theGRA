#include "Course.h"

Course::Course()
{
    //ctor
}

Course::~Course()
{
    //dtor
}

Course::Course(string _name, int _semester, int _room)
{
    this->name = _name;
    this->semester = _semester;
    this->room = _room;
}

string Course::get_name()
{
    return this->name;
}

int Course::get_semester()
{
    return this->semester;
}

int Course::get_room()
{
    return this->room;
}


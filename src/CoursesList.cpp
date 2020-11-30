#include "CoursesList.h"
#include <fstream>
#include <cstdlib>      // std::rand, std::srand
#include <algorithm>    // std::random_shuffle

using namespace std;

CoursesList::CoursesList()
{
    this->load_courses_from_file();
}

CoursesList::~CoursesList()
{
    //dtor
}

bool CoursesList::load_courses_from_file()
{
    ifstream file( "files/courses.txt", ios::in );
    string name;
    int semester, room_number;

    if( !file )
        cerr << "Cant open " << endl;

    while( file >> name >> semester >> room_number )
    {
        cout << name << " " << semester << " " << room_number << endl;
        this->add_course(name, semester, room_number);
    }

    file.close();
    return 0;

}

vector<Course> CoursesList::get_random_courses_list(int semester)
{
    for (int i = 0; i < this->get_size(); i++)
    {

    }
    ;
}

bool CoursesList::add_course(string name, int semester, int room)
{
    this->list_of_courses.push_back(new Course(name, semester, room));

    return true;
}

int CoursesList::get_size()
{
    return this->list_of_courses.size();
}

Course* CoursesList::get_course_at(int index)
{
    return this->list_of_courses[index];
}

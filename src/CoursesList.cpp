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
        this->add_course(name, semester, room_number);
    }

    file.close();
    return 0;

}

int myrandom (int i) {return std::rand()%i;}

vector<Course> CoursesList::get_random_courses_list(int semester)
{
    vector<Course> courses;
    for (int i = 0; i < this->get_size(); i++)
    {
        if (list_of_courses[i]->get_semester() == semester)
        {
            Course temp;
            temp.set_name(list_of_courses[i]->get_name());
            temp.set_room(list_of_courses[i]->get_room());
            temp.set_semester(list_of_courses[i]->get_semester());
            courses.push_back(temp);
        }
    }
    random_shuffle (courses.begin(), courses.end(), myrandom);

    return courses;
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

#ifndef COURSESLIST_H
#define COURSESLIST_H
#include "Course.h"
#include <string>
#include <vector>

class CoursesList
{
    private:
        vector<Course*> list_of_courses;

    public:
        /** Default constructor */
        CoursesList();
        /** Default destructor */
        virtual ~CoursesList();

        bool load_courses_from_file();

        vector<Course> get_random_courses_list( int semester);

        bool add_course(string name, int semester, int room_number);

        Course* get_course_at(int index);

        int get_size();

    protected:

    private:
};

#endif // COURSESLIST_H

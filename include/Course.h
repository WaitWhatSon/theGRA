#ifndef COURSE_H
#define COURSE_H
#include <string>
#include <iostream>

using namespace std;

class Course
{
    private:
        string name;
        int semester;
        int room;

    public:
        /** Default constructor */
        Course();
        Course(string name, int semester, int room);
        /** Default destructor */
        virtual ~Course();

        string get_name();
        int get_semester();
        int get_room();

        void set_name(string);
        void set_semester(int);
        void set_room(int);

    protected:

    private:
};

#endif // COURSE_H

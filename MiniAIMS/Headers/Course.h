#include "Characters.h"

class Course {
public:
    string course_code;
    bool grades_released = false;
    vector<Student> enrolled_students;
    Faculty instructor;
    void display_students_enrolled();

    Course(Faculty inst_input,string code = "TBD") : course_code(code), instructor(inst_input) {}
};

class Running_Courses {
public:
    void display_courses();

    vector<Course> course_list;
};
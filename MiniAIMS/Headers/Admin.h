#include "Course.h"

class Admin {
public:
    string contact;
    bool add_course(Running_Courses &rc_list,Faculty_list &f_list);
    bool delete_course(Running_Courses &rc_list);
    bool add_student(Students_list &s_list);
    bool delete_student(Students_list &s_list,Running_Courses &rc_list);
    bool add_faculty(Faculty_list &f_list);
    bool delete_faculty(Running_Courses &rc_list,Faculty_list &f_list);
    bool add_student_to_course(Course &c_obj, Student &s_obj);
    bool delete_student_from_course(Course &c_obj, Student &s_obj);
    void works()  {
        cout<<"Works!\n";
    }
};
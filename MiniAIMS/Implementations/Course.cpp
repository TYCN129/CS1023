#include "../Headers/Course.h"

void Course::display_students_enrolled() {
    int i;
    for(i = 0; i < enrolled_students.size(); i++) {
        cout<<i + 1<<". "<<enrolled_students[i].name<<"\n";
    }
}

void Running_Courses::display_courses()  {
    int i;
    for(i = 0; i < course_list.size(); i++) {
        cout<<i + 1<<". "<<course_list[i].course_code<<"\n";
    }
}
#include "Headers/Admin.h"

void retrieve(Students_list &s_list,Faculty_list &f_list,Running_Courses &rc_list)  {

    fstream fin;
    fin.open("Files/Student_list/record.txt",fstream::in);
    
    Person p_temp{};
    Student s_temp(p_temp);
    if(fin.is_open()) {
        
        fin.read((char *)(&s_temp),sizeof(s_temp));
        while(!fin.eof()) {
            s_list.get_list().push_back(s_temp);
            fin.read((char *)(&s_temp),sizeof(s_temp));
        }
        fin.close();
        cout<<"Student data retrieved\n";
    }

    fin.open("Files/Faculty_list/record.txt",fstream::in);

    Faculty f_temp(p_temp);
    if(fin.is_open()) {
    
        fin.read((char *)(&f_temp),sizeof(f_temp));
        while(!fin.eof()) {
            f_list.f_list.push_back(f_temp);
            fin.read((char *)(&f_temp),sizeof(f_temp));
        }
        fin.close();
        cout<<"Faculty data retrieved\n";
    }

    fin.open("Files/Course_list/record.txt",fstream::in);
    
    Course c_temp(f_temp);
    if(fin.is_open()) {

        fin.read((char *)(&c_temp),sizeof(c_temp));
        while(!fin.eof()) {
            rc_list.course_list.push_back(c_temp);
            fin.read((char *)(&c_temp),sizeof(c_temp));
        }
        fin.close();
        cout<<"Course data retrieved\n";
    }

    for(int i = 0; i < rc_list.course_list.size(); i++) {
        fin.open("Files/Course_list/Enrolled/" + rc_list.course_list[i].course_code + ".txt",fstream::in);
        fin.read((char *)(&s_temp),sizeof(s_temp));
        while(!fin.eof()) {
            rc_list.course_list[i].enrolled_students.push_back(s_temp);
            fin.read((char *)(&s_temp),sizeof(s_temp));
        }
        fin.close();
    }
    
    for(Course &c_obj : rc_list.course_list) { 
        if(c_obj.grades_released == true) {
            for(Student &s_obj : s_list.get_list()) {
                for(Student &s : c_obj.enrolled_students) {
                    if(s_obj.name == s.name) {
                        fin.open("Files/Student_list/Student_grades/" + s_obj.roll_no + ".txt",fstream::in);
                        Student_grade temp;
                        
                        fin.read((char *)(&temp),sizeof(temp));
                        while(!fin.eof()) {
                            if(temp.get_code() == c_obj.course_code) s_obj.grades.push_back(temp);
                            fin.read((char *)(&temp),sizeof(temp));
                        }

                        fin.close();
                    }
                }
            }
        }
    }

return;
}

void print_admin_tasks(Students_list &s,Faculty_list &f)  {

    system("clear");
    cout<<"You are now logged in as an Admin.\n";
    cout<<"Choose a task from the following and enter its number\t\t\t\tStudents: "<<s.list_size()<<"\n";
    cout<<"1. Add a new course\t\t\t\t\t\t\t\t Faculty: "<<f.list_size()<<"\n";
    cout<<"2. Delete an existing course\n";
    cout<<"3. Add a new IITH student\n";
    cout<<"4. Delete an existing IITH student\n";
    cout<<"5. Add an IITH student to a course\n";
    cout<<"6. Remove an IITH student from a course\n";
    cout<<"7. Add a new faculty member\n";
    cout<<"8. Remove faculty member\n";
    cout<<"Enter L to log out from the Admin account\n";
    cout<<"Enter Q to log out and exit this session\n";

return;
}

void perform_admin_task(Admin &admin, Running_Courses &r,Students_list &s,Faculty_list &f,char choice)  {

    int choice_s, choice_c;
    switch(choice) {
        case '1':
            admin.add_course(r,f);
            break;
        case '2':
            admin.delete_course(r);
            break;
        case '3':
            admin.add_student(s);
            break;
        case '4':
            admin.delete_student(s,r);
            break;
        case '5':
            r.display_courses();
            if(r.course_list.size() == 0) {
                cout<<"No course has been added yet\n";
                break;
            }
            cout<<"Select a course where enrollment is to be done\n";
            cin>>choice_c;
            
            if(r.course_list[choice_c - 1].grades_released == true) {
                cout<<"Grades have already been released. Cannot register now\n";
                break;
            }
            s.display_students();
            cout<<"Choose a student to be enrolled in";
            cin>>choice_s;
            
            admin.add_student_to_course(r.course_list[choice_c - 1],s.get_student(choice_s - 1));
            break;
        case '6':
            r.display_courses();
            cout<<"Select the course from where the student is to be removed\n";
            cin>>choice_c;

            r.course_list[choice_c - 1].display_students_enrolled();
            cout<<"Select the student to be removed from "<<r.course_list[choice_c - 1].course_code<<endl;
            cin>>choice_s;

            admin.delete_student_from_course(r.course_list[choice_c - 1],s.get_student(choice_s - 1));
            break;
        case '7':
            admin.add_faculty(f);
            break;
        case '8':
            admin.delete_faculty(r,f);
            break;
        default:
            cout<<"Enter valid option\n";
    }

return;
}

void print_faculty_tasks(string name)  {

    system("clear");
    cout<<"You are now logged in as "<<name<<" (Faculty)\n";
    cout<<"1. Display students enrolled for your course\n";
    cout<<"2. Submit grades\n";
    cout<<"Enter L to log out from the Faculty account\n";
    cout<<"Enter Q to log out and exit this session\n";

return;
}

void perform_faculty_task(Faculty &fac, Running_Courses &r,Students_list &s,Faculty_list &f,char choice)  {

    switch(choice) {
        case '1':
            fac.display_enrolled_students(r);
            break;
        case '2':
            fac.submit_grades(r,s);
            break;
        default:
            cout<<"Enter valid option\n";
    }

return;
}

void print_student_tasks(string name)  {

    system("clear");
    cout<<"You are now logged in as "<<name<<" (Student)\n";
    cout<<"1. Register for a running course\n";
    cout<<"2. De-register from a running course\n";
    cout<<"3. Display grades for registered courses\n";
    cout<<"Enter L to log out from the Admin account\n";
    cout<<"Enter Q to log out and exit this session\n";

return;
}

void perform_student_task(Student &stud,Running_Courses &r,char choice)  {

    int choice_c;
    switch(choice) {
        case '1':
            r.display_courses();
            cout<<"Select from above courses to register for\n";
            cin>>choice_c;

            stud.register_course(r.course_list[choice_c - 1]);
            break;
        case '2':
            r.display_courses();
            cout<<"Select from above courses to deregister from\n";
            cin>>choice_c;

            stud.deregister(r.course_list[choice_c - 1]);
            break;
        case '3':
            stud.display_grades();
            break;
        default:
            cout<<"Enter valid option\n";
    }

return;
}

void choose_role()  {

    cout<<"1. Admin\n";
    cout<<"2. Faculty\n";
    cout<<"3. Student\n";
    cout<<"Choose from the above roles to login as\n";
return;
}

void loading()  {
    cout.flush();
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 3; i++) {
            cout << ".";
            cout.flush();
            __libcpp_thread_sleep_for(500ms);
        }
        cout << "\b\b\b   \b\b\b";
    }
}

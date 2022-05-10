#include "../Headers/Admin.h"

void Faculty::display_enrolled_students(Running_Courses &rc_list)  {
    for(const Course &c_obj : rc_list.course_list) {
        if(c_obj.instructor.name == this->name) {
            if(c_obj.enrolled_students.size() == 0) {
                cout<<"No students enrolled\n";
                return;
            }
            for(const Student &s_obj : c_obj.enrolled_students) {
                cout<<s_obj.roll_no<<": "<<s_obj.name<<endl;
            }
        }
    }
    
return;
}

void Faculty::submit_grades(Running_Courses &rc_list,Students_list &s_list)  {
    for(Course &c_obj : rc_list.course_list) {
        if(c_obj.instructor.name == this->name) {
            if(c_obj.grades_released == true) {
                cout<<"Grades already submitted\n";
                return;
            } else {
                for(Student &s_obj : s_list.get_list()) {
                    for(Student &s : c_obj.enrolled_students) {
                        if(s_obj.name == s.name) {
                            string grade_input;
                            cout<<"Enter grade for student "<<s_obj.name<<": \n";
                            cin>>grade_input;
                            Student_grade temp(c_obj.course_code,grade_input);
                            s_obj.grades.push_back(temp);

                            fstream fin, f_temp;
                            fin.open("Files/Student_list/Student_grades/" + s_obj.roll_no + ".txt",fstream::app);
                            fin.write((char *)(&temp),sizeof(temp));
                            fin.close();
                            
                            Person p_temp;
                            Faculty fac_temp(p_temp);
                            Course c_temp(fac_temp);
                            fin.open("Files/Course_list/record.txt",fstream::in);
                            f_temp.open("Files/Course_list/temp.txt",fstream::app);

                            fin.read((char *)(&c_temp),sizeof(c_temp));
                            while(!fin.eof()) {
                                if(c_obj.course_code != c_temp.course_code) f_temp.write((char *)(&c_temp),sizeof(c_temp));
                                else {
                                    c_temp.grades_released = true;
                                    f_temp.write((char *)(&c_temp),sizeof(c_temp));
                                }
                                fin.read((char *)(&c_temp),sizeof(c_temp));
                            }

                            fin.close();
                            f_temp.close();
                            remove("Files/Course_list/record.txt");
                            rename("Files/Course_list/temp.txt","Files/Course_list/record.txt");
                        }
                    }
                }
                c_obj.grades_released = true;
                cout<<"Updating...\n";
            }
        }
    }

return;
}

bool Student::register_course(Course &obj)  {
    bool registered = false;
    for(int i = 0; i < obj.enrolled_students.size(); i++) {
        if(obj.enrolled_students[i].name == this->name) {
            registered = true;
        }
    }

    if(registered == true) {
        cout<<"Registration already done\n";
        return false;
    } else {
        if(obj.grades_released == false) {
            obj.enrolled_students.push_back(*this);
            cout<<"Successfully registered for "<<obj.course_code<<endl;
            fstream file;
            file.open("Files/Course_list/Enrolled/" + obj.course_code + ".txt",fstream::app);
            file.write((char *)this,sizeof(*this));
            file.close();
            return true;
        } else {
            cout<<"Grades already released. Could not register.\n";
            return false;
        }
    }


}

bool Student::deregister(Course &obj)  {
    bool not_registered = true;
    for(int i = 0; i < obj.enrolled_students.size(); i++) {
        if(obj.enrolled_students[i].name == this->name) {
            not_registered = false;
            if(obj.grades_released == false) {
                cout<<"De-registered from "<<obj.course_code<<endl;
                obj.enrolled_students.erase(obj.enrolled_students.begin() + i);

                Person p_temp;
                Student s_temp(p_temp);

                fstream file, temp;
                file.open("Files/Course_list/Enrolled/" + obj.course_code + ".txt",fstream::in);
                temp.open("Files/Course_list/Enrolled/temp.txt",fstream::app);

                file.read((char *)(&s_temp),sizeof(s_temp));
                while(!file.eof()) {
                    if(this->name != s_temp.name) temp.write("Files/Course_list/Enrolled/temp.txt",fstream::app);
                    file.read((char *)(&s_temp),sizeof(s_temp));
                }

                string path = "Files/Course_list/Enrolled/" + obj.course_code + ".txt";
                remove(path.c_str());
                rename("Files/Course/Enrolled/temp.txt",path.c_str());
                return true;
            } else {
                cout<<"Grades already released. Could not de-register.\n";
                return false;
            }
        }
    }

    if(not_registered == true) {
        cout<<"Registration was not done\n";
        return false;
    }

return false;
}

void Student::display_grades()  {
    for(Student_grade s_g : grades) {
        cout<<s_g.get_code() + ": " + s_g.get_grade()<<endl;
    }

return;
}
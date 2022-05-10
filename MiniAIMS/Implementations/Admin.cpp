#include "../Headers/Admin.h"

void update_course_list(Course temp)  {

    fstream fout;
    fout.open("Files/Course_list/record.txt",fstream::app);
    fout.write((char *)(&temp),sizeof(temp));
    fout.close();

return;
}
bool Admin::add_course(Running_Courses &rc_list,Faculty_list &f_list)  {
    string code;
    int choice;

    cout<<"Enter course code: \n";
    cin.ignore();
    getline(cin,code);
    
    f_list.display_faculties();
    cout<<"Select from the above faculties to be assigned to this course\n";
    cin>>choice;
    Course temp(f_list.f_list[choice - 1],code);
    rc_list.course_list.push_back(temp);

    update_course_list(temp);

    cout<<"Course added successfully\n";

return true;
}

void file_c_delete(Running_Courses &rc_list,int choice)  {
  
    fstream temp, fin;
    temp.open("Files/Course_list/temp.txt",fstream::app);
    fin.open("Files/Course_list/record.txt",fstream::in);

    Person p_temp{};
    Faculty f_temp(p_temp);
    Course c_temp(f_temp);
    fin.read((char *)(&c_temp),sizeof(c_temp));
    while(!fin.eof()) {
        if(c_temp.course_code != rc_list.course_list[choice - 1].course_code) {
            temp.write((char *)(&c_temp),sizeof(c_temp));
        }
        fin.read((char *)(&c_temp),sizeof(c_temp));
    }

    fin.close();
    temp.close();
    remove("Files/Course_list/record.txt");
    rename("Files/Course_list/temp.txt","Files/Course_list/record.txt");

    string path = "Files/Course_list/Enrolled/" + rc_list.course_list[choice - 1].course_code + ".txt";
    remove(path.c_str());

return;
}
bool Admin::delete_course(Running_Courses &rc_list)  {
    int choice;
    
    if(rc_list.course_list.size() == 0) {
        cout<<"No course to delete\n";
        return false;
    }

    for(int i = 0; i < rc_list.course_list.size(); i++) {
        cout<<i + 1<<". "<<rc_list.course_list[i].course_code<<endl;
    }
    
    cout<<"Choose from the above running courses to be deleted: \n";
    cout<<"Enter 0 to return back \n";
    cin>>choice;
    
    if(choice == 0) return false;

    file_c_delete(rc_list,choice);

    rc_list.course_list.erase(rc_list.course_list.begin() + (choice - 1));
    cout<<"Course deleted successfully\n";

return true;
}

void file_s_add(Student temp)  {
    
    fstream fin;
    fin.open("Files/Student_list/record.txt",fstream::app);
    fin.write((char *)(&temp),sizeof(temp));
    fin.close();

return;
}
bool Admin::add_student(Students_list &s_list)  {
    string name_input;
    int age_input;

    cout<<"Enter name of the student: \n";
    cin.ignore();
    getline(cin,name_input);
    cout<<"Enter student's age: \n";
    cin>>age_input;

    string roll;
    s_list.get_list().size() < 10 ? roll = "@0" + to_string(s_list.get_list().size()) : roll = "@" + to_string(s_list.get_list().size());

    Person p_temp(name_input,age_input);
    Student temp(p_temp,roll);

    file_s_add(temp);

    s_list.s_list.push_back(temp);
    cout<<"Student "<<temp.name<<" added successfully\n";
    
return true;
}

void file_s_delete(string name_input,Running_Courses &rc_list)  {
    
    fstream temp, fin;
    temp.open("Files/Student_list/temp.txt",fstream::app);
    fin.open("Files/Student_list/record.txt",fstream::in);

    Person p_temp{};
    Student s_temp(p_temp);
    fin.read((char *)(&s_temp),sizeof(s_temp));
    while(!fin.eof()) {
        if(s_temp.name != name_input) {
            temp.write((char *)(&s_temp),sizeof(s_temp));
        }
        fin.read((char *)(&s_temp),sizeof(s_temp));
    }

    fin.close();
    temp.close();
    remove("Files/Student_list/record.txt");
    rename("Files/Student_list/temp.txt","Files/Student_list/record.txt");

    for(int i = 0; i < rc_list.course_list.size(); i++) {
        string path = "Files/Course_list/Enrolled/" + rc_list.course_list[i].course_code + ".txt";
        fin.open(path,fstream::in);
        temp.open("Files/Course_list/Enrolled/temp.txt",fstream::app);
        
        fin.read((char *)(&s_temp),sizeof(s_temp));
        while(!fin.eof()) {
            if(s_temp.name != name_input) temp.write((char *)(&s_temp),sizeof(s_temp));
            fin.read((char *)(&s_temp),sizeof(s_temp));
        }

        fin.close();
        temp.close();
        remove(path.c_str());
        rename("Files/Course_list/Enrolled/temp.txt",path.c_str());
    }


return;
}
bool Admin::delete_student(Students_list &s_list,Running_Courses &rc_list)  {

    if(s_list.s_list.size() == 0) {
        cout<<"No student to remove\n";
        return false;
    }

    string name_input;
    int choice;

    for(int i = 0; i < s_list.s_list.size(); i++) {
        cout<<i + 1<<" "<<s_list.s_list[i].name<<endl;
    }
    cout<<"Select from the above students to remove \n";
    cout<<"Enter 0 to return back \n";
    cin>>choice;

    if(choice == 0) {
        cout<<"Returning back\n";
        return false;
    }

    name_input = s_list.s_list[choice - 1].name;
    s_list.s_list.erase(s_list.s_list.begin() + (choice - 1));
    file_s_delete(name_input,rc_list);

    for(Course &c_obj : rc_list.course_list) {
        for(int i = 0; i < c_obj.enrolled_students.size(); i++) {
            if(c_obj.enrolled_students[i].name == name_input) {
                c_obj.enrolled_students.erase(c_obj.enrolled_students.begin() + i);
                break;
            }
        }
    }

    cout<<"Student "<<name_input<<" was removed successfully\n";

return true;
}

void file_f_add(Faculty temp)  {

    fstream fin;
    fin.open("Files/Faculty_list/record.txt",fstream::app);
    fin.write((char *)(&temp),sizeof(temp));
    fin.close();

}
bool Admin::add_faculty(Faculty_list &f_list)  {
    string name_input;
    int age_input;

    cout<<"Enter name of the faculty: \n";
    cin.ignore();
    getline(cin,name_input);
    cout<<"Enter faculty's age: \n";
    cin>>age_input;

    Person p_temp(name_input,age_input);
    Faculty temp(p_temp);

    file_f_add(temp);
    
    f_list.f_list.push_back(temp);
    cout<<"Faculty "<<temp.name<<" added successfully\n";

return true;
}

void file_f_delete(string name_input)  {

    fstream temp, fin;
    temp.open("Files/Faculty_list/temp.txt",fstream::app);
    fin.open("Files/Faculty_list/record.txt",fstream::in);

    Person p_temp{};
    Faculty f_temp(p_temp);
    fin.read((char *)(&f_temp),sizeof(f_temp));
    while(!fin.eof()) {
        if(f_temp.name != name_input) {
            temp.write((char *)(&f_temp),sizeof(f_temp));
        }
        fin.read((char *)(&f_temp),sizeof(f_temp));
    }

    fin.close();
    temp.close();
    remove("Files/Faculty_list/record.txt");
    rename("Files/Faculty_list/temp.txt","Files/Faculty_list/record.txt");

return;
}

bool Admin::delete_faculty(Running_Courses &rc_list,Faculty_list &f_list)  {
    
    if(f_list.f_list.size() == 0) {
        cout<<"No faculty to remove\n";
        return false;
    }
    
    string name_input;
    int choice;

    for(int i = 0; i < f_list.f_list.size(); i++) {
        cout<<i + 1<<" "<<f_list.f_list[i].name<<endl;
    }
    cout<<"Select from the above faculties to remove \n";
    cout<<"Enter 0 to return back \n";
    cin>>choice;

    if(choice == 0) return false;
    
    name_input = f_list.f_list[choice - 1].name;

    f_list.f_list.erase(f_list.f_list.begin() + (choice - 1));

    for(Course &c_obj : rc_list.course_list) {
        if(c_obj.instructor.name == name_input) {
            cout<<"Faculty "<<name_input<<" (course taught -> "<<c_obj.course_code<<") was removed successfully\n";
            break;
        } else {
            cout<<"Faculty "<<name_input<<"(course taught -> None) was removed successfully\n";
            break;
        }            
    }

    file_f_delete(name_input);

return true;
}

void enrolled_list_add(Course &c_obj,Student &s_obj)  {
  
    fstream fin;
    fin.open("Files/Course_list/Enrolled/" + c_obj.course_code + ".txt",fstream::app);
    if(!fin.is_open()) cout<<"File not created/opened\n";
    fin.write((char *)(&s_obj),sizeof(s_obj));
    fin.close();

return;
}

bool Admin::add_student_to_course(Course &c_obj, Student &s_obj)  {

    for(Student &s : c_obj.enrolled_students)
        if(s.name == s_obj.name) {
            cout<<"Student already registered for this course\n";
            return false;
        }

    cout<<"Student "<<s_obj.name<<" added to "<< c_obj.course_code<<" successfully\n";
    c_obj.enrolled_students.push_back(s_obj);
    enrolled_list_add(c_obj,s_obj);

return true;
}

void enrolled_list_delete(Course &c_obj,Student &s_obj)  {

    fstream file, temp;
    file.open("Files/Course_list/Enrolled/" + c_obj.course_code + ".txt",fstream::in);
    temp.open("Files/Course_list/Enrolled/temp.txt",fstream::app);
    
    Person p_temp;
    Student s_temp(p_temp);

    file.read((char *)(&s_temp),sizeof(s_temp));
    while(!file.eof()) {
        if(s_temp.name != s_obj.name) temp.write((char *)(&s_temp),sizeof(s_temp));
        file.read((char *)(&s_temp),sizeof(s_temp));
    }

    file.close();
    temp.close();
    string path = "Files/Course_list/Enrolled/" + c_obj.course_code + ".txt";
    remove(path.c_str());
    rename("Files/Course_list/Enrolled/temp.txt",path.c_str());

return;
}
bool Admin::delete_student_from_course(Course &c_obj, Student &s_obj)  {
    
    int count = 0;
    for(int i = 0; i < c_obj.enrolled_students.size(); i++) {
        if(c_obj.enrolled_students[i].name == s_obj.name) {
            count++;
            cout<<"Student "<<s_obj.name<<" removed from "<< c_obj.course_code<<" successfully\n";
            c_obj.enrolled_students.erase(c_obj.enrolled_students.begin() + i);
            enrolled_list_delete(c_obj,s_obj);
            return true;
        }
    }

    if(count == 0) {
        cout<<"Student was not registered\n";
        return false;
    }
    
return false;
}
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<cstdio>
using namespace std;

class Course;
class Student_grade;
class Admin;
class Running_Courses;

class Person {
public:
    int age;
    string name;
    Person(string name_input = "Unknown",int age_input = 0) : name(name_input), age(age_input) {}
};

class Student : public Person {
public:
    string contact, roll_no;
    vector<Student_grade> grades;
    bool register_course(Course &obj);
    bool deregister(Course &obj);
    void display_grades();

    Student(Person p_obj,string roll_no_input = "Invalid") : Person(p_obj),roll_no(roll_no_input)  {}
};

class Students_list {
    friend class Admin;
public:
    void display_students()  {
        for(int i = 0; i < s_list.size(); i++) {
            cout<<i + 1<<". "<<s_list[i].name<<"\n";
        }
    }
    Student &get_student(int index) {
        return s_list[index];
    }
    vector<Student> &get_list()  {
        return s_list;
    }
    int list_size() {
        return s_list.size();
    }
private:
    vector<Student> s_list;
};

class Faculty : public Person {
public:
    string contact;
    void display_enrolled_students(Running_Courses &rc_list);
    void submit_grades(Running_Courses &rc_list,Students_list &s_list);

    Faculty(Person p_obj) : Person(p_obj.name,p_obj.age) {}
};

class Faculty_list {
public:
    void display_faculties()  {
        for(int i = 0; i < f_list.size(); i++) {
            cout<<i + 1<<". "<<f_list[i].name<<"\n";
        }
    }
    int list_size() {
        return f_list.size();
    }
    vector<Faculty> f_list;
};

class Student_grade {
public:
    string get_grade()  {return grade;}
    string get_code()  {return course_code;}
    Student_grade(string code_input = "NA",string grade_input = "NA") : grade(grade_input),course_code(code_input) {}
private:
    string course_code, grade;
};

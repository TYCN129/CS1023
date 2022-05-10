#include "utilities.h"

int main()  {

    Admin a1;
    Running_Courses r;
    Students_list s;
    Faculty_list f;
    retrieve(s,f,r);

    char action_choice, role_choice;
    
    system("clear");
    cout<<"Welcome to MiniAIMS!\n";
    __libcpp_thread_sleep_for(3s);
    cout<<"Opening Admin control panel";
    loading();
    system("clear");
    

Admin:
    print_admin_tasks(s,f);
    cin>>action_choice;
    while(action_choice != 'Q' && action_choice != 'L') {
        perform_admin_task(a1,r,s,f,action_choice);
        __libcpp_thread_sleep_for(2s);
        system("clear");

        print_admin_tasks(s,f);
        cin>>action_choice;
    }
    cout<<"Logging out";
    loading();
    system("clear");
    goto Handler;

Faculty:
        int choice_f;
        f.display_faculties();
        cout<<"Select from the above faculty accounts to login as\n";
        cin>>choice_f;
        print_faculty_tasks(f.f_list[choice_f - 1].name);
        cin>>action_choice;
        while(action_choice != 'Q' && action_choice != 'L') {
            perform_faculty_task(f.f_list[choice_f - 1],r,s,f,action_choice);
            __libcpp_thread_sleep_for(2s);
            system("clear");

            print_faculty_tasks(f.f_list[choice_f - 1].name);
            cin>>action_choice;
        }
        cout<<"Logging out";
        loading();
        system("clear");
        goto Handler;

Student:
        int choice_s;
        s.display_students();
        cout<<"Select from the above student accounts to login as\n";
        cin>>choice_s;
        print_student_tasks(s.get_list()[choice_s - 1].name);
        cin>>action_choice;
        while(action_choice != 'Q' && action_choice != 'L') {
            perform_student_task(s.get_list()[choice_s - 1],r,action_choice);
            __libcpp_thread_sleep_for(2s);
            system("clear");

            print_student_tasks(s.get_list()[choice_s - 1].name);
            cin>>action_choice;
        }
        cout<<"Logging out";
        loading();
        system("clear");
        goto Handler;

Handler:
    if(action_choice == 'Q') return 0;
    else if(action_choice == 'L') {
        choose_role();
        cin>>role_choice;
        switch(role_choice) {
        case '1':
            print_admin_tasks(s,f);
            cin>>action_choice;
            goto Admin;
            break;
        case '2':
            goto Faculty;
            break;
        case '3':
            goto Student;
            break;
        }
    }

return 0;
}

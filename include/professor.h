#include <iostream>
#include <string>
#include "user.h"
using namespace std;

class Professor : public User{
    private:
        string department;
        string subject;
    public:
        Professor(int id, int age, string f_name, string l_name, string department, string subject) : User(id, age, f_name, l_name){
            setProfessor(department, subject);
        }

        void setProfessor(string dep, string sub){
            department = dep;
            subject = sub;
        }

        void displayProfessor() const{
            displayUser();
            cout << "Department: " << department << endl;
            cout << "Subject: " << subject << endl;
        }
};
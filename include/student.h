#include <iostream>
#include <string>
#include "user.h"
using namespace std;

class Student : public User{
    private:
        double gpa;
        int semester;
    public:
        
        Student(int id, int age, string first_name, string last_name, double gpa, int semester) : User(id, age, first_name, last_name){
            setStudent(gpa, semester);
        }

        void setStudent(int g, int s){
            if(g < 0.0 || g > 4.0){
                cout << "GPA must be between 0.0 and 4.0! Set to 0.0" << endl;
                gpa = 0.0;
            } else {
                gpa = g;
            }

            // checks if value is negative
            if(s < 0){
                cout << "Semester must be positive! Set to 0." << endl;
                semester = 0;
            } else {
                semester = s;
            }
        }

        void displayStudent() const{
            displayUser();
            cout << "GPA: " << gpa << endl;
            cout << "Semester: " << semester << endl;
        }
};
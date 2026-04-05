#pragma once
#include <iostream>
#include <string>
using namespace std;

class User{
    private:
        int U_ID;
        int age;
        string first_name;
        string last_name;
    public:
        
        //parameterized constructor
        User(int u_id, int age, string f_name, string l_name){
             setUser(u_id, age, f_name, l_name);
        }

        //setter function for User
        void setUser(int id, int a, string f_n, string l_n){
            first_name = f_n;
            last_name = l_n;


            //validation of id
            if(id > 0){
                U_ID = id;
            } else {
                U_ID = 0;
                cout << "ID cannot be negative! Set to 0." << endl;
            }

            //validation of age
            if(a > 0){
                age = a;
            } else {
                age = 0;
                cout << "AGE cannot be negative! Set to 0." << endl;
            }
        }

        void displayUser() const{
            cout << "First Name: " << first_name << endl;
            cout << "Last Name: " << last_name << endl;
            cout << "Age: " << age << endl;
            cout << "ID: " << U_ID << endl;
        }
};


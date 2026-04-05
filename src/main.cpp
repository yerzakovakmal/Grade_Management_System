#include <iostream>
#include "../include/user.h"
#include "../include/student.h"
#include "../include/professor.h"
#include "../include/grade.h"
#include "../include/course.h"
using namespace std;

int main(){
    //"Akmal", 19, 2510064, "Computer Science", 3.8, 1
    Student s1(101, 19, "Akmal", "Yerzakov", 3.7, 2);
    Student s2(102, 20, "Jamshid", "Erkinov", 3.9, 3);

    //"Mr. Karimov", 40, 201, "Engineering", 5000, "Java Programming Language"
    Professor p1(201, 27, "Sasha", "Petrov", "Computer Science", "Operating System");
    Professor p2(202, 23, "Diyora", "Mirzayeva", "Mathematics", "Statistics and Analysis");


    cout << "\n---------- Student Details ----------" << endl;
    s1.displayStudent();

    cout << "\n---------- Student Details ----------" << endl;
    s2.displayStudent();

    cout << "\n---------- Teacher Details ----------" << endl;
    p1.displayProfessor();

    cout << "\n---------- Teacher Details ----------" << endl;
    p2.displayProfessor();
    return 0;
}
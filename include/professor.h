#include "user.h"
#include "course.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

class Professor : virtual public User{
    private: 
        string employeeID;
        string department;
        vector<Course*> taughtCourses;
    public:

        Professor(string name, string email, string password, string empId, string dept);
        ~Professor() override;
        
        //getters
        string getEmployeeId() const;
        string getDepartment() const;
        vector<Course*> getTaughtCourses() const;
        

        // setters
        void createCourse(Course* course);
        void assignGrade(Student& student, Course& course, double score);
        void postMaterial(string material, Course& course);
        void createAssignment(Course& course, string title, string description, double maxScore);
        string generateReport(Course& course) const;
        void assignTA(TeachingAssistant& ta, Course& course);

        //operator overloads
        bool operator==(const Professor& other) const;
        friend ostream& operator<<(ostream& os, const Professor& p);

        string getRole() const override;
        void displayInfo() const override;
};
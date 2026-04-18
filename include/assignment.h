# pragma once
#include <iostream>
#include <string>
using namespace std;

class Course;

class Assignment{
    private:
        int assignmentID;
        string title;
        string dueDate;
        double maxScore;
        Course* course;
    public:
        Assignment(string title, string dueDate, double maxScore, Course* course);

        //getters
        int getAssignmentID() const;
        string getTitle() const;
        string getDueDate() const;
        double getMaxScore() const;
        Course* getcourse() const;

        //setters
        void setTitle(string title);
        void setDueDate(string date);
        void setMaxScore(double score);


        bool isOverdue(string todayDate) const;
        static int getTotalAssignments();

        //operator overloading
        friend ostream& operator<<(ostream& out, const Assignment& a);
        bool operator==(const Assignment other) const;
        bool operator!=(const Assignment& other) const;
        bool operator<(const Assignment& other) const;
        bool operator>(const Assignment& other) const;
};
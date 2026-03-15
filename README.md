# Student Course & Grade Management System
*The main goal of this project is to develop a GUI-based Student Course & Grade Management System in C++ that helps organize academic information more efficiently for students and instructors. The system is designed to simplify course management, grade recording, and student data handling through a user-friendly interface.*


# Problem Statement
- Managing student, course, and grade information manually can be slow and confusing
- Existing systems may require too many steps for simple academic tasks
- Professors may face difficulties while recording and updating grades
- Students may not have a clear and organized way to view their academic progress

# Target Users
- Students
- Professors
- Academic Admins

# Expected Outcomes
- Faster organization of student and course data
- Easier grade recording and updating
- Better usability through a clean GUI
- Reduced manual workload for both students and professors
- More efficient academic data management overall

# Project Structure
```
team_project_oop/
│
├── include/
│   ├── user.h
│   ├── student.h
│   ├── professor.h
│
├── src/
│   ├── user.cpp
│   ├── student.cpp
│   ├── professor.cpp
│   ├── course.cpp
│   ├── grade.cpp
│   ├── main.cpp
│
├── data/
│   ├── students.txt
│   ├── courses.txt
│   ├── grades.txt
│
├── README.md
└── .gitignore
```
*(work in progress...)*


## Main Classes
- ```User``` -> base class
- ```Student``` -> class inherited from ```User```
- ```Professor``` -> class inherited from ```User```
- ```Course```
- ```Grade``` 
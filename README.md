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

## File Structure

```
project/
├── src/
│   ├── User.hpp / User.cpp
│   ├── Student.hpp / Student.cpp
│   ├── Professor.hpp / Professor.cpp
│   ├── TeachingAssistant.hpp / TeachingAssistant.cpp
│   ├── Course.hpp / Course.cpp
│   ├── Assignment.hpp / Assignment.cpp
│   ├── Grade.hpp / Grade.cpp
│   ├── Exceptions.hpp
│   └── main.cpp
├── qt/
│   ├── MainWindow.hpp / .cpp / .ui
│   ├── LoginDialog.hpp / .cpp / .ui
│   └── ...
├── design/
│   ├── wireframes.fig
│   └── hifi_screens.fig
├── demo/
│   ├── exceptions_demo.cpp   
│   └── operators_demo.cpp   
├── data/
│   └── (saved .txt files from file I/O)
└── README.md
```
---
*(work in progress...)*

## Team Task Board

---

## Team Structure

| Member | Role | Focus |
|---|---|---|
| Akmal | C++ Lead | Class hierarchy, integration |
| Akbarali | C++ Dev | Supporting classes, file I/O |
| Xondamir | Qt Lead | Main window, navigation |
| Nodir | Qt Dev | Forms, dialogs, widgets |
| Malika | Design + Presenter | Figma UI, slides, + bonus code |
| Rushana | Design + Presenter | Figma UI, slides, + bonus code |

---

## C++ Tasks — Akmal & Akbarali

> **Rule:** Every class gets its own `.hpp` and `.cpp` file. No implementation inside `.hpp` except inline getters. Always compile and test before pushing.

---

### TASK C-01 — `User` base class
**Assigned to:** Akmal
**Files:** `User.hpp`, `User.cpp`

**What to include:**
- `protected` fields: `name`, `email`, `password`, `role`, `userId` (int)
- `private static` fields: `totalUsers`, `nextId` (auto-increment from 1000)
- Constructor with validation (empty name/email throws, password < 6 chars throws)
- Virtual destructor — decrements `totalUsers`
- Getters: `getName()`, `getEmail()`, `getUserId()`, `getRole()` (non-virtual version)
- Setters with validation: `setName()`, `setEmail()`
- Methods: `login()`, `logout()`, `updateProfile()`, `changePassword()`
- Static methods: `getTotalUsers()`, `resetUserCount()`
- `operator==` (compare by userId), `operator!=`, `operator<<`
- **Pure virtual:** `getRole() const = 0`, `displayInfo() const = 0`

**How to think about it:**
> This class can never be instantiated directly. Every method that all three user types share goes here. If you find yourself writing the same method in Student AND Professor, move it up to User.

---

### TASK C-02 — `Student` class
**Assigned to:** Akmal
**Files:** `Student.hpp`, `Student.cpp`

**What to include:**
- Inherits: `virtual public User`
- Fields: `studentId` (string), `gpa` (double), `enrolledCourses` (vector\<Course*\>), `grades` (vector\<Grade\>)
- Constructor: calls `User(name, email, password, "Student")`
- Methods: `enrollCourse()`, `dropCourse()`, `viewGrades()`, `calculateGPA()`, `submitAssignment()`, `viewTranscript()`, `receiveGrade()` (called by Professor/TA when assigning)
- `operator==` (compare by studentId), `operator<<`
- Override: `getRole()` returns `"Student"`, `displayInfo()`

**How to think about it:**
> `calculateGPA()` loops over the grades vector and averages them. `enrollCourse()` should check capacity and throw `CourseFullException` if full. `receiveGrade()` is the method Professor calls — Student doesn't grade itself.

---

### TASK C-03 — `Professor` class
**Assigned to:** Akmal
**Files:** `Professor.hpp`, `Professor.cpp`

**What to include:**
- Inherits: `virtual public User`
- Fields: `employeeId` (string), `department` (string), `taughtCourses` (vector\<Course*\>) — non-owning
- Constructor: calls `User(name, email, password, "Professor")`
- Methods: `createCourse()`, `assignGrade()`, `manageRoster()`, `postMaterial()`, `createAssignment()`, `generateReport()` (returns string), `assignTA()`
- `assignGrade()` throws `out_of_range` if score not in 0–100
- `operator==` (compare by employeeId), `operator<<`
- Override: `getRole()` returns `"Professor"`, `displayInfo()`

**How to think about it:**
> `generateReport()` should return a string, not print directly — this keeps it GUI-ready. Use `ostringstream` to build the string and return it. Professor does not own Course objects, just holds pointers to them.

---

### TASK C-04 — `TeachingAssistant` class
**Assigned to:** Akmal
**Files:** `TeachingAssistant.hpp`, `TeachingAssistant.cpp`

**What to include:**
- Inherits: `public Student`, `public Professor` (multiple inheritance)
- Fields: `assignedCourse` (Course*), `hoursWorked` (int), `stipend` (double)
- Constructor initializer list **must** explicitly call `User(...)` first (virtual base rule), then `Student(...)`, then `Professor(...)`
- Methods: `gradeAssignment()`, `postAnnouncement()`, `holdOfficeHours()`, `answerQuestion()`, `assistProfessor()`, `viewCourseRoster()`, `logHours()`, `setAssignedCourse()`
- `operator==` (compare by getUserId()), `operator<<`
- **Must** override both `getRole()` and `displayInfo()` — required to resolve ambiguity from two parents

**How to think about it:**
> The constructor initializer list is the trickiest part. Study virtual inheritance before writing this. Every method that checks `assignedCourse` should throw `runtime_error` if it is `nullptr` — a TA without a course should not be able to grade or post.

---

### TASK C-05 — `Course` class
**Assigned to:** Akbarali
**Files:** `Course.hpp`, `Course.cpp`

**What to include:**
- Fields: `courseId` (string), `courseName` (string), `credits` (int), `capacity` (int), `enrolledStudents` (vector\<Student*\>), `assignments` (vector\<Assignment\>), `materials` (vector\<string\>), `announcements` (vector\<string\>), `professor` (Professor*)
- `static int courseCount`
- Constructor: validates capacity > 0, increments courseCount
- Methods: `addStudent()` — throws `CourseFullException` if at capacity, `removeStudent()`, `getEnrolledStudents()`, `getRoster()`, `addMaterial()`, `addAssignment()`, `addAnnouncement()`, `getCourseName()`, `getCourseId()`
- `operator==` (compare by courseId), `operator<<`
- `saveToFile(string filename)` — writes course data to a `.txt` file
- `loadFromFile(string filename)` — reads it back (static factory method)

**How to think about it:**
> Course owns its Assignment objects (store by value in the vector). It does NOT own Student or Professor pointers — those are managed elsewhere. File saving can be simple line-by-line text: one field per line.

---

### TASK C-06 — `Assignment` class
**Assigned to:** Akbarali
**Files:** `Assignment.hpp`, `Assignment.cpp`

**What to include:**
- Fields: `assignmentId` (int, auto-increment), `title` (string), `dueDate` (string), `maxScore` (double), `course` (Course*, non-owning)
- Constructor: throws if `maxScore <= 0`
- Methods: `getTitle()`, `getDueDate()`, `getMaxScore()`, `getCourseId()`
- `operator<` (compare by dueDate — useful for sorting), `operator==`, `operator<<`

**How to think about it:**
> Keep this class simple. It represents the definition of an assignment, not a student's submission. The Grade class connects a student to an assignment score.

---

### TASK C-07 — `Grade` class
**Assigned to:** Akbarali
**Files:** `Grade.hpp`, `Grade.cpp`

**What to include:**
- Fields: `student` (Student*, non-owning), `assignment` (Assignment*, non-owning), `score` (double), `letterGrade` (char), `feedback` (string)
- Constructor: calls `calculateLetterGrade()` automatically
- Private method `calculateLetterGrade()`: 90+ = A, 80+ = B, 70+ = C, 60+ = D, else F
- Methods: `setScore()` — recalculates letter grade on change, `getScore()`, `getLetterGrade()`, `getFeedback()`, `setFeedback()`
- `setScore()` throws `out_of_range` if score not in 0–maxScore
- `operator>` (compare scores), `operator==`, `operator<<`
- `saveToFile()`, `loadFromFile()`

**How to think about it:**
> `calculateLetterGrade()` should be called both in the constructor and whenever `setScore()` is called — the letter grade must always stay in sync with the score. Never let them get out of sync.

---

### TASK C-08 — Exception classes
**Assigned to:** Akbarali
**Files:** `Exceptions.hpp` (header only — these are tiny)

**What to include:**
```cpp
class EnrollmentException    : public runtime_error { ... };
class CourseFullException     : public EnrollmentException { ... };
class GradeOutOfRangeException: public out_of_range { ... };
class InvalidUserException    : public invalid_argument { ... };
class FileIOException         : public runtime_error { ... };
```
Each class just needs a constructor that passes a message string to the parent:
```cpp
explicit CourseFullException(const string& msg)
    : EnrollmentException(msg) {}
```

**How to think about it:**
> These are all one-liners. The value is in the type — catching `CourseFullException` is more specific than catching `runtime_error`. Keep them all in one `Exceptions.hpp` file, no `.cpp` needed.

---

### TASK C-09 — `main.cpp` demo
**Assigned to:** Akmal + Akbarali (together)
**Files:** `main.cpp`

**What to include:**
- Create 1 Professor, 2 Students, 1 TA
- Professor creates a Course and adds both Students
- Professor assigns TA to the Course
- Professor assigns grades to both Students
- TA grades an assignment
- Print all users via `operator<<` and `displayInfo()`
- Demonstrate polymorphism: store all users in `vector<User*>` and call `getRole()` on each
- Demonstrate `getTotalUsers()` static method
- Wrap everything in try-catch blocks using your custom exceptions
- Save a Course to file and reload it

**How to think about it:**
> This is your proof that everything connects. Build it last, after all classes compile cleanly individually. It is also what the professor will likely run first.

---

## Qt Tasks — Xondamir & Nodir

> Start these after C++ core classes (C-01 through C-04) are done. Qt wraps the C++ objects — it never reimplements the logic.

### TASK Q-01 — Project setup & main window skeleton
**Assigned to:** Xondamir
- Set up Qt Creator project, link C++ source files
- Create `MainWindow` with sidebar navigation (Dashboard, Courses, Students, Grades)
- Role-based view switching: Professor sees different tabs than Student

### TASK Q-02 — Login screen
**Assigned to:** Nodir
- Email + password form
- On submit: calls `user.login()`, catches `runtime_error`, shows error dialog
- On success: switches to role-appropriate main window

### TASK Q-03 — Course management screen (Professor view)
**Assigned to:** Xondamir
- List of courses (`QTableWidget` or `QListWidget`)
- "Create course" button → dialog form → calls `professor.createCourse()`
- "View roster" button → calls `professor.manageRoster()`

### TASK Q-04 — Grade entry screen
**Assigned to:** Nodir
- Select student from dropdown, enter score
- Calls `professor.assignGrade()`, wraps in try-catch, shows `GradeOutOfRangeException` as a `QMessageBox`

### TASK Q-05 — Student dashboard
**Assigned to:** Xondamir + Nodir
- Shows enrolled courses, GPA, grades table
- Calls `student.calculateGPA()`, `student.viewGrades()`

---

## Design Tasks — Malika & Rushana

> Use Figma with IUT brand colors: Navy `#0D2D6E`, Sky Blue `#0099D6`. Font: DM Sans for body, Playfair Display for headings.

### TASK D-01 — Wireframes (lo-fi)
**Assigned to:** Malika
- Sketch all screens: Login, Dashboard (Professor), Dashboard (Student), TA view, Course detail, Grade entry
- No colors yet — just boxes and labels
- Share with C++ and Qt teams to confirm data fields before coding

### TASK D-02 — Hi-fi Figma screens
**Assigned to:** Rushana
- Apply IUT branding to all wireframes
- Export color codes and font sizes for Xondamir/Nodir to match in QSS

### TASK D-03 — Presentation slides
**Assigned to:** Malika & Rushana
- Slide 1: Problem statement & system overview
- Slide 2: Class hierarchy diagram (export from our UML)
- Slide 3: OOP concepts used (with code snippets)
- Slide 4: Qt UI screenshots
- Slide 5: Team contributions & demo flow

### TASK D-04 (Bonus coding) — Exception demo writeup
**Assigned to:** Malika
- Write a small standalone `exceptions_demo.cpp`
- Create one of each custom exception class, throw and catch each one, print the message
- This is self-contained — no other classes needed
- Good starting point: copy `Exceptions.hpp` and write a `main()` that tests each one

### TASK D-05 (Bonus coding) — Operator overload demo
**Assigned to:** Rushana
- Write a standalone `operators_demo.cpp`
- Create two Student objects and demonstrate `operator==`, `operator!=`, `operator<<`
- Create two Grade objects and demonstrate `operator>` (which student scored higher)
- No Qt needed — pure C++ console output

---


## Order of Work

```
Week 1:  C-01 User → C-02 Student → C-03 Professor
Week 1:  C-05 Course → C-06 Assignment → C-07 Grade → C-08 Exceptions
Week 1:  D-01 Wireframes (Malika, in parallel)
Week 2:  C-04 TeachingAssistant → C-09 main.cpp demo
Week 2:  Q-01 Qt setup → Q-02 Login → Q-03/Q-04/Q-05 screens
Week 2:  D-02 Hi-fi screens → D-03 Slides
Ongoing: D-04 exceptions_demo (Malika) → D-05 operators_demo (Rushana)
```

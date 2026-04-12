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
│   ├── Admin.hpp / Admin.cpp
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
│   └── (saved .txt files from Course/Grade file I/O)
└── README.md
```
---
*(work in progress...)*

# Team Task Board

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

## ID Format Convention

Every user in the system gets a unique, human-readable ID generated automatically at construction.

| Role | Prefix | Example | Format |
|---|---|---|---|
| Student | `U` | `U2510001` | U + 2-digit year + 4-digit order |
| Professor | `P` | `P2510001` | P + 2-digit year + 4-digit order |
| Admin | `A` | `A2510001` | A + 2-digit year + 4-digit order |

**How it works in C++:**
```cpp
// In each subclass — static members defined in .cpp
static int nextOrderNum;   // starts at 1, increments per class
static int enrollmentYear; // e.g. 25 for 2025

// Static helper (defined in each subclass)
static string generateId(const string& prefix) {
    ostringstream oss;
    oss << prefix
        << setw(2) << setfill('0') << enrollmentYear
        << setw(4) << setfill('0') << nextOrderNum++;
    return oss.str();  // e.g. "U2510001"
}
```
Each class (`Student`, `Professor`, `Admin`) keeps its own `nextOrderNum` counter so IDs never collide across roles.

---

## C++ Tasks — Akmal & Akbarali

> **Rule:** Every class gets its own `.hpp` and `.cpp` file. No implementation inside `.hpp` except inline getters. Always compile and test before marking a task done.

---

### TASK C-01 — `User` abstract base class
**Assigned to:** Akmal
**Files:** `User.hpp`, `User.cpp`

**What to include:**
- `protected` fields: `name`, `email`, `password`, `role`, `userId` (string — stores the formatted ID like `U2510001`)
- `private static` fields: `totalUsers` (int) — counts all User instances across all subclasses
- Constructor takes `(name, email, password, role, userId)` — the formatted ID is passed in by the subclass
- Validation in constructor: empty name/email throws `InvalidUserException`, password under 6 chars throws `InvalidUserException`
- Virtual destructor — decrements `totalUsers`
- Getters: `getName()`, `getEmail()`, `getUserId()`, `getRole()` (non-virtual version returning the `role` field)
- Setters with validation: `setName()`, `setEmail()` (check for `@` character)
- Common methods: `login()`, `logout()`, `updateProfile()`, `changePassword()`
- Static: `getTotalUsers()`
- `operator==` compares by `userId` string, `operator!=`, `operator<<`
- **Pure virtual:** `getRole() const = 0`, `displayInfo() const = 0`

**How to think about it:**
> `User` itself never generates an ID — it receives one from the subclass constructor. The subclass calls its own `generateId()` static method and passes the result up to `User(...)`. This keeps ID generation logic where it belongs: in each subclass.

---

### TASK C-02 — `Student` class
**Assigned to:** Akmal
**Files:** `Student.hpp`, `Student.cpp`

**What to include:**
- Inherits: `virtual public User`
- Own static fields: `static int nextOrderNum`, `static int enrollmentYear` (default 25)
- Own static method: `static string generateId()` — returns e.g. `"U2510001"`
- Fields: `gpa` (double), `enrolledCourses` (vector\<Course*\>), `grades` (vector\<Grade\>)
- Constructor: calls `generateId()` internally, passes result to `User(name, email, password, "Student", generatedId)`
- Methods: `enrollCourse()` — throws `CourseFullException` if course at capacity, `dropCourse()`, `viewGrades()`, `calculateGPA()`, `submitAssignment()`, `viewTranscript()`, `receiveGrade()` (called by Professor or TA when scoring)
- `operator==` compares by `userId`, `operator<<`
- Override: `getRole()` returns `"Student"`, `displayInfo()`

**How to think about it:**
> `calculateGPA()` loops over the grades vector and averages all scores. `receiveGrade()` is not called by the student themselves — it is the method that Professor and TA call on a Student object to record a score. Think of it as a public "write slot" for grades.

---

### TASK C-03 — `Professor` class
**Assigned to:** Akmal
**Files:** `Professor.hpp`, `Professor.cpp`

**What to include:**
- Inherits: `virtual public User`
- Own static fields: `static int nextOrderNum`, `static int enrollmentYear`
- Own static method: `static string generateId()` — returns e.g. `"P2510001"`
- Fields: `department` (string), `taughtCourses` (vector\<Course*\>) — non-owning pointers
- Constructor: calls `generateId()`, passes to `User(...)`
- Methods:
  - `createCourse(Course* course)` — adds to `taughtCourses`
  - `assignGrade(Student&, Course&, double score)` — throws `GradeOutOfRangeException` if score not 0–100
  - `viewRoster(Course& course)` — returns `vector<Student*>` of enrolled students (replaces the old `manageRoster` print method — returns data, doesn't print, so Qt can display it)
  - `removeStudentFromCourse(Student&, Course&)` — calls `course.removeStudent()`
  - `postMaterial(string, Course&)`
  - `createAssignment(Course&, string title, double maxScore)`
  - `generateReport(Course&) const` — returns a formatted `string` via `ostringstream`
  - `assignTA(TeachingAssistant&, Course&)`
- `operator==` compares by `userId`, `operator<<`
- Override: `getRole()` returns `"Professor"`, `displayInfo()`

**How to think about it:**
> `viewRoster()` returns a vector instead of printing — this is the GUI-ready pattern. Both the console `main.cpp` and the Qt screen can call the same method and display the result however they want. Never print inside a method that Qt will also call.

---

### TASK C-04 — `TeachingAssistant` class
**Assigned to:** Akmal
**Files:** `TeachingAssistant.hpp`, `TeachingAssistant.cpp`

**What to include:**
- Inherits: `public Student, public Professor` — multiple inheritance
- No separate ID format needed — TA is still a Student, so their ID stays `U25XXXX`
- Fields: `assignedCourse` (Course*, non-owning), `hoursWorked` (int), `stipend` (double)
- Constructor initializer list **must** call `User(...)` explicitly first (virtual base rule), then `Student(...)`, then `Professor(...)`
- In practice: TA's ID is already generated by the `Student` constructor path — pass the same ID through
- Methods: `gradeAssignment()`, `postAnnouncement()`, `holdOfficeHours()`, `answerQuestion()`, `assistProfessor()`, `viewCourseRoster()`, `logHours()`, `setAssignedCourse()`
- Every method that uses `assignedCourse` must throw `runtime_error` if it is `nullptr`
- `operator==` compares by `getUserId()`, `operator<<`
- **Must** override both `getRole()` (returns `"TeachingAssistant"`) and `displayInfo()` — compiler requires this to resolve ambiguity from two parent definitions

**How to think about it:**
> The constructor initializer list is the hardest part of this whole project. With virtual inheritance, `TeachingAssistant` is responsible for calling `User(...)` directly — the calls inside `Student` and `Professor` constructors are silently skipped. Study this before writing a single line.

---

### TASK C-05 — `Admin` class
**Assigned to:** Akmal
**Files:** `Admin.hpp`, `Admin.cpp`

**What to include:**
- Inherits: `virtual public User`
- Own static fields: `static int nextOrderNum`, `static int enrollmentYear`
- Own static method: `static string generateId()` — returns e.g. `"A2510001"`
- Fields: `adminDepartment` (string — e.g. `"IT"`, `"Academic Affairs"`), `permissions` (vector\<string\>)
- Constructor: calls `generateId()`, passes to `User(...)`
- Methods:
  - `createStudent(name, email, password, year)` — constructs and returns a `Student*`, Admin is the only class that creates Students
  - `createProfessor(name, email, password, dept, year)` — constructs and returns a `Professor*`
  - `deleteUser(User* user)` — removes from system (for now just prints a confirmation)
  - `viewAllStudents(vector<Student*>&)` — prints or returns the full list
  - `viewAllProfessors(vector<Professor*>&)` — same
  - `assignProfessorToCourse(Professor&, Course&)` — calls `professor.createCourse(&course)`
  - `generateSystemReport()` — returns a string summary: total users, total courses, etc.
  - `hasPermission(string perm) const` — checks if `perm` is in the `permissions` vector
  - `addPermission(string perm)`, `revokePermission(string perm)`
- `operator==` compares by `userId`, `operator<<`
- Override: `getRole()` returns `"Admin"`, `displayInfo()`

**How to think about it:**
> Admin is the gatekeeper. In real systems, only an authorized role can create other users — students don't register themselves, an admin creates their account. `createStudent()` and `createProfessor()` are factory-style methods: they call `new Student(...)` and return the pointer. The caller (main.cpp or Qt) is responsible for storing and eventually deleting it.

---

### TASK C-06 — `Course` class
**Assigned to:** Akbarali
**Files:** `Course.hpp`, `Course.cpp`

**What to include:**
- Fields: `courseId` (string), `courseName` (string), `credits` (int), `capacity` (int), `enrolledStudents` (vector\<Student*\>), `assignments` (vector\<Assignment\>), `materials` (vector\<string\>), `announcements` (vector\<string\>), `professor` (Professor*, non-owning)
- `static int courseCount`
- Constructor: validates capacity > 0, increments `courseCount`
- Methods: `addStudent()` — throws `CourseFullException` if full, `removeStudent()`, `getEnrolledStudents()`, `addMaterial()`, `addAssignment()`, `addAnnouncement()`, `getCourseName()`, `getCourseId()`, `isFull() const`
- `operator==` compares by `courseId`, `operator<<`
- `saveToFile(string filename)` — writes each field line by line to a `.txt` file
- `static Course loadFromFile(string filename)` — reads it back, throws `FileIOException` if file not found

**How to think about it:**
> Course owns its `Assignment` objects (store by value in the vector). It does NOT own `Student` or `Professor` pointers. File format can be simple: one field per line, e.g. line 1 = courseId, line 2 = courseName, line 3 = credits, etc. `loadFromFile` reads them back in the same order.

---

### TASK C-07 — `Assignment` class
**Assigned to:** Akbarali
**Files:** `Assignment.hpp`, `Assignment.cpp`

**What to include:**
- Fields: `assignmentId` (int, auto-increment static counter), `title` (string), `dueDate` (string, format `"YYYY-MM-DD"`), `maxScore` (double), `course` (Course*, non-owning)
- Constructor: throws `invalid_argument` if `maxScore <= 0` or `title` is empty
- Methods: `getTitle()`, `getDueDate()`, `getMaxScore()`, `getAssignmentId()`
- `operator<` compares by `dueDate` string (lexicographic order works for `YYYY-MM-DD`), `operator==`, `operator<<`

**How to think about it:**
> This class represents the definition of an assignment — not a submission. A student's score on this assignment lives in the `Grade` class. Keep `Assignment` simple.

---

### TASK C-08 — `Grade` class
**Assigned to:** Akbarali
**Files:** `Grade.hpp`, `Grade.cpp`

**What to include:**
- Fields: `student` (Student*, non-owning), `assignment` (Assignment*, non-owning), `score` (double), `letterGrade` (char), `feedback` (string)
- Constructor: calls private `calculateLetterGrade()` immediately
- Private: `calculateLetterGrade()` — 90+ → A, 80+ → B, 70+ → C, 60+ → D, else F
- `setScore()` — throws `GradeOutOfRangeException` if score > assignment's maxScore or < 0, then recalculates letter grade
- Methods: `getScore()`, `getLetterGrade()`, `getFeedback()`, `setFeedback()`
- `operator>` compares scores, `operator==`, `operator<<`
- `saveToFile()`, `loadFromFile()`

**How to think about it:**
> `calculateLetterGrade()` must be called in both the constructor and `setScore()`. The letter grade must always match the score — never allow them to drift out of sync.

---

### TASK C-09 — Exception classes
**Assigned to:** Akbarali
**Files:** `Exceptions.hpp` (header-only — no `.cpp` needed)

**What to include:**
```cpp
class EnrollmentException     : public runtime_error { ... };
class CourseFullException      : public EnrollmentException { ... };
class GradeOutOfRangeException : public out_of_range { ... };
class InvalidUserException     : public invalid_argument { ... };
class FileIOException          : public runtime_error { ... };
```
Each is just a constructor that forwards a message string to the parent class:
```cpp
explicit CourseFullException(const string& msg)
    : EnrollmentException(msg) {}
```

**How to think about it:**
> The power is in the type, not the message. Code that catches `CourseFullException` knows exactly what went wrong without parsing a string. Keep all five in one `Exceptions.hpp`.

---

### TASK C-10 — `main.cpp` integration demo
**Assigned to:** Akmal + Akbarali (together, after all classes compile)
**Files:** `main.cpp`

**What to include:**
- Create 1 Admin — use Admin to create 1 Professor and 2 Students (factory pattern)
- Print all generated IDs to verify format (`U2510001`, `P2510001`, `A2510001`)
- Professor creates a Course, Admin assigns Professor to it
- Professor assigns TA to course
- Professor assigns grades to both Students
- TA grades an assignment independently
- Demonstrate polymorphism: store all users in `vector<User*>`, loop and call `getRole()` and `displayInfo()` on each
- Call `User::getTotalUsers()` — should reflect correct count
- Save a Course to file, reload it, print its name to confirm file I/O works
- Wrap every risky call in try-catch using custom exceptions

---

## Qt Tasks — Xondamir & Nodir

> Start after C-01 through C-05 compile cleanly. Qt is a wrapper — it calls C++ methods, never reimplements logic.

### TASK Q-01 — Project setup & main window
**Assigned to:** Xondamir
- Qt Creator project, link all C++ `.cpp` files
- Sidebar navigation: Dashboard, Users, Courses, Grades
- Role-based view: Admin sees user management, Professor sees courses, Student sees grades

### TASK Q-02 — Login screen
**Assigned to:** Nodir
- Email + password fields, submit button
- Calls `user.login()`, catches `runtime_error`, shows `QMessageBox` on failure

### TASK Q-03 — Admin panel (user management)
**Assigned to:** Xondamir
- Table of all students and professors
- "Create Student" / "Create Professor" buttons — calls `admin.createStudent()` / `admin.createProfessor()`
- Generated ID displayed immediately after creation

### TASK Q-04 — Course management (Professor view)
**Assigned to:** Xondamir
- List of courses, "Create course" dialog
- "View roster" calls `professor.viewRoster(course)` and displays the returned vector in a table

### TASK Q-05 — Grade entry & student dashboard
**Assigned to:** Nodir
- Professor/TA view: student dropdown, score input, calls `assignGrade()`, shows `GradeOutOfRangeException` as `QMessageBox`
- Student view: table of grades, GPA display calling `student.calculateGPA()`

---

## Design Tasks — Malika & Rushana

> IUT brand colors: Navy `#0D2D6E`, Sky Blue `#0099D6`. Fonts: DM Sans (body), Playfair Display (headings).

### TASK D-01 — Wireframes (lo-fi)
**Assigned to:** Malika
- All screens: Login, Admin panel, Professor dashboard, Student dashboard, TA view, Course detail, Grade entry
- Share with C++ team before hi-fi — confirms what data each screen needs

### TASK D-02 — Hi-fi Figma screens
**Assigned to:** Rushana
- Apply IUT branding to all wireframes
- Export color hex codes and font sizes for Xondamir/Nodir to match in Qt Style Sheets (QSS)

### TASK D-03 — Presentation slides
**Assigned to:** Malika & Rushana
- Slide 1: Problem statement & system overview
- Slide 2: Class hierarchy UML diagram
- Slide 3: OOP concepts demonstrated (with short code snippets)
- Slide 4: UI screenshots from Qt
- Slide 5: Team roles & live demo flow

### TASK D-04 — Bonus coding: Exception demo
**Assigned to:** Malika
**Files:** `demo/exceptions_demo.cpp`

Write a self-contained file (no other classes needed) that:
- Includes `Exceptions.hpp`
- In `main()`, uses try-catch blocks to throw and catch each of the 5 custom exceptions
- Prints the `.what()` message for each one
- This is about 40 lines total — a great intro to exception handling

> If the professor asks you about this file: explain what `throw` does (transfers control to the nearest matching `catch`), what `.what()` returns (the message string), and why custom exceptions are more useful than plain `runtime_error`.

### TASK D-05 — Bonus coding: Operator overload demo
**Assigned to:** Rushana
**Files:** `demo/operators_demo.cpp`

Write a self-contained file that:
- Defines two simple `Student`-like structs (or includes Student.hpp directly)
- Demonstrates `operator==`, `operator!=`, `operator<<` on two student objects
- Demonstrates `operator>` on two Grade objects (which student scored higher)
- Prints results clearly to console

> If the professor asks: explain that `operator==` returns `bool` and compares a specific field (userId), and that `operator<<` returns `ostream&` so that chaining like `cout << s1 << s2` works.

---

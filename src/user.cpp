// User.cpp — implementation
#include "User.h"

// ── Static member definitions (required outside class) ─
int User::totalUsers = 0;
int User::nextId = 1000;  // IDs start at 1000

// ── Constructor ───────────────────────────────────────
User::User(string name, string email,
    string password, string role)
    : name(name), email(email),
    password(password), role(role),
    userId(nextId++)
{
    if (name.empty() || email.empty())
        throw invalid_argument("Name and email cannot be empty");
    if (password.length() < 6)
        throw invalid_argument("Password must be at least 6 chars");
    ++totalUsers;
}

// ── Destructor ────────────────────────────────────────
User::~User() {
    --totalUsers;   // keep the count accurate
}

// ── Getters ───────────────────────────────────────────
string User::getName()   const { return name; }
string User::getEmail()  const { return email; }
int    User::getUserId() const { return userId; }

// ── Setters ───────────────────────────────────────────
void User::setName(string newName) {
    if (newName.empty())
        throw invalid_argument("Name cannot be empty");
    name = newName;
}

void User::setEmail(string newEmail) {
    if (newEmail.find('@') == string::npos)
        throw invalid_argument("Invalid email format");
    email = newEmail;
}

// ── Common methods ────────────────────────────────────
bool User::login(string inputEmail, string inputPassword) {
    if (email == inputEmail && password == inputPassword) {
        cout << "Login successful. Welcome, " << name << "!\n";
        return true;
    }
    throw runtime_error("Invalid email or password");
    return false;
}

void User::logout() {
    cout << name << " has logged out.\n";
}

void User::updateProfile(string newName, string newEmail) {
    setName(newName);    // reuse setters (with validation)
    setEmail(newEmail);
    cout << "Profile updated successfully.\n";
}

void User::changePassword(string oldPass, string newPass) {
    if (password != oldPass)
        throw runtime_error("Current password is incorrect");
    if (newPass.length() < 6)
        throw invalid_argument("New password too short");
    if (newPass == oldPass)
        throw invalid_argument("New password must differ from old");
    password = newPass;
    cout << "Password changed successfully.\n";
}

// ── Static methods ────────────────────────────────────
int User::getTotalUsers() { return totalUsers; }
void User::resetUserCount() { totalUsers = 0; nextId = 1000; }

// ── Operator overloads ────────────────────────────────
bool User::operator==(const User& other) const {
    return userId == other.userId;   // unique ID = identity
}

bool User::operator!=(const User& other) const {
    return !(*this == other);       // reuse operator==
}

ostream& operator<<(ostream& os, const User& u) {
    os << "[" << u.role << "] "
        << u.name << " <"
        << u.email << ">"
        << " #" << u.userId;
    return os;
}
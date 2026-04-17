// User.h — abstract base class declaration
#pragma once
#include <string>
#include <iostream>
#include <stdexcept>
using namespace std;

class User {
protected:
    // protected so subclasses can read directly
    string name;
    string email;
    string password;
    string role;
    int    userId;

private:
    static int totalUsers;   // shared across ALL User instances
    static int nextId;       // auto-increment ID counter

public:
    // ── Constructor & Destructor ───────────────────
    User(string name, string email,
        string password, string role);
    virtual ~User();          // virtual — required for polymorphism

    // ── Getters ───────────────────────────────────
    string getName()     const;
    string getEmail()    const;
    string getRole()     const;
    int    getUserId()   const;

    // ── Setters (with validation) ──────────────────
    void setName(string name);
    void setEmail(string email);

    // ── Common methods (all users share these) ─────
    bool login(string email, string password);
    void logout();
    void updateProfile(string newName, string newEmail);
    void changePassword(string oldPass, string newPass);

    // ── Static methods ────────────────────────────
    static int  getTotalUsers();
    static void resetUserCount();  // useful for testing

    // ── Operator overloads ────────────────────────
    bool    operator==(const User& other) const;
    bool    operator!=(const User& other) const;
    friend ostream& operator<<(ostream& os, const User& u);

    // ── Pure virtual — MUST be overridden ─────────
    virtual string getRole()     const = 0;
    virtual void   displayInfo() const = 0;
};
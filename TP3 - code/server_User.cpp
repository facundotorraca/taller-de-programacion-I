#include "server_User.h"
#include "common_Socket.h"
#include "server_LogState.h"
#include <string>
#include <cstdbool>

#include <iostream>
User::User(std::string real_user, std::string real_pass) {
    this->real_user.assign(real_user);
    this->real_pass.assign(real_pass);
    this->log_state = NotLogged;
}

void User::set_username(std::string username) {
    this->username.assign(username);
}

void User::set_password(std::string password) {
    this->password.assign(password);
}

bool User::verify_login() {
    bool pass_correct = (this->real_pass.compare(this->password) == 0);
    bool user_correct = (this->real_user.compare(this->username) == 0);

    this->password.clear();
    this->username.clear();

    if (pass_correct && user_correct) {
        this->log_state = Logged;
        return true;
    }
    this->log_state = NotLogged;
    return false;
}

bool User::logged() {
    return (this->log_state == Logged);
}

bool User::logged_out() {
    return (this->log_state == LoggedOut);
}

void User::log_out() {
    this->log_state = LoggedOut;
}

User::~User() {}

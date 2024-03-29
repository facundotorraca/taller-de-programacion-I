#include "server_CommandUser.h"
#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include "server_ProtectedSet.h"
#include <string>
#include <map>

CommandUser::CommandUser(std::string username):
    username(username)
{}

void CommandUser::execute(User& user,
                          std::map<std::string, std::string>& config,
                          ProtectedSet& directories) {
    user.set_username(this->username);
    this->answer.assign(std::string(USER) + " " +
                        config["passRequired"] + "\n");
}

void CommandUser::send_answer(Socket& socket) {
    socket.send(this->answer);
}

CommandUser::~CommandUser() {}

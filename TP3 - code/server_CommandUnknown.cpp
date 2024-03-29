#include "server_CommandUnknown.h"
#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include "server_ProtectedSet.h"
#include <string>
#include <map>

void CommandUnknown::execute(User& user,
                             std::map<std::string, std::string>& config,
                             ProtectedSet& directories) {
    if (user.logged()) {
        this->answer.assign(std::string(UNKW) + " " +
                            config["unknownCommand"] + "\n");
    } else {
        this->answer.assign(std::string(NOT_LOGG) + " " +
                            config["clientNotLogged"] + "\n");
    }
}

void CommandUnknown::send_answer(Socket& socket) {
    socket.send(this->answer);
}

CommandUnknown::~CommandUnknown() {}

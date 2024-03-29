#ifndef _COMMAND_HELP_H_
#define _COMMAND_HELP_H_

#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include "server_ProtectedSet.h"
#include <string>
#include <map>

class CommandHelp : public Command {
    std::string answer;

    public:
        void execute(User& user,
                     std::map<std::string, std::string>& config,
                     ProtectedSet& directories);

        void send_answer(Socket& socket);
};

#endif

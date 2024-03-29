#include "server_Server.h"
#include "server_FileError.h"
#include "server_ThreadClient.h"
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <cstdbool>
#include <iostream>

Server::Server(const std::string port, const std::string filename) {
    this->load_configs(filename);
    this->acceptor = new ThreadAcceptor(port,
                                        this->config,
                                        this->directories,
                                        this->clients);
}

void Server::load_configs(const std::string filename) {
    std::ifstream f_conf;
    f_conf.open(filename);
    if (!f_conf.is_open()) {
        throw FileError("File Open Failed");
    }

    std::string line;
    while (getline(f_conf, line)) {
        size_t pos_delim = line.find('=');

        std::string key = line.substr(0, pos_delim);
        std::string val = line.substr(pos_delim + 1, std::string::npos);

        this->config.insert(std::pair<std::string, std::string>(key, val));
    }
    f_conf.close();
}

void Server::wait_quit() {
    char input;
    do {
        input = std::cin.get();
    } while (input != 'q');
}

void Server::stop_clients() {
    for (size_t i = 0; i < clients.size(); i++ ) {;
        this->clients[i]->stop();
        this->clients[i]->join();
        delete this->clients[i];
    }
}

void Server::start() {
    this->acceptor->start();
    this->wait_quit();
    this->stop_clients();

    this->acceptor->stop();
    this->acceptor->join();
    delete this->acceptor;
}

Server::~Server() {}

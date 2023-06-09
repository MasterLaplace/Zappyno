/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Client
*/

#include "../../includes/Client.hpp"

namespace Manager {
    Client::Client(const std::string &ip, const unsigned short port) {
        this->socket = std::make_unique<Network::Socket>();
        this->socket->setupServerAddress(ip, port);
        this->socket->connectToServer();
        this->resetBuffer();
        this->resetReadfds();
        this->resetTimeout();
    }

    void Client::sendToServer(const std::string &message) {
        send(this->socket->getClientSocket(), message.c_str(), message.length(), 0);
    }

    std::string Client::receiveFromServer() {
        std::string tmp = "";
        ssize_t n = 0;

        if (select(this->socket->getClientSocket() + 1, &this->readfds, NULL, NULL, &this->timeout) < 0)
            throw std::runtime_error("Select failed.");
        if (FD_ISSET(this->socket->getClientSocket(), &this->readfds)) {
            if ((n = read(this->socket->getClientSocket(), this->buffer, BUFFER_SIZE)) <= 0)
                return "";
            tmp += std::string(this->buffer, n);
            if (tmp.find("\n") == std::string::npos) {
                this->resetBuffer();
                tmp += this->receiveFromServer();
            }
            this->resetBuffer();
        }
        this->resetReadfds();
        this->resetTimeout();
        return tmp;
    }
} // namespace Manager

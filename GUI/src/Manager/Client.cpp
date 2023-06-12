/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Client
*/

#include "../../includes/Client.hpp"

namespace Manager {
    void Client::setSocket(const std::string &ip, const unsigned short port) {
        this->resetSocket();
        this->socket->setupServerAddress(ip, port);
        this->socket->connectToServer();
    }

    void Client::resetSocket() {
        this->closeConnection();
        this->socket = std::make_unique<Network::Socket>();
        this->resetBuffer();
        this->resetReadfds();
        this->resetTimeout();
    }

    void Client::sendToServer(const std::string &message) {
        if (!this->socket)
            throw std::runtime_error("Socket is not set.");
        send(this->socket->getClientSocket(), message.c_str(), message.length(), 0);
    }

    std::string Client::receiveFromServer() {
        std::string tmp = "";
        ssize_t n = 0;

        if (!this->socket)
            throw std::runtime_error("Socket is not set.");
        if (select(this->socket->getClientSocket() + 1, &this->readfds, NULL, NULL, &this->timeout) < 0)
            throw std::runtime_error("Select failed.");
        if (FD_ISSET(this->socket->getClientSocket(), &this->readfds)) {
            if ((n = read(this->socket->getClientSocket(), this->buffer, BUFFER_SIZE)) <= 0)
                return "";
            tmp += std::string(this->buffer, n);
            if (tmp[tmp.length() - 1] != '\n') {
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

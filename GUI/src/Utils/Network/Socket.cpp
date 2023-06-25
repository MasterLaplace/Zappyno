/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Socket
*/

#include "../../../includes/Socket.hpp"

namespace Network {
    Socket::Socket() {
        if ((this->clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            throw std::runtime_error("Failed to create socket.");
    }

    void Socket::setupServerAddress(const std::string &ip, const unsigned short port) {
        this->serverAddress.sin_family = AF_INET;
        this->serverAddress.sin_port = htons(port);
        if (inet_pton(AF_INET, this->hostname_to_ip(ip), &this->serverAddress.sin_addr) <= 0)
            throw std::runtime_error("Invalid address/Address not supported.");
    }

    void Socket::connectToServer() {
        if (connect(this->clientSocket, (struct sockaddr*)&(this->serverAddress), sizeof(this->serverAddress)) < 0)
            throw std::runtime_error("Connection failed.");
    }

    const char *Socket::hostname_to_ip(const std::string &hostname) {
        struct hostent *he;
        struct in_addr **addr_list;

        if (!(he = gethostbyname(hostname.c_str())))
            throw std::runtime_error("Failed to get hostname.");

        addr_list = (struct in_addr **) he->h_addr_list;

        if (*addr_list)
            return inet_ntoa(*addr_list[0]);
        return "127.0.0.1";
    }
} // namespace Network

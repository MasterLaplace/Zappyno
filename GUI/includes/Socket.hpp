/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Socket
*/

#ifndef SOCKET_HPP_
    #define SOCKET_HPP_
    #include <iostream>
    #include <cstdlib>
    #include <cstring>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <sys/time.h>

namespace Network {
    class Socket {
        public:
            Socket();
            ~Socket() { close(this->clientSocket); }

            /**
             * @brief Set the Server Address object with the server IP and port
             *
             * @param serverIP  The server IP
             * @param port  The server port
             */
            void setupServerAddress(const std::string &ip, const unsigned short port);

            /**
             * @brief Connect to the server with the server address set before
             *
             */
            void connectToServer();

            /**
             * @brief Get the Client Socket object
             *
             * @return int  The client socket
             */
            int getClientSocket() { return this->clientSocket; }

        private:
            int clientSocket;
            sockaddr_in serverAddress;
    };
}

#endif /* !SOCKET_HPP_ */

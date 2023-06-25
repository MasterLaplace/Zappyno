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
    #include <netdb.h>
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

            /**
             * @brief Get the Server Address object with the server IP and port
             *
             * @param hostname  The server IP or hostname (ex: localhost)
             * @return const char*  The server IP address (ex: 127.0.0.1)
             */
            const char *hostname_to_ip(const std::string &hostname);

        private:
            int clientSocket;
            sockaddr_in serverAddress;
    };
}

#endif /* !SOCKET_HPP_ */

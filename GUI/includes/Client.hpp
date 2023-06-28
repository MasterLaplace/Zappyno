/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Client
*/

#ifndef CLIENT_HPP_
    #define CLIENT_HPP_
    #define MAX_PORT 0xFFFF
    #define MIN_PORT 0x0001
    #define BUFFER_SIZE 4096
    #include "Socket.hpp"
    #include <memory>

namespace Manager {
    class Client {
        public:
            Client() = default;
            Client(const std::string &ip, const unsigned short port) { this->setSocket(ip, port); }
            ~Client() = default;

            void resetBuffer() { memset(buffer, 0, BUFFER_SIZE); }
            void resetReadfds() { FD_ZERO(&this->readfds); FD_SET(this->socket->getClientSocket(), &this->readfds); }
            void resetTimeout() { timeout.tv_sec = 0; timeout.tv_usec = 1000000 / this->_framerate; }

            void setFramerate(unsigned framerate) { this->_framerate = framerate; }
            unsigned getFramerate() const { return this->_framerate; }

            /**
             * @brief Set the Socket object and reset buffer, readfds and timeout
             *
             * @param ip  IP address
             * @param port  Port
             */
            void setSocket(const std::string &ip, const unsigned short port);

            /**
             * @brief Reset socket, buffer, readfds and timeout
             *
             */
            void resetSocket();

            /**
             * @brief Send message to server
             *
             * @param message  Message to send
             */
            void sendToServer(const std::string &message);

            /**
             * @brief Receive message from server and return it
             *
             * @return std::string  Message received
             */
            std::string receiveFromServer();

            void closeConnection() { this->socket = nullptr; }

        protected:
        private:
            std::unique_ptr<Network::Socket> socket = nullptr;
            fd_set readfds = {0};
            timeval timeout;
            char buffer[BUFFER_SIZE] = {0};
            unsigned _framerate = 30;
    };
} // namespace Manager

#endif /* !CLIENT_HPP_ */

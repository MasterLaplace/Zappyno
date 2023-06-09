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
            Client(const std::string &ip, const unsigned short port);
            ~Client() = default;

            void resetBuffer() { memset(buffer, 0, BUFFER_SIZE); }
            void resetReadfds() { FD_ZERO(&this->readfds); FD_SET(this->socket->getClientSocket(), &this->readfds); }
            void resetTimeout() { timeout.tv_sec = 0; timeout.tv_usec = 1000000 / this->_framerate; }

            void setFramerate(unsigned framerate) { this->_framerate = framerate; }
            unsigned getFramerate() const { return this->_framerate; }

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
            std::unique_ptr<Network::Socket> socket;
            fd_set readfds;
            timeval timeout;
            char buffer[BUFFER_SIZE];
            unsigned _framerate = 60;
    };
} // namespace Manager

#endif /* !CLIENT_HPP_ */

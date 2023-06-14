/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Protocol
*/


#ifndef PROTOCOL_HPP_
    #define PROTOCOL_HPP_
    #include "Tiles.hpp"
    #include "StringManager.hpp"
    #include "Client.hpp"
    #include <functional>

/**
 * @brief Protocol class
 *
*/
namespace Manager {
    class Protocol {
        public:
            Protocol() {
                commands["msz"] = [this](std::string &str) { msz(str); };
            }
            ~Protocol() = default;

            void parseCommand(std::string &str, std::shared_ptr<Client> client);


            void setMapSize(std::string &str) { _mapSize = Math::Vector(String::string_to_string_vector(str, " ")); }
            Math::Vector getMapSize() const { return _mapSize; }

        protected:
        private:
            Math::Vector _mapSize = {10, 10};
            std::map<const std::string /*name*/, std::function<void(std::string&)>> commands;
            std::vector<std::string> _teams;
            unsigned _timeUnit = 100;
    };
} // namespace Manager

#endif /* !PROTOCOL_HPP_ */

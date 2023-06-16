/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Protocol
*/


#ifndef PROTOCOL_HPP_
    #define PROTOCOL_HPP_
    #include "Tiles.hpp"
    #include "Trantorian.hpp"
    #include "StringManager.hpp"
    #include "Chat.hpp"
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
                commands["bct"] = [this](std::string &str) { bct(str); };
                commands["tna"] = [this](std::string &str) { tna(str); };
                commands["pnw"] = [this](std::string &str) { pnw(str); };
                commands["ppo"] = [this](std::string &str) { ppo(str); };
                commands["plv"] = [this](std::string &str) { plv(str); };
                commands["pin"] = [this](std::string &str) { pin(str); };
                commands["pex"] = [this](std::string &str) { pex(str); };
                commands["pbc"] = [this](std::string &str) { pbc(str); };
                commands["pic"] = [this](std::string &str) { pic(str); };
                commands["pie"] = [this](std::string &str) { pie(str); };
                commands["pfk"] = [this](std::string &str) { pfk(str); };
                commands["pdr"] = [this](std::string &str) { pdr(str); };
                commands["pgt"] = [this](std::string &str) { pgt(str); };
                commands["pdi"] = [this](std::string &str) { pdi(str); };
                commands["enw"] = [this](std::string &str) { enw(str); };
            }
            ~Protocol() = default;

            void parseCommand(std::string &str, std::shared_ptr<Client> client);

            /**
             * @brief map size (width, height)
             *
             * @param str  msz X Y\n
             */
            void msz(std::string &str);

            /**
             * @brief content of a tile (x, y, q0, q1, q2, q3, q4, q5, q6)
             *
             * @param str  bct X Y q0 q1 q2 q3 q4 q5 q6\n
             */
            void bct(std::string &str);

            /**
             * @brief name of all the teams
             *
             * @param str  tna N\n * nbr_teams
             */
            void tna(std::string &str);

            /**
             * @brief connection of a new player (id, x, y, orientation, level, team name)
             *
             * @param str  pnw n X Y O L N\n
             */
            void pnw(std::string &str);

            /**
             * @brief player’s position and orientation (id, x, y, orientation)
             *
             * @param str  ppo n X Y O\n
             */
            void ppo(std::string &str);

            /**
             * @brief player’s level (id, level)
             *
             * @param str  plv n L\n
             */
            void plv(std::string &str);

            /**
             * @brief player’s inventory (id, food, linemate, deraumere, sibur, mendiane, phiras, thystame)
             *
             * @param str  pin n X Y q0 q1 q2 q3 q4 q5 q6\n
             */
            void pin(std::string &str);

            /**
             * @brief expulsion by a player (id)
             *
             * @param str  pex n\n
             */
            void pex(std::string &str);

            /**
             * @brief broadcast (id, message)
             *
             * @param str  pbc n M\n
             */
            void pbc(std::string &str);

            /**
             * @brief start of an incantation (by the first player)
             *
             * @param str  pic X Y L n n . . . \n
             */
            void pic(std::string &str);

            /**
             * @brief end of an incantation (by the first player)
             *
             * @param str  pie X Y R\n
             */
            void pie(std::string &str);

            /**
             * @brief egg laying by the player (id of the player)
             *
             * @param str  pfk n\n
             */
            void pfk(std::string &str);

            /**
             * @brief resource dropping by the player (id of the player, id of the resource)
             *
             * @param str  pdr n i\n
             */
            void pdr(std::string &str);

            /**
             * @brief resource collecting by the player (id of the player, id of the resource)
             *
             * @param str  pgt n i\n
             */
            void pgt(std::string &str);

            /**
             * @brief death of a player (id) (remove from map)
             *
             * @param str  pdi n\n
             */
            void pdi(std::string &str);

            /**
             * @brief egg laying by the player (id of the player, id of the egg)
             *
             * @param str  enw e n X Y\n
             */
            void enw(std::string &str);

            void setMapSize(std::string &str) { _mapSize = Math::Vector(String::string_to_string_vector(str, " ")); }
            Math::Vector getMapSize() const { return _mapSize; }

            void setTrantorians(std::vector<GUI::Trantorian> trantorians) { _trantorians = trantorians; }
            void setEggs(std::vector<GUI::Egg> eggs) { _eggs = eggs; }

            std::vector<GUI::Trantorian> getTrantorians() const { return _trantorians; }
            std::vector<GUI::Egg> getEggs() const { return _eggs; }
            GUI::Trantorian getTrantorian(unsigned id) const;

            void addTrantorian(GUI::Trantorian trantorian) { _trantorians.push_back(trantorian); }
            void addEgg(GUI::Egg egg) { _eggs.push_back(egg); }

            void deleteTrantorian(unsigned id);
            void deleteEgg(unsigned id);

            std::shared_ptr<Interface::Chat> getChat() const { return _chat; }
            void setChat(std::shared_ptr<Interface::Chat> chat) { _chat = chat; }

        protected:
        private:
            std::vector<GUI::Tiles> _tiles;
            std::vector<GUI::Trantorian> _trantorians;
            std::vector<GUI::Egg> _eggs;
            Math::Vector _mapSize = {10, 10};
            std::map<const std::string /*name*/, std::function<void(std::string&)>> commands;
            std::vector<std::string /*name*/> _teams;
            unsigned _timeUnit = 100;
            std::shared_ptr<Interface::Chat> _chat = nullptr;
    };
} // namespace Manager

#endif /* !PROTOCOL_HPP_ */

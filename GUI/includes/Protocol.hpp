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
    #include "Chat.hpp"
    #include "Button.hpp"
    #include "Client.hpp"
    #include "Text.hpp"
    #include <functional>

/**
 * @brief Protocol class
 *
*/
namespace Manager {
    class Protocol {
        public:
            Protocol(std::shared_ptr<sf::RenderWindow> &window) {
                _window = window;
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
                commands["ebo"] = [this](std::string &str) { ebo(str); };
                commands["edi"] = [this](std::string &str) { edi(str); };
                commands["sgt"] = [this](std::string &str) { sgt(str); };
                commands["sst"] = [this](std::string &str) { sst(str); };
                commands["seg"] = [this](std::string &str) { seg(str); };
                commands["smg"] = [this](std::string &str) { smg(str); };
                commands["suc"] = [this](std::string &str) { suc(str); };
                commands["sbp"] = [this](std::string &str) { sbp(str); };
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

            /**
             * @brief player connection for an egg (id of the egg)
             *
             * @param str  ebo e\n
             */
            void ebo(std::string &str);

            /**
             * @brief death of an egg (id) (remove from map)
             *
             * @param str  edi e\n
             */
            void edi(std::string &str);

            /**
             * @brief time unit request (time unit)
             *
             * @param str  sgt T\n
             */
            void sgt(std::string &str);

            /**
             * @brief time unit modification (time unit)
             *
             * @param str  sst T\n
             */
            void sst(std::string &str);

            /**
             * @brief end of the game (team name)
             *
             * @param str  seg N\n
             */
            void seg(std::string &str);

            /**
            * @brief message from the server (message)
             *
             * @param str  smg M\n
             */
            void smg(std::string &str);

            /**
             * @brief throw unknown command
             *
             * @param str  suc\n
             */
            void suc(std::string &str);

            /**
             * @brief throw command parameter error
             *
             * @param str  sbp\n
             */
            void sbp(std::string &str);

            void setMapSize(std::string &str) { _mapSize = Math::Vector(String::string_to_string_vector(str, " ")); }
            Math::Vector getMapSize() const { return _mapSize; }

            void setScaleTile(double scale) { _scale = scale; }
            double getScaleTile() const { return _scale; }

            void move_map(Math::Vector pos) {
                for (auto &tile : _tiles) {
                    tile.setPos(tile.getPos() + pos);
                    for (auto &food : tile.getFoods())
                        food.setPos(food.getPos() + pos);
                    for (auto &trantorian : tile.getTrantorians())
                        trantorian->setPos(trantorian->getPos() + pos);
                    for (auto &egg : tile.getEggs())
                        egg->setPos(egg->getPos() + pos);
                }
            }

            void updatePosition() {
                unsigned x = 0;
                unsigned y = 0;
                for (auto &tile : _tiles) {
                    if (x == _mapSize.x())
                        x = 0, y++;
                    if (_scale <= 0) {
                        x++;
                        continue;
                    }
                    auto size = tile.getSize();
                    auto screen_size = _window->getSize();
                    Math::Vector np = {((screen_size.x / 2) - ((size.x()*_scale) * _mapSize.x() / 2)) + (size.x()*_scale) * x, ((screen_size.y / 2) - ((size.y()*_scale) * _mapSize.y() / 2)) + (size.y()*_scale) * y};
                    tile.setPos(np);
                    tile.setScale({_scale, _scale});
                    for (auto &food : tile.getFoods()) {
                        if (_scale <= 0)
                            continue;
                        auto ns = _scale * tile.getScaleRatio();
                        food.setScale({ns, ns});
                        food.setPos({np.x() + (size.x() * _scale / 2) - (food.getSize().x() * ns / 2), np.y() + (size.y() * _scale / 2) - (food.getSize().y() * ns / 2)});
                    }
                    x++;
                }
            }

            void deleteEgg(unsigned id) {
                for (auto &tile : _tiles) {
                    for (auto it = tile.getEggs().begin(); it != tile.getEggs().end(); it++) {
                        if ((*it)->getId() == id) {
                            tile.getEggs().erase(it);
                            return;
                        }
                    }
                }
            }

            GUI::Tiles &getTile(Math::Vector pos);
            std::shared_ptr<GUI::Trantorian> getTile(unsigned id);
            std::shared_ptr<GUI::Egg> getEgg(unsigned id);

            std::shared_ptr<Interface::Chat> getChat() const { return _chat; }
            void setChat(std::shared_ptr<Interface::Chat> chat) { _chat = chat; }

            void setTextInventoryUser(std::shared_ptr<std::vector<Interface::Text>> text_user) { _text_user = text_user; }
            void setTextInventoryCase(std::shared_ptr<std::vector<Interface::Text>> text_case) { _text_case = text_case; }

            std::vector<unsigned> getUserData(unsigned id) {
                std::vector<unsigned> data(7);
                if (_tiles.size() > id || _tiles.empty())
                    return std::vector<unsigned>(7, 0);
                for (auto food : _tiles[id].getFoods()) {
                    data[static_cast<size_t>(food.getType())]++;
                }
                std::cout << "[getuserdata]" << std::endl;
                return data;
            }

            std::vector<unsigned> getCaseData(unsigned id) {
                std::vector<unsigned> data(7);
                if (_tiles.size() > id || _tiles.empty())
                    return std::vector<unsigned>(7, 0);
                for (auto food : _tiles[id].getFoods()) {
                    data[static_cast<size_t>(food.getType())]++;
                }
                std::cout << "[getcasedata]" << std::endl;
                return data;
            }

            void setWinnerTeam(std::string team) { _winnerTeam = team; }
            std::string getWinnerTeam() const { return _winnerTeam; }

            std::vector<Interface::CALLBACK> getCallback() const {
                std::vector<Interface::CALLBACK> callback;
                callback.push_back(_gotoResult);
                return callback;
            }

            void draw() {
                for (auto &tile : _tiles)
                    tile.drawTile();
                for (auto &tile : _tiles) {
                    tile.drawFoods();
                    tile.drawTrantorians();
                    tile.drawEggs();
                }
            }

        protected:
        private:
            std::vector<GUI::Tiles> _tiles;
            Math::Vector _mapSize = {10, 10};
            double _scale = 1;
            std::map<const std::string /*name*/, std::function<void(std::string&)>> commands;
            std::vector<std::string /*name*/> _teams;
            unsigned _timeUnit = 100;
            std::shared_ptr<Interface::Chat> _chat = nullptr;
            std::string _winnerTeam = "";
            Interface::CALLBACK _gotoResult = Interface::CALLBACK::NONE;
            std::shared_ptr<sf::RenderWindow> _window = nullptr;
            std::shared_ptr<std::vector<Interface::Text>> _text_user = nullptr;
            std::shared_ptr<std::vector<Interface::Text>> _text_case = nullptr;
    };
} // namespace Manager

#endif /* !PROTOCOL_HPP_ */

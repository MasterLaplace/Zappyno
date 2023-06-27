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

/*
SYMBOL MEANING
X width or horizontal position
Y height or vertical position
q0 resource 0 (food) quantity
q1 resource 1 (linemate) quantity
q2 resource 2 (deraumere) quantity
q3 resource 3 (sibur) quantity
q4 resource 4 (mendiane) quantity
q5 resource 5 (phiras) quantity
q6 resource 6 (thystame) quantity
n player number
O orientation: 1(N), 2(E), 3(S), 4(W)
L player or incantation level
e egg number
T time unit
N name of the team
R incantation result
M message
i resource number
*/

/**
 * @brief Protocol class
 *
 * SERVER CLIENT DETAILS
 * msz X Y\n msz\n map size                         // OK
 * bct X Y q0 q1 q2 q3 q4 q5 q6\n bct X Y\n content of a tile           // OK
 * bct X Y q0 q1 q2 q3 q4 q5 q6\n * nbr_tiles mct\n content of the map (all the tiles)  // OK
 * tna N\n * nbr_teams tna\n name of all the teams  // OK
 * pnw #n X Y O L N\n connection of a new player    // NEED TO BE CHECKED
 * ppo n X Y O\n ppo #n\n player’s position         // OK
 * plv n L\n plv #n\n player’s level                // OK
 * pin n X Y q0 q1 q2 q3 q4 q5 q6\n pin #n\n player’s inventory         // OK
 * pex n\n expulsion                                // OK
 * pbc n M\n broadcast                              // OK
 * pic X Y L n n . . . \n start of an incantation (by the first player) // OK
 * pie X Y R\n end of an incantation                // OK
 * pfk n\n egg laying by the player                 // OK
 * pdr n i\n resource dropping                      // OK
 * pgt n i\n resource collecting                    // OK
 * pdi n\n death of a player                        // OK
 * enw e n X Y\n an egg was laid by a player        // OK
 * ebo e\n player connection for an egg             // OK
 * edi e\n death of an egg                          // OK
 * sgt T\n sgt\n time unit request                  // OK
 * sst T\n sst T\n time unit modification           // OK
 * seg N\n end of game                              // OK
 * smg M\n message from the server                  // OK
 * suc\n unknown command                            // OK
 * sbp\n command parameter                          // OK
*/
namespace Manager {
    class Protocol {
        public:
            Protocol(std::shared_ptr<sf::RenderWindow> &window, std::shared_ptr<Client> client) {
                _window = window;
                _client = client;
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
                // msz X Y\n msz\n map size // je m'en fout
                // bct X Y q0 q1 q2 q3 q4 q5 q6\n bct X Y\n content of a tile // je m'en fout
                // bct X Y q0 q1 q2 q3 q4 q5 q6\n * nbr_tiles mct\n content of the map (all the tiles)
                // tna N\n * nbr_teams tna\n name of all the teams // je m'en fout
                // ppo n X Y O\n ppo #n\n player’s position
                // plv n L\n plv #n\n player’s level
                // pin n X Y q0 q1 q2 q3 q4 q5 q6\n pin #n\n player’s inventory
                // sgt T\n sgt\n time unit request
                // sst T\n sst T\n time unit modification
            }
            ~Protocol() = default;

            void parseCommand(std::string &str);

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

            void move_map(Math::Vector pos);
            void updatePosition();

            void deleteEgg(unsigned id);

            GUI::Tiles &getTile(Math::Vector pos);
            std::shared_ptr<GUI::Trantorian> getTile(unsigned id);
            std::shared_ptr<GUI::Egg> getEgg(unsigned id);
            std::vector<std::string> getScore();

            void setTextInventoryUser(std::shared_ptr<std::vector<Interface::Text>> text_user) { _text_user = text_user; }
            void setTextInventoryCase(std::shared_ptr<std::vector<Interface::Text>> text_case) { _text_case = text_case; }

            std::vector<unsigned> getUserData(unsigned id);
            std::vector<unsigned> getCaseData(unsigned id);

            void setWinnerTeam(std::string team) { _winnerTeam = team; }
            std::string getWinnerTeam() const { return _winnerTeam; }

            int getCallbackTileId();
            int getCallbackUserId();

            void updateProtocol(const Math::Vector &mousePos, const bool &mousePressed = false) {
                int id = 0;

                for (auto &tile : _tiles) {
                    tile.updateTile(mousePos, mousePressed, _userId, _scale);
                    if (tile.getState() == Interface::Checkbox::State::RELEASED)
                        _tileId = id;
                    // std::cout << "[updateProtocol] Tile " << id << " clicked" << std::endl;
                    id++;
                }
            }

            void animationProtocol() {
                for (auto &tile : _tiles) {
                    tile.animationTile();
                }
            }

            void sendTileToServer(int i, int j) {
                static bool id = false;
                if (!id) { id = true; return; };
                // ppo n X Y O\n ppo #n\n player’s position
                // plv n L\n plv #n\n player’s level
                // pin #n\n player’s inventory
                if (i + j * _mapSize.y() >= int(_tiles.size()))
                    return;
                for (auto &trantorian : _tiles[i + j * _mapSize.x()].getTrantorians()) {
                    std::string str = "ppo " + std::to_string(trantorian->getId()) + "\n";
                    _client->sendToServer(str);
                    str = "plv " + std::to_string(trantorian->getId()) + "\n";
                    _client->sendToServer(str);
                    str = "pin " + std::to_string(trantorian->getId()) + "\n";
                    _client->sendToServer(str);
                }
            }

            std::vector<Interface::CALLBACK> getCallback() const {
                std::vector<Interface::CALLBACK> callback;
                callback.push_back(_gotoResult);
                if (_tileId >= 0 && _tileId < int(_tiles.size()))
                    callback.push_back(_tiles[_tileId].getCallback());
                if (_userId >= 0 && _userId < int(_tiles.size()))
                    callback.push_back(_tiles[_userId].getCallback());
                return callback;
            }

            void draw();

        protected:
        private:
            std::vector<GUI::Tiles> _tiles;
            Math::Vector _mapSize = {10, 10};
            double _scale = 1;
            std::map<const std::string /*name*/, std::function<void(std::string&)>> commands;
            std::vector<std::string /*name*/> _teams;
            unsigned _timeUnit = 100;
            int _tileId = -1;
            int _userId = -1;
            std::string _winnerTeam = "";
            Interface::CALLBACK _gotoResult = Interface::CALLBACK::NONE;
            std::shared_ptr<sf::RenderWindow> _window = nullptr;
            std::shared_ptr<std::vector<Interface::Text>> _text_user = nullptr;
            std::shared_ptr<std::vector<Interface::Text>> _text_case = nullptr;
        public:
            std::shared_ptr<Manager::Client> _client = nullptr;
            std::string message = "";
    };
} // namespace Manager

#endif /* !PROTOCOL_HPP_ */

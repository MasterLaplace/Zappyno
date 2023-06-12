/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Xml
*/

#ifndef XML_HPP_
    #define XML_HPP_
    #include <iostream>
    #include <fstream>
    #include <map>
    #include <cstring>
    #include <regex>
    #include "StringManager.hpp"

namespace Parser {
    class Xml {
        public:
            Xml() = default;
            ~Xml() = default;

            void loadFile(std::string path);
            void clear() { _attributes.clear(); }

            std::string getAttribute(std::string pathname, std::string className, std::string tileName, std::string key) const;
            std::vector<std::string> getAttributes(std::string pathname, std::string tileName) const;
            std::vector<std::map<std::string, std::string>> getTiles(std::string pathname, std::string type) const;

        protected:
        private:
            /* Path: GUI/ressources/scene.xml
            <Panels>
                <Panel name="stat" position="0, 0"/>
            </Panels>
            */
            std::map<std::string /*pathname*/, // ex: "GUI/ressources/scene.xml"
            std::map<std::string /*class*/, // ex: "Panels"
            std::map<std::string /*token*/, // ex: "Panel"
            std::map<std::string /*attribute*/, // ex: "position"
            std::string /*value*/ // ex: "0, 0"
            >>>> _attributes;
    };
} // namespace Parser

#endif /* !XML_HPP_ */

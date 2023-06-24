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

            /**
             * @brief Load the xml file and store all attributes in a map (see _attributes)
             *
             * @param path  the path to the xml file, ex: "GUI/ressources/scene.xml"
             */
            void loadFile(std::string path);
            void clear() { _attributes.clear(); }

            /**
             * @brief Get the Attribute object from the xml file (one attribute of a tile)
             *
             * @param pathname  ex: "GUI/ressources/scene.xml"
             * @param className  ex: "Panels"
             * @param tileName  ex: "Panel"
             * @param key  ex: "position"
             * @return std::string  ex: "0, 0"
             */
            std::string getAttribute(std::string pathname, std::string className, std::string tileName, std::string key) const;

            /**
             * @brief Get the Attributes object from the xml file (all attributes of a tile)
             *
             * @param pathname  ex: "GUI/ressources/scene.xml"
             * @param tileName  ex: "Panel"
             * @return std::vector<std::string>  ex: ["0, 0", "0, 0"]
             */
            std::vector<std::string> getAttributes(std::string pathname, std::string tileName) const;

            /**
             * @brief Get the Tiles object from the xml file (all tiles of a class)
             *
             * @param pathname  ex: "GUI/ressources/scene.xml"
             * @param type  ex: "Panel"
             * @return std::vector<std::map<std::string, std::string>>  ex: [{"position": "0, 0"}, {"position": "0, 0"}]
             */
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

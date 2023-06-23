/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Xml
*/

#include "../../../includes/Xml.hpp"

namespace Parser {
    void Xml::loadFile(std::string pathname)
    {
        if (pathname.empty() || _attributes.find(pathname) != _attributes.end())
            return;

        std::ifstream myfile(pathname);
        std::string line;

        if (myfile.is_open()) {
            std::regex token_regex("name=\"([^\"]*)\"");
            std::regex data_regex(" ([a-z0-9]+)=\"([^\"]*)\"");
            std::regex balise_regex("<([a-zA-Z]+)?>");
            std::string balise;
            bool isComented = false;

            while (std::getline(myfile, line)) {
                // Skip commented lines
                if (line.find("<!--") != std::string::npos && line.find("-->") != std::string::npos)
                    continue;
                if (line.find("<!--") != std::string::npos)
                    isComented = true;
                if (line.find("-->") != std::string::npos)
                    isComented = false;
                if (isComented)
                    continue;

                std::smatch token_match;
                std::smatch balise_match;
                if (std::regex_search(line, balise_match, balise_regex))
                    balise = balise_match[1];
                if (std::regex_search(line, token_match, token_regex)) {
                    std::string token = token_match[1];
                    std::map<std::string, std::string> data;
                    std::string::const_iterator start = line.cbegin();
                    std::string::const_iterator end = line.cend();
                    std::smatch data_match;
                    while (std::regex_search(start, end, data_match, data_regex)) {
                        data[data_match[1]] = data_match[2];
                        start = data_match[0].second;
                    }
                    _attributes[pathname][balise][token] = data;
                }
            }
            myfile.close();
        } else {
            throw std::runtime_error("Unable to open file");
        }
    }

    std::string Xml::getAttribute(std::string pathname, std::string className, std::string tokenName, std::string attributeName) const
    {
        auto pathIt = _attributes.find(pathname);
        if (pathIt == _attributes.end()) {
            return "";
        }
        const std::map<std::string, std::map<std::string, std::map<std::string, std::string>>>& classMap = pathIt->second;
        auto classIt = classMap.find(className);
        if (classIt == classMap.end()) {
            return "";
        }
        const std::map<std::string, std::map<std::string, std::string>>& tokenMap = classIt->second;
        auto tokenIt = tokenMap.find(tokenName);
        if (tokenIt == tokenMap.end()) {
            return "";
        }
        const std::map<std::string, std::string>& attributeMap = tokenIt->second;
        auto attributeIt = attributeMap.find(attributeName);
        if (attributeIt == attributeMap.end()) {
            return "";
        }
        return attributeIt->second;
    }

    std::vector<std::string> Xml::getAttributes(std::string pathname, std::string tileName) const
    {
        auto pathIt = _attributes.find(pathname);
        if (pathIt == _attributes.end()) {
            return {};
        }
        const std::map<std::string, std::map<std::string, std::map<std::string, std::string>>>& classMap = pathIt->second;
        auto classIt = classMap.find(tileName);
        if (classIt == classMap.end()) {
            return {};
        }
        const std::map<std::string, std::map<std::string, std::string>>& tokenMap = classIt->second;
        std::vector<std::string> attributes;
        for (auto it = tokenMap.begin(); it != tokenMap.end(); ++it) {
            attributes.push_back(it->first);
        }
        return attributes;
    }

    std::vector<std::map<std::string, std::string>> Xml::getTiles(std::string pathname, std::string type) const
    {
        auto pathIt = _attributes.find(pathname);
        if (pathIt == _attributes.end()) {
            return {};
        }
        const std::map<std::string, std::map<std::string, std::map<std::string, std::string>>>& classMap = pathIt->second;
        std::vector<std::map<std::string, std::string>> tiles;
        for (auto it = classMap.begin(); it != classMap.end(); ++it) {
            if (it->first == type) {
                const std::map<std::string, std::map<std::string, std::string>>& tokenMap = it->second;
                for (auto it2 = tokenMap.begin(); it2 != tokenMap.end(); ++it2) {
                    tiles.push_back(it2->second);
                }
            }
        }
        return tiles;
    }
} // namespace Parser

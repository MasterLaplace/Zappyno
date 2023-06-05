/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Obj
*/

#ifndef OBJ_HPP_
    #define OBJ_HPP_
    #include <string>
    #include <iostream>
    #include <fstream>
    #include <cstring>
    #include <vector>
    #include <map>
    #include "Mesh.hpp"
    #include "StringManager.hpp"

namespace Parser {
    class Obj {
        public:
            static Engine::Mesh loadFile(const std::string &filename);

        protected:
        private:
    };
} // namespace Parser

#endif /* !OBJ_HPP_ */

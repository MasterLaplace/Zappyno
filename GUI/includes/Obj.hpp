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
    #include <memory>
    #include "Mesh.hpp"
    #include "StringManager.hpp"

namespace Parser {
    class Obj {
        public:
            static std::shared_ptr<Engine::Mesh> loadFile(const std::string &filename);

        protected:
        private:
    };
}

#endif /* !OBJ_HPP_ */

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Obj
*/

#include "Obj.hpp"
#include <algorithm>

namespace Parser {
    /**
     * @brief load an obj file and return a vector of unique_ptr<Engine::Mesh>
     *
     * @param filename the path to the obj file
     * @return a vector of unique_ptr<Engine::Mesh>
     */
    std::shared_ptr<Engine::Mesh> Obj::loadFile(const std::string &filename) {
        std::shared_ptr<Engine::Mesh> newshape = std::make_shared<Engine::Mesh>();
        std::ifstream file(filename);

        if (!file.is_open()) {
            throw std::runtime_error("Obj: Failed to open OBJ file " + filename + " (" + __FILE__ + ":" + std::to_string(__LINE__) + ")");
        }

        std::vector<std::string> buffer;
        std::string lines;
        while (std::getline(file, lines)) {
            buffer.push_back(lines);
        }
        std::vector<std::string> info;
        std::size_t nb_v = 0, nb_vt = 0;

        for (auto& line : buffer) {
            if (line[0] == 'v' && line[1] == ' ')
                nb_v++;
            else if (line[0] == 'v' && line[1] == 't')
                nb_vt++;
        }

        Math::Vector vertices[nb_v];
        Math::Vector tex_coords[nb_vt];
        std::size_t v = 0, t = 0;

        for (auto& line : buffer) {
            if ((info = String::stwa(line, " \t")).empty());
            else if (info[0][0] == 'v' && info[0][1] == '\0') {
                try {
                    vertices[v] = Math::Vector(stof(info[1]), stof(info[2]), stof(info[3]));
                    v++;
                } catch (std::exception& e) {
                    std::cout << "Missing vertex in OBJ file, skipping..." << std::endl;
                }
            } else if (info[0][0] == 'v' && info[0][1] == 't') {
                try {
                    tex_coords[t] = Math::Vector(stof(info[1]), stof(info[2]), (info.size() >= 4) ? stof(info[3]) : 0);
                    t++;
                } catch (std::exception& e) {
                    std::cout << "Missing texture coordinate in OBJ file, skipping..." << std::endl;
                }
            }
        }

        std::size_t nb_chr = 0;

        for (auto& line : buffer) {
            info = String::stwa(line, " \t/");
            if (info.empty());
            else if (info[0][0] == 'f' && (nb_chr = std::count(line.begin(), line.end(), '/')) != 0) {
                try {
                    newshape->add(std::make_shared<Engine::Triangle>(
                            vertices[std::stoi(info[1]) - 1],
                            vertices[std::stoi(info[(nb_chr % 3 == 0 && nb_chr != 3) ? 4 : 3]) - 1],
                            vertices[std::stoi(info[(nb_chr % 3 == 0 && nb_chr != 3) ? 7 : 5]) - 1],

                            tex_coords[std::stoi(info[2]) - 1],
                            tex_coords[std::stoi(info[(nb_chr % 3 == 0 && nb_chr != 3) ? 5 : 4]) - 1],
                            tex_coords[std::stoi(info[(nb_chr % 3 == 0 && nb_chr != 3) ? 8 : 6]) - 1]
                    ));
                } catch (std::exception& e) {
                    std::cout << "Failed to parse face 1 in OBJ file, skipping..." << std::endl;
                }
                if (((nb_chr % 3 == 0 && nb_chr != 3) ? 10 : 7) < info.size()) {
                    try {
                        newshape->add(std::make_shared<Engine::Triangle>(
                                vertices[std::stoi(info[1]) - 1],
                                vertices[std::stoi(info[(nb_chr % 3 == 0 && nb_chr != 3) ? 7 : 5]) - 1],
                                vertices[std::stoi(info[(nb_chr % 3 == 0 && nb_chr != 3) ? 10 : 6]) - 1],

                                tex_coords[std::stoi(info[2]) - 1],
                                tex_coords[std::stoi(info[(nb_chr % 3 == 0 && nb_chr != 3) ? 8 : 6]) - 1],
                                tex_coords[std::stoi(info[(nb_chr % 3 == 0 && nb_chr != 3) ? 11 : 7]) - 1]
                        ));
                    } catch (std::exception& e) {
                        std::cout << "Failed to parse face 2 in OBJ file, skipping..." << std::endl;
                    }
                }
            }
        }
        return newshape;
    }
}

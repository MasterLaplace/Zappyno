/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Obj
*/

#include "../../../includes/Obj.hpp"
#include <algorithm>
#include <chrono>

namespace Parser {
    /**
     * @brief load an obj file and return a vector of unique_ptr<Engine::Mesh>
     *
     * record the time it took to load the file:
     * - teapot.obj: 8ms / 6320 triangles (without texture)
     * - Artisans_Hub.obj: 15ms / 9737 triangles (without texture)
     *
     * @param filename the path to the obj file
     * @return a vector of unique_ptr<Engine::Mesh>
     */
    Engine::Mesh Obj::loadFile(const std::string &filename) {
        // start timer
        auto start = std::chrono::high_resolution_clock::now();
        Engine::Mesh newshape;
        std::ifstream file(filename);

        if (!file.is_open())
            throw std::runtime_error("Obj: Failed to open OBJ file " + filename + " (" + __FILE__ + ":" + std::to_string(__LINE__) + ")");

        std::vector<std::string> buffer;
        std::string lines;
        std::vector<std::string> info;

        std::vector<Math::Vector> vertices;
        std::vector<Math::Vector> tex_coords;

        while (std::getline(file, lines)) {
            if ((info = String::string_to_string_vector(lines, " \t")).empty());
            else if (info[0] == "v") {
                try {
                    vertices.push_back(Math::Vector(stof(info[1]), stof(info[2]), stof(info[3])));
                } catch (std::exception& e) {
                    std::cout << "Missing vertex in OBJ file, skipping..." << std::endl;
                }
            } else if (info[0][0] == 'v' && info[0][1] == 't') {
                try {
                    tex_coords.push_back(Math::Vector(stof(info[1]), stof(info[2]), (info.size() >= 4) ? stof(info[3]) : 0));
                } catch (std::exception& e) {
                    std::cout << "Missing texture coordinate in OBJ file, skipping..." << std::endl;
                }
            } else if (info[0][0] != 'v')
                buffer.push_back(lines);
        }

        unsigned nb_chr = 0;
        static const unsigned tab[2][7] = {
            {3, 5, 4, 6, 7, 6, 7},
            {4, 7, 5, 8, 10, 10, 11}
        };

        for (auto& line : buffer) {
            info = String::string_to_string_vector(line, " \t/");
            if (info.empty());
            else if (info[0][0] == 'f' && (nb_chr = count(line.begin(), line.end(), '/'))) {
                unsigned index(nb_chr % 3 == 0 && nb_chr != 3);
                try {
                    newshape.add(std::make_shared<Engine::Triangle>(
                            vertices[stoi(info[1]) - 1],
                            vertices[stoi(info[tab[index][0]]) - 1],
                            vertices[stoi(info[tab[index][1]]) - 1],

                            tex_coords[stoi(info[2]) - 1],
                            tex_coords[stoi(info[tab[index][2]]) - 1],
                            tex_coords[stoi(info[tab[index][3]]) - 1]
                    ));
                } catch (std::exception& e) {
                    std::cout << "Failed to parse face 1 in OBJ file, skipping..." << std::endl;
                }
                if (tab[index][4] < info.size()) {
                    try {
                        newshape.add(std::make_shared<Engine::Triangle>(
                                vertices[stoi(info[1]) - 1],
                                vertices[stoi(info[tab[index][1]]) - 1],
                                vertices[stoi(info[tab[index][5]]) - 1],

                                tex_coords[stoi(info[2]) - 1],
                                tex_coords[stoi(info[tab[index][3]]) - 1],
                                tex_coords[stoi(info[tab[index][6]]) - 1]
                        ));
                    } catch (std::exception& e) {
                        std::cout << "Failed to parse face 2 in OBJ file, skipping..." << std::endl;
                    }
                }
            } else if (info[0][0] == 'f') {
                try {
                    newshape.add(std::make_shared<Engine::Triangle>(
                            vertices[stoi(info[1]) - 1],
                            vertices[stoi(info[2]) - 1],
                            vertices[stoi(info[3]) - 1]
                    ));
                } catch (std::exception& e) {
                    std::cout << "Failed to parse face in OBJ file, skipping..." << std::endl;
                }
            }
        }
        // print elapsed time
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
        std::cout << "[Obj] OBJ file \"" << filename << "\" loaded in " << duration.count() << "ms" << std::endl;
        return newshape;
    }
} // namespace Parser

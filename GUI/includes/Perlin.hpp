/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Perlin
*/

#ifndef PERLIN_HPP_
    #define PERLIN_HPP_
    #include <vector>
    #include <iostream>  // Pour l'affichage (facultatif)
    #include <cmath>     // Pour la fonction de bruit Perlin (facultatif)

namespace Math {
    class Perlin {
        public:
            Perlin(std::vector<std::vector<int>> &map, int mapWidth, int mapHeight);
            ~Perlin() = default;

            void setPerlinImage(std::vector<std::vector<int>> &map, int mapWidth, int mapHeight);
            void PerlinNoise2D(int nWidth, int nHeight, float *fSeed, int nOctaves, float fBias, float *fOutput);
            void setGreyScale(std::vector<std::vector<int>> &map, int mapWidth, int mapHeight);

        protected:
        private:
    };
} // namespace Math

#endif /* !PERLIN_HPP_ */

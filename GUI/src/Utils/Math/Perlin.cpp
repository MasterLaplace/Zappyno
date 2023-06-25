/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Perlin
*/

#include "../../../includes/Perlin.hpp"
#include <climits>

namespace Math {
    Perlin::Perlin(std::vector<std::vector<int>> &map, int mapWidth, int mapHeight) {
        map.resize(mapHeight, std::vector<int>(mapWidth));
        int scl = 20;
        int cols = mapWidth / scl;
        int rows = mapHeight / scl;

        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                map[y * scl][x * scl] = 0;
            }
        }
    }

    void Perlin::setPerlinImage(std::vector<std::vector<int>> &map, int mapWidth, int mapHeight) {
        map.resize(mapHeight, std::vector<int>(mapWidth));
        float *fNoiseSeed2D;
        float *fPerlinNoise2D;
        fNoiseSeed2D = new float[mapWidth * mapHeight];
        fPerlinNoise2D = new float[mapWidth * mapHeight];

        for (int x = 0; x < mapWidth * mapHeight; x++) {
            fNoiseSeed2D[x] = (float)rand() / (float)RAND_MAX;
        }

        PerlinNoise2D(mapWidth, mapHeight, fNoiseSeed2D, 8, 3.0f, fPerlinNoise2D);
        for (int x = 0; x < mapWidth; x++) {
            for (int y = 0; y < mapHeight; y++) {
                map[x][y] = static_cast<int>(fPerlinNoise2D[y * mapWidth + x] * 255);
            }
        }

        setGreyScale(map, mapWidth, mapHeight);
    }

    void Perlin::PerlinNoise2D(int nWidth, int nHeight, float *fSeed, int nOctaves, float fBias, float *fOutput) {
        for (int x = 0; x < nWidth; x++) {
            for (int y = 0; y < nHeight; y++) {
                float fNoise = 0.0f;
                float fScaleAcc = 0.0f;
                float fScale = 1.0f;

                for (int o = 0; o < nOctaves; o++) {
                    int nPitch = nWidth / std::pow(2, o);
                    if (nPitch == 0) { nPitch = 1; }
                    int nSampleX1 = (x / nPitch) * nPitch;
                    int nSampleY1 = (y / nPitch) * nPitch;

                    int nSampleX2 = (nSampleX1 + nPitch) % nWidth;
                    int nSampleY2 = (nSampleY1 + nPitch) % nWidth;

                    float fBlendX = (float)(x - nSampleX1) / (float)nPitch;
                    float fBlendY = (float)(y - nSampleY1) / (float)nPitch;

                    float fSampleT = (1.0f - fBlendX) * fSeed[nSampleY1 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY1 * nWidth + nSampleX2];
                    float fSampleB = (1.0f - fBlendX) * fSeed[nSampleY2 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY2 * nWidth + nSampleX2];

                    fScaleAcc += fScale;
                    fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
                    fScale = fScale / fBias;
                }

                // Scale to seed range
                fOutput[y * nWidth + x] = fNoise / fScaleAcc;
            }
        }
    }

    void Perlin::setGreyScale(std::vector<std::vector<int>> &map, int mapWidth, int mapHeight) {
        int minValue = INT_MAX;
        int maxValue = INT_MIN;

        // Trouver la valeur minimale et maximale dans map
        for (int i = 0; i < mapHeight; i++) {
            for (int j = 0; j < mapWidth; j++) {
                int value = map[i][j];
                if (value < minValue) {
                    minValue = value;
                }
                if (value > maxValue) {
                    maxValue = value;
                }
            }
        }

        // Convertir les valeurs de map à l'échelle de 0 à 255
        for (int i = 0; i < mapHeight; i++) {
            for (int j = 0; j < mapWidth; j++) {
                double perlinValue = map[i][j];
                perlinValue = (perlinValue - minValue) / (maxValue - minValue);  // Réduire à une plage de 0 à 1
                perlinValue *= 255;  // Mettre à l'échelle de 0 à 255
                map[i][j] = static_cast<int>(perlinValue);
            }
        }
    }
}

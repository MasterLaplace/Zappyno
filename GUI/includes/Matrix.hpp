/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Math Library
*/

#ifndef MATRIX_HPP_
    #define MATRIX_HPP_
    #include "Vector.hpp"
    #include <vector>

namespace Math {
    class Matrix {
        public:
            Matrix() = default;
            Matrix(const std::vector<std::vector<double>> &mat)
            {
                for(unsigned i = 0; i < 4; i++) {
                    for(unsigned j = 0; j < 4; j++) {
                        m[i][j] = mat[i][j];
                    }
                }
            }
            ~Matrix() = default;

            Matrix &operator=(const Matrix &mat) = default;
            Matrix &operator=(const std::vector<std::vector<double>> &mat);
            std::vector<double> &operator[](unsigned i) { return m[i]; };
            const std::vector<double> &operator[](unsigned i) const { return m[i]; };

            void SetRotateXMatrix(double angle);

            void SetRotateYMatrix(double angle);

            void SetRotateZMatrix(double angle);

            void SetTranslateMatrix(double x, double y, double z);

            void SetScaleMatrix(double x, double y, double z);

            void MultiplyVector(Vector &v, Vector w) const;

            void Multiply(Matrix m1, Matrix m2);

            Matrix QuickInverse() const;

        public:
            std::vector<std::vector<double>> m{
                {1, 0, 0, 0},
                {0, 1, 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1}
            };
    };
    std::ostream &operator<<(std::ostream &os, const Matrix &matrix);
} // namespace Math

#endif /* !MATRIX_HPP_ */

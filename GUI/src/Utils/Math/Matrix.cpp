/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Math Library
*/

#include "Matrix.hpp"

namespace Math {
    Matrix &Matrix::operator=(const std::vector<std::vector<double>> &mat) {
        for(std::size_t i = 0; i < 4; i++) {
            for(std::size_t j = 0; j < 4; j++) {
                m[i][j] = mat[i][j];
            }
        }
        return *this;
    }

    void Matrix::SetRotateXMatrix(double angle)
    {
        std::vector<std::vector<double>> rot_matrix = {
            { 1, 0, 0, 0 },
            { 0, cos(angle), -sin(angle), 0 },
            { 0, sin(angle), cos(angle), 0 },
            { 0, 0, 0, 1 }
        };

        m = rot_matrix;
    }

    void Matrix::SetRotateYMatrix(double angle)
    {
        std::vector<std::vector<double>> rot_matrix = {
            { cos(angle), 0, sin(angle), 0 },
            { 0, 1, 0, 0 },
            { -sin(angle), 0, cos(angle), 0 },
            { 0, 0, 0, 1 }
        };

        m = rot_matrix;
    }

    void Matrix::SetRotateZMatrix(double angle)
    {
        std::vector<std::vector<double>> rot_matrix = {
            { cos(angle), -sin(angle), 0, 0 },
            { sin(angle), cos(angle), 0, 0 },
            { 0, 0, 1, 0 },
            { 0, 0, 0, 1 }
        };

        m = rot_matrix;
    }

    void Matrix::SetTranslateMatrix(double x, double y, double z)
    {
        std::vector<std::vector<double>>tran_matrix = {
            { 1, 0, 0, 0 },
            { 0, 1, 0, 0 },
            { 0, 0, 1, 0 },
            { x, y, z, 1 }
        };

        m = tran_matrix;
    }

    void Matrix::SetScaleMatrix(double x, double y, double z)
    {
        std::vector<std::vector<double>> sca_matrix = {
            { x, 0, 0, 0 },
            { 0, y, 0, 0 },
            { 0, 0, z, 0 },
            { 0, 0, 0, 1 }
        };

        m = sca_matrix;
    }

    Math::Vector Matrix::MultiplyVector(Math::Vector v, Math::Vector w) const {
        v.e[0] = w.x() * m[0][0] + w.y() * m[1][0] + w.z() * m[2][0];
        v.e[1] = w.x() * m[0][1] + w.y() * m[1][1] + w.z() * m[2][1];
        v.e[2] = w.x() * m[0][2] + w.y() * m[1][2] + w.z() * m[2][2];
        return v;
    }

    void Matrix::Multiply(Matrix m1, Matrix m2) {
        for(std::size_t i = 0; i < 4; i++) {
            for (std::size_t j = 0; j < 4; j++) {
                m[j][i] = m1[j][0] * m2[0][i]
                        + m1[j][1] * m2[1][i]
                        + m1[j][2] * m2[2][i]
                        + m1[j][3] * m2[3][i];
            }
        }
    }

    Matrix Matrix::QuickInverse() const {
        Matrix inv;

        for(std::size_t i = 0; i < 3; i++) {
            for(std::size_t j = 0; j < 3; j++) {
                inv.m[i][j] = m[j][i];
            }
        }

        inv.m[3][0] = -(m[3][0] * inv.m[0][0] + m[3][1] * inv.m[1][0] + m[3][2] * inv.m[2][0]);
        inv.m[3][1] = -(m[3][0] * inv.m[0][1] + m[3][1] * inv.m[1][1] + m[3][2] * inv.m[2][1]);
        inv.m[3][2] = -(m[3][0] * inv.m[0][2] + m[3][1] * inv.m[1][2] + m[3][2] * inv.m[2][2]);

        inv.m[0][3] = inv.m[1][3] = inv.m[2][3] = 0.0;
        inv.m[3][3] = 1.0;

        return inv;
    }

    std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
        os << "Matrix content:" << std::endl;
        try {
            for (std::size_t i = 0; i < 4; i++) {
                for (std::size_t j = 0; j < 4; j++) {
                    os << matrix[i][j] << " ";
                }
                os << std::endl;
            }
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
        return os;
    }
}

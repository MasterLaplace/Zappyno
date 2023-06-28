/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Triangle
*/

#include "../../includes/Triangle.hpp"

namespace Engine {
    Triangle::Triangle() {
        _vertex[0] = Math::Vector();
        _vertex[1] = Math::Vector();
        _vertex[2] = Math::Vector();
    }

    Triangle::Triangle(const Math::Vector &v0, const Math::Vector &v1, const Math::Vector &v2) {
        _vertex[0] = v0;
        _vertex[1] = v1;
        _vertex[2] = v2;
    }

    Triangle::Triangle(const Math::Vector &v0, const Math::Vector &v1, const Math::Vector &v2,
                    const Math::Vector &t0, const Math::Vector &t1, const Math::Vector &t2) {
        _vertex[0] = v0;
        _vertex[1] = v1;
        _vertex[2] = v2;
        _tex_coords[0] = t0;
        _tex_coords[1] = t1;
        _tex_coords[2] = t2;
    }

    Triangle::Triangle(const Triangle &triangle) {
        _vertex[0] = triangle[0];
        _vertex[1] = triangle[1];
        _vertex[2] = triangle[2];
        _tex_coords[0] = triangle._tex_coords[0];
        _tex_coords[1] = triangle._tex_coords[1];
        _tex_coords[2] = triangle._tex_coords[2];
        _dp = triangle._dp;
    }

    Triangle &Triangle::operator=(const Triangle &triangle) {
        _vertex[0] = triangle[0];
        _vertex[1] = triangle[1];
        _vertex[2] = triangle[2];
        _tex_coords[0] = triangle._tex_coords[0];
        _tex_coords[1] = triangle._tex_coords[1];
        _tex_coords[2] = triangle._tex_coords[2];
        _dp = triangle._dp;
        return *this;
    }

    bool Triangle::operator==(const Triangle &triangle) const {
        return _vertex[0] == triangle[0] && _vertex[1] == triangle[1] && _vertex[2] == triangle[2];
    }

    std::ostream &operator<<(std::ostream &os, const Triangle &triangle) {
        os << "Triangle content:" << std::endl;
        os << "\tVertex 0: " << triangle[0] << std::endl;
        os << "\tVertex 1: " << triangle[1] << std::endl;
        os << "\tVertex 2: " << triangle[2] << std::endl;
        return os;
    }


    int Triangle::ClipAgainstPlane(Math::Vector plane_p, Math::Vector plane_n, Triangle &out_tri1, Triangle &out_tri2)
    {
        plane_n.normalise();

        // Return signed shortest distance from point to plane, plane normal must be normalised
        auto dist = [&](Math::Vector &p) {
            return (plane_n.x() * p.x() + plane_n.y() * p.y() + plane_n.z() * p.z() - Math::dot(plane_n, plane_p));
        };

        Math::Vector* inside_points[3];  int nInsidePointCount = 0;
        Math::Vector* outside_points[3]; int nOutsidePointCount = 0;

        // Get signed distance of each point in triangle to plane
        float d0 = dist(_vertex[0]);
        float d1 = dist(_vertex[1]);
        float d2 = dist(_vertex[2]);

        if (d0 >= 0) { inside_points[nInsidePointCount++] = &_vertex[0]; }
        else { outside_points[nOutsidePointCount++] = &_vertex[0]; }
        if (d1 >= 0) { inside_points[nInsidePointCount++] = &_vertex[1]; }
        else { outside_points[nOutsidePointCount++] = &_vertex[1]; }
        if (d2 >= 0) { inside_points[nInsidePointCount++] = &_vertex[2]; }
        else { outside_points[nOutsidePointCount++] = &_vertex[2]; }

        if (nInsidePointCount == 0) {
            return 0; // No returned triangles are valid
        }

        if (nInsidePointCount == 3) {
            out_tri1 = *this;

            return 1; // Just the one returned original triangle is valid
        }

        if (nInsidePointCount == 1 && nOutsidePointCount == 2)
        {
            out_tri1.SetDp(_dp);
            out_tri1[0] = *inside_points[0];

            out_tri1[1].IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0]);
            out_tri1[2].IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[1]);

            return 1; // Return the newly formed single triangle
        }

        if (nInsidePointCount == 2 && nOutsidePointCount == 1)
        {
            out_tri1.SetDp(_dp);
            out_tri2.SetDp(_dp);

            out_tri1[0] = *inside_points[0];
            out_tri1[1] = *inside_points[1];
            out_tri1[2].IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0]);

            out_tri2[0] = *inside_points[1];
            out_tri2[1] = out_tri1[2];
            out_tri2[2].IntersectPlane(plane_p, plane_n, *inside_points[1], *outside_points[0]);

            return 2; // Return two newly formed triangles which form a quad
        }
        return 0; // No returned triangles are valid
    }
} // namespace Engine

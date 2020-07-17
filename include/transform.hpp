#pragma once

#include "matrix4x4.hpp"
#include "vec3.hpp"
#include "point3.hpp"
#include "normal3.hpp"

namespace gm {

    class Transform {
    public:
    constexpr Transform() : m_matrix(Matrix4x4f::identity()), m_inverse(Matrix4x4f::identity()) { }

    auto constexpr Transform::translate(Vec3f const& vec) -> Transform& {
        m_matrix *= {
            1, 0, 0, vec.x,
            0, 1, 0, vec.y,
            0, 0, 1, vec.z,
            0, 0, 0,     1
        };
        m_inverse *= {
            1, 0, 0, -vec.x,
            0, 1, 0, -vec.y,
            0, 0, 1, -vec.z,
            0, 0, 0,      1
        };

        return *this;
    }

    auto constexpr Transform::scale(Vec3f const& vec) -> Transform&
    {
        m_matrix *= {
            vec.x,     0,     0, 0,
                0, vec.y,     0, 0,
                0,     0, vec.z, 0,
                0,     0,     0,   1
        };

        m_inverse *= {
            1.0f/vec.x,          0,          0,  0,
            0,          1.0f/vec.y,          0,  0,
            0,                   0, 1.0f/vec.z,  0,
            0,                   0,          0,  1
        };

        return *this;
    }

    auto constexpr Transform::rotate(Vec3f const& axis, FLOAT angle) -> Transform& {

        auto const norm_axis = axis.normalise();
        auto const rad = degree_to_radian(angle);

        auto const cos_theta = gcem::cos(rad);
        auto const sin_theta = gcem::sin(rad);

        auto mat = Matrix4x4f::identity();

        mat(0, 0) = norm_axis.x() * norm_axis.x() + (1.0f - norm_axis.x() * norm_axis.x()) * cos_theta;
        mat(0, 1) = norm_axis.x() * norm_axis.y() * (1.0f - cos_theta) - norm_axis.z() * sin_theta;
        mat(0, 2) = norm_axis.x() * norm_axis.z() * (1.0f - cos_theta) + norm_axis.y() * sin_theta;
        mat(0, 3) = 0;

        mat(1, 0) = norm_axis.x() * norm_axis.y() * (1.0f - cos_theta) + norm_axis.z() * sin_theta;
        mat(1, 1) = norm_axis.y() * norm_axis.y() + (1.0f - norm_axis.y() * norm_axis.y()) * cos_theta;
        mat(1, 2) = norm_axis.y() * norm_axis.z() * (1.0f - cos_theta) - norm_axis.x() * sin_theta;
        mat(1, 3) = 0;

        mat(2, 0) = norm_axis.x() * norm_axis.z() * (1.0f - cos_theta) - norm_axis.y() * sin_theta;
        mat(2, 1) = norm_axis.y() * norm_axis.z() * (1.0f - cos_theta) + norm_axis.x() * sin_theta;
        mat(2, 2) = norm_axis.z() * norm_axis.z() + (1.0f - norm_axis.z() * norm_axis.z()) * cos_theta;
        mat(2, 3) = 0;

        mat(3, 0) = 0;
        mat(3, 1) = 0;
        mat(3, 2) = 0;
        mat(3, 3) = 1;

        m_matrix *= mat;
        m_inverse *= mat.transpose();

        return *this;
    }
    
    auto constexpr Transform::apply(Point3f const& point) const -> Point3f {

        const auto x = m_matrix(0,0) * point.x + m_matrix(0,1) * point.y + m_matrix(0,2) * point.z + m_matrix(0,3);
        const auto y = m_matrix(1,0) * point.x + m_matrix(1,1) * point.y + m_matrix(1,2) * point.z + m_matrix(1,3);
        const auto z = m_matrix(2,0) * point.x + m_matrix(2,1) * point.y + m_matrix(2,2) * point.z + m_matrix(2,3);
        const auto w = m_matrix(3,0) * point.x + m_matrix(3,1) * point.y + m_matrix(3,2) * point.z + m_matrix(3,3);

        return {x/w, y/w, z/w};
    }

    auto constexpr Transform::apply(Vec3f const& vec) const -> Vec3f {

        const auto x = m_matrix(0,0) * vec.x + m_matrix(0,1) * vec.y + m_matrix(0,2) * vec.z;
        const auto y = m_matrix(1,0) * vec.x + m_matrix(1,1) * vec.y + m_matrix(1,2) * vec.z;
        const auto z = m_matrix(2,0) * vec.x + m_matrix(2,1) * vec.y + m_matrix(2,2) * vec.z;
        return {x, y, z};
    }

    auto constexpr Transform::apply(Normal3f const& normal) const -> Normal3f {

        // Note: normals are transformed using the inverse transpose matrix
        const auto x = m_inverse(0,0) * normal.x() + m_inverse(1,0) * normal.y() + m_inverse(2,0) * normal.z();
        const auto y = m_inverse(0,1) * normal.x() + m_inverse(1,1) * normal.y() + m_inverse(2,1) * normal.z();
        const auto z = m_inverse(0,2) * normal.x() + m_inverse(1,2) * normal.y() + m_inverse(2,2) * normal.z();
        return Vec3f{ x, y, z }.normalise();
    }

    // TODO: undo functions

    private:
        Matrix4x4f m_matrix;
        Matrix4x4f m_inverse;
    };

}
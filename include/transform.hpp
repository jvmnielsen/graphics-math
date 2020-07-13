#pragma once

#include "matrix4x4.hpp"
#include "vec3.hpp"
#include "point3.hpp"
#include "normal3.hpp"

namespace gm {

    class Transform
    {
    public:
        constexpr Transform() : m_matrix(Matrix4x4f::identity()), m_inverse(Matrix4x4f::identity()) { }

        auto constexpr translate(Vec3f const& vec) -> Transform&;
        auto constexpr scale(Vec3f const& vec) -> Transform&;
        auto constexpr rotate(Vec3f const& axis, FLOAT angle) -> Transform&;

        auto constexpr apply(Point3f const& point) const -> Point3f;
        auto constexpr apply(Vec3f const& vec) const -> Vec3f;
        auto constexpr apply(Normal3f const& normal) const -> Normal3f;

    private:
        Matrix4x4f m_matrix;
        Matrix4x4f m_inverse;
    };

}
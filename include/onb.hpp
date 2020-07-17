#pragma once
#include "normal3.hpp"
#include "vec3.hpp"

#include <array>

namespace gm {
    // Orthonormal Basis
    class ONB {
    public:
        constexpr ONB::ONB(Normal3f const& normal) : m_basis(
            std::array<Normal3f, 3>{ 
                Vec3f{1, 0, 0}.normalise(),
                Vec3f{0, 1, 0}.normalise(),
                Vec3f{0, 0, 1}.normalise()
            }) {

            m_basis[2] = normal;

            Vec3f a;
            if (gcem::abs(normal.x() > 0.9)) { // is the normal the x-axis?
                a = Vec3f{0.0, 1.0, 0.0};
            } else {
                a = Vec3f{1.0, 0.0, 0.0};
            }

            m_basis[1] = cross(m_basis[2], a).normalise();
            m_basis[0] = cross(m_basis[1], m_basis[2]).normalise();
        }
        
        auto constexpr operator[](int i) const ->  Normal3f const& {
            return m_basis[i];
        }

        auto constexpr convert_to_local(const Vec3f& vec) const -> Vec3f {
            return vec.x * m_basis[0] + vec.y * m_basis[1] + vec.z * m_basis[2];
        }

        auto constexpr u() const -> Normal3f const& { return m_basis[0]; }
        auto constexpr v() const -> Normal3f const& { return m_basis[1]; }
        auto constexpr w() const -> Normal3f const& { return m_basis[2]; }
        
    private:
        std::array<Normal3f, 3> m_basis;
    };
}
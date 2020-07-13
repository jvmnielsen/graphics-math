#pragma once
#include "normal3.hpp"
#include "vec3.hpp"

#include <array>

namespace gm {
    // Orthonormal Basis
    class ONB {
    public:

        constexpr ONB(Normal3f const& normal);
        
        auto constexpr operator[](int i) const ->  Normal3f const&;
        auto constexpr convert_to_local(const Vec3f& vec) const -> Normal3f;

        auto constexpr u() const -> Normal3f const& { return m_basis[0]; }
        auto constexpr v() const -> Normal3f const& { return m_basis[1]; }
        auto constexpr w() const -> Normal3f const& { return m_basis[2]; }
        
    private:
        std::array<Normal3f, 3> m_basis;
    };
}
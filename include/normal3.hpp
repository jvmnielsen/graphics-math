#pragma once

#include "util.hpp"
#include "vec3.hpp"

namespace gm {

    template<typename Type> 
    class Normal3 {
    private:
        friend class Vec3<Type>;
        constexpr Normal3() : m_x(1), m_y(0), m_z(0) { }
        constexpr Normal3(Type x, Type y, Type z) : m_x(x), m_y(y), m_z(z) { }  
        Type m_x, m_y, m_z;   
    public:
        auto constexpr x() const -> Type { return m_x; }
        auto constexpr y() const -> Type { return m_y; }
        auto constexpr z() const -> Type { return m_z; }
    };

    template<typename Type>
    auto constexpr dot(Normal3<Type> const& v, Normal3<Type> const& u) -> Type {
        return v.x() * u.x() + v.y() * u.y() + v.z() * u.z();
    }

    template<typename Type>
    auto constexpr dot(Normal3<Type> const& v, Vec3<Type> const& u) -> Type {
        return v.x() * u.x + v.y() * u.y + v.z() * u.z;
    }

    typedef Normal3<FLOAT> Normal3f;
}
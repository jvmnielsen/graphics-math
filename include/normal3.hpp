#pragma once

#include "util.hpp"
// #include "vec3.hpp"

#include <ostream>

namespace gm { 

    template<typename Type>
    class Normal3 {
    private:
        template<typename>
        friend class Vec3;

        constexpr Normal3(Type x, Type y, Type z) : m_x(x), m_y(y), m_z(z) { }  
        Type m_x, m_y, m_z;   
    public:
        auto constexpr x() const -> Type { return m_x; }
        auto constexpr y() const -> Type { return m_y; }
        auto constexpr z() const -> Type { return m_z; }

        auto constexpr operator==(Normal3<Type> const& other) const -> bool {
            if constexpr (std::is_floating_point_v<Type>) {
                return gcem::abs(x() - other.x()) < constants::epsilon
                    && gcem::abs(y() - other.y()) < constants::epsilon
                    && gcem::abs(z() - other.z()) < constants::epsilon;
            } 
            return x() == other.x() && y() == other.y() && z() == other.z();
        }

        auto constexpr operator!=(Normal3<Type> const& other) const -> bool {
            if constexpr (std::is_floating_point_v<Type>) {
                return gcem::abs(x() - other.x()) > constants::epsilon
                    || gcem::abs(y() - other.y()) > constants::epsilon
                    || gcem::abs(z() - other.z()) > constants::epsilon;
            } else {
                return x() != other.x() || y() != other.y() || z() != other.z();
            }
        } 

        constexpr operator Vec3<Type>() const { return Vec3f{ x(), y(), z() }; }

        auto friend operator<<(std::ostream &os, Normal3<Type> const& n) -> std::ostream & {
            os << '[' << n.x() << ',' << n.y() << ',' << n.z() <<']' << '\n';
            return os;
        }

        // unary minus
        auto constexpr operator-() const -> Normal3<Type> { 
            return { -m_x, -m_y, -m_z };
        }

    };

    template<typename Type>
    auto constexpr operator*(Type const scalar, Normal3<Type> const& n) -> Vec3<Type> {
        return { scalar * n.x(), scalar * n.y(), scalar * n.z() };
    }

    template<typename Type>
    auto constexpr dot(Normal3<Type> const& v, Normal3<Type> const& u) -> Type {
        return v.x() * u.x() + v.y() * u.y() + v.z() * u.z();
    }

    template<typename Type>
    auto constexpr dot(Normal3<Type> const& v, Vec3<Type> const& u) -> Type {
        return v.x() * u.x + v.y() * u.y + v.z() * u.z;
    }

    template<typename Type> 
    auto constexpr cross(Normal3<Type> const& n, Vec3<Type> const& v) -> Vec3<Type> {
        return { n.y() * v.z - n.z() * v.y,
                 n.z() * v.x - n.x() * v.z,
                 n.x() * v.y - n.y() * v.x };
    }

    template<typename Type> 
    auto constexpr cross(Normal3<Type> const& n, Normal3<Type> const& m) -> Vec3<Type> {
        return { n.y() * m.z() - n.z() * m.y(),
                 n.z() * m.x() - n.x() * m.z(),
                 n.x() * m.y() - n.y() * m.x() };
    }

    typedef Normal3<FLOAT> Normal3f;
}
#pragma once


#include "vec3.hpp"

#include <ostream>
#include <algorithm>

namespace gm {

    template<typename Type>
    class Point3 {
    public:
        Type x, y, z;

        constexpr Point3() { x = y = z = 0; }
        constexpr Point3(Type x, Type y, Type z) : x(x), y(y), z(z) { }
        constexpr explicit Point3(Type val) : x(val), y(val), z(val) { }

        auto constexpr operator==(Point3<Type> const& other) const -> bool {
            if constexpr (std::is_floating_point_v<Type>) {
                return gcem::abs(x - other.x) < constants::epsilon
                    && gcem::abs(y - other.y) < constants::epsilon
                    && gcem::abs(z - other.z) < constants::epsilon;
            } 
            return x == other.x && y == other.y && z == other.z;
        }

        auto constexpr operator!=(Point3<Type> const& other) const -> bool {
            if constexpr (std::is_floating_point_v<Type>) {
                return gcem::abs(x - other.x) > constants::epsilon
                    || gcem::abs(y - other.y) > constants::epsilon
                    || gcem::abs(z - other.z) > constants::epsilon;
            } else {
                return x != other.x || y != other.y || z != other.z;
            }
        } 

        auto constexpr operator-(Point3<Type> const& other) const -> Vec3<Type> {
            return { x - other.x, y - other.y, z - other.z };
        }

        auto constexpr operator+(Vec3<Type> const& v) const -> Point3<Type> {
            return { x + v.x, y + v.y, z + v.z };
        }

        auto constexpr operator-(Vec3<Type> const& v) const -> Point3<Type> {
            return { x - v.x, y - v.y, z - v.z };
        }

        auto constexpr operator+(Point3<Type> const& p) const -> Point3<Type> {
            return { x + p.x, y + p.y, z + p.z };
        }

        auto constexpr operator/(Type div) const -> Point3<Type> {
            return { x / div, y / div, z / div }; 
        }

        auto constexpr operator[](std::size_t const index) const -> Type {
            assert(index >= 0 && index <= 2);
            if (index == 0) return x; 
            if (index == 1) return y; 
            return z;
        }

        auto friend operator<<(std::ostream &os, Point3<Type> const& p) -> std::ostream & {
            os << '(' << p.x << ',' << p.y << ',' << p.z <<')' << '\n';
            return os;
        }
    };

    
    template<typename Type>
    auto elementwise_min(const Point3<Type>& a, const Point3<Type>& b) -> Point3<Type> {
        return {std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z)};
    }

    template<typename Type>
    auto elementwise_max(const Point3<Type>& a, const Point3<Type>& b) -> Point3<Type> {
        return {std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z)};
    }

    template<typename Type>
    auto constexpr operator*(Type const scalar, Point3<Type> const& p) -> Point3<Type> {
        return { scalar * p.x, scalar * p.y, scalar * p.z };
    }

    template<typename Type>
    auto constexpr operator/(Type const scalar, Point3<Type> const& p) -> Point3<Type> {
        return { p.x / scalar, p.y / scalar, p.z / scalar };
    }

    typedef Point3<FLOAT> Point3f;
    typedef Point3<int> Point3i;

}
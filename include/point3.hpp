#pragma once


#include "vec3.hpp"


namespace gm {

    template<typename Type>
    class Point3 {
    public:
        Type x, y, z;

        constexpr Point3() { x = y = z = 0; }
        constexpr Point3(Type x, Type y, Type z) : x(x), y(y), z(z) { }

        auto constexpr operator==(Point3<Type> const& other) const -> bool {
            return x == other.x && y == other.y && z == other.z;
        }

        auto constexpr operator!=(Point3<Type> const& other) const -> bool {
            return x != other.x || y != other.y || z != other.z;
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
    };

    typedef Point3<FLOAT> Point3f;
    typedef Point3<int> Point3i;

}
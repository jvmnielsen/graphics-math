#pragma once


#include "vec3.hpp"


namespace gm {

template<typename Type>
class Point3 {
    Type x, y, z;

    constexpr Point3() { x = y = z = 0; }
    constexpr Point3(Type x, Type y, Type z) : x(x), y(y), z(z) { }

    auto constexpr operator-(Point3 const& other) const -> Vec3 {
        return { x - other.x, y - other.y, z - other.z };
    }

    auto constexpr operator+(Vec3 const& v) const -> Point3 {
        return { x + v.x, y + v.y, z + v.z };
    }

    auto constexpr operator-(Vec3 const& v) const -> Point3 {
        return { x - v.x, y - v.y, z - v.z };
    }

};

}
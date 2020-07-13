#pragma once


#include "vec2.hpp"


namespace gm {

template<typename Type, REQUIRES(std::is_arithmetic<Type>())>
class Point2 {
    Type x, y, z;

    constexpr Point3() { x = y = z = 0; }
    constexpr Point3(Type x, Type y, Type z) : x(x), y(y), z(z) { }

    auto constexpr operator-(Point2<Type> const& other) const -> Vec2<Type> {
        return { x - other.x, y - other.y, z - other.z };
    }

    auto constexpr operator+(Vec2<Type> const& v) const -> Point2<Type> {
        return { x + v.x, y + v.y, z + v.z };
    }

    auto constexpr operator-(Vec2<Type> const& v) const -> Point2<Type> {
        return { x - v.x, y - v.y, z - v.z };
    }

};

}
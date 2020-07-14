#pragma once


#include "vec2.hpp"
#include "util.hpp"

#include <ostream>

namespace gm {

template<typename Type>
class Point2 {
    Type x, y, z;

    constexpr Point2() { x = y = z = 0; }
    constexpr Point2(Type x, Type y, Type z) : x(x), y(y), z(z) { }

    auto constexpr operator==(Point2<Type> const& other) const -> bool {
        if constexpr (std::is_floating_point_v<Type>) {
            return gcem::abs(x - other.x) < constants::epsilon
                && gcem::abs(y - other.y) < constants::epsilon;
        } 
        return x == other.x && y == other.y;
    }

    auto constexpr operator!=(Point2<Type> const& other) const -> bool {
        if constexpr (std::is_floating_point_v<Type>) {
            return gcem::abs(x - other.x) > constants::epsilon
                || gcem::abs(y - other.y) > constants::epsilon;
        } else {
            return x != other.x || y != other.y;
        }
    }

    auto constexpr operator-(Point2<Type> const& other) const -> Vec2<Type> {
        return { x - other.x, y - other.y, z - other.z };
    }

    auto constexpr operator+(Vec2<Type> const& v) const -> Point2<Type> {
        return { x + v.x, y + v.y, z + v.z };
    }

    auto constexpr operator-(Vec2<Type> const& v) const -> Point2<Type> {
        return { x - v.x, y - v.y, z - v.z };
    }

    auto friend operator<<(std::ostream &os, Point2<Type> const& p) -> std::ostream & {
        os << '(' << p.x << ',' << p.y <<')' << '\n';
        return os;
    }

};

typedef Point2<FLOAT> Point2f;
typedef Point2<int> Point2i;

}
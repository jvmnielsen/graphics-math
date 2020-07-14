#pragma once


#include "vec2.hpp"
#include "util.hpp"
#include "point3.hpp"

#include <ostream>

namespace gm {

template<typename Type>
class Point2 {
    Type x, y, z;

    constexpr Point2() : x(0), y(0), z(0) { }
    constexpr Point2(Type x, Type y) : x(x), y(y){ }
    constexpr explicit Point2(Point3<Type> const& p) : x(p.x), y(p.y) { }

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

    auto constexpr operator[](std::size_t const index) const -> Type {
        assert(index >= 0 && index <= 2);
        if (index == 0) return x; 
        if (index == 1) return y; 
        return z;
    }

    auto friend operator<<(std::ostream &os, Point2<Type> const& p) -> std::ostream & {
        os << '(' << p.x << ',' << p.y <<')' << '\n';
        return os;
    }

};

template<typename Type>
auto elementwise_min(const Point2<Type>& a, const Point2<Type>& b) -> Point2<Type> {
    return {std::min(a.x, b.x), std::min(a.y, b.y)};
}

template<typename Type>
auto elementwise_max(const Point2<Type>& a, const Point2<Type>& b) -> Point2<Type> {
    return {std::max(a.x, b.x), std::max(a.y, b.y)};
}

typedef Point2<FLOAT> Point2f;
typedef Point2<int> Point2i;

}
#pragma once
#include <gcem.hpp>
#include "util.hpp"
#include "vec3.hpp"

#include <ostream>


namespace gm {

    template<typename Type>
    class Vec2 {
    public:
        Type x, y;

        constexpr Vec2() : x(0), y(0) { }
        constexpr Vec2(Type x, Type y) : x(x), y(y) { }
        auto constexpr static fill(Type val) -> Vec2<Type> {
            return { val, val }; 
        } 
        constexpr explicit Vec2(Vec3<Type> const& v) : x(v.x), y(v.y) { }

        auto constexpr length_squared() const -> Type {
            return x * x + y * y;
        }

        auto constexpr length() const -> Type {
            return static_cast<Type>(gcem::sqrt(length_squared()));
        }

        auto constexpr operator+(Vec2<Type> const& other) const -> Vec2<Type> {
            return { x + other.x, y + other.y };
        }

        auto constexpr operator-(Vec2<Type> const& other) const -> Vec2<Type> {
            return { x - other.x, y - other.y };
        }

        // unary minus
        auto constexpr operator-() const -> Vec2<Type> { 
            return { -x, -y };
        }

        auto constexpr operator[](std::size_t const index) const -> Type {
            assert(index >= 0 && index <= 2);
            if (index == 0) return x; 
            return y; 
        }

        auto constexpr operator==(Vec2<Type> const& other) const -> bool {
            if constexpr (std::is_floating_point_v<Type>) {
                return gcem::abs(x - other.x) < constants::epsilon
                    && gcem::abs(y - other.y) < constants::epsilon;
            } else {
                return x == other.x && y == other.y;
            }
        }

        auto constexpr operator!=(Vec2<Type> const& other) const -> bool {
            if constexpr (std::is_floating_point_v<Type>) {
                return gcem::abs(x - other.x) > constants::epsilon
                    || gcem::abs(y - other.y) > constants::epsilon;
            } else {
                return x != other.x || y != other.y;
            }
        } 

        auto constexpr dot(Vec2 const& other) const -> Type {
            return dot(*this, other); 
        }

        auto constexpr cross(Vec2<Type> const& other) const -> Vec2<Type> {
            return cross(*this, other); 
        }

        auto constexpr operator/(Type const scalar) const -> Vec2<Type> {
            return { x / scalar, y / scalar };
        }

        auto friend operator<<(std::ostream &os, Vec2<Type> const& v) -> std::ostream & {
            os << '[' << v.x << ',' << v.y << ']' << '\n';
            return os;
        }

    };

    template<typename Type>
    auto constexpr dot(Vec2<Type> const& v, Vec2<Type> const& u) -> Type {
        return v.x * u.x + v.y * u.y;
    }

    template< typename T > 
    auto cross(Vec2<T> const& u, Vec2<T> const& v) -> Vec2<T> {
        return { u.y * v.z - u.z * v.y,
                 u.z * v.x - u.x * v.z };
    }

    template<typename Type>
    auto constexpr operator*(Type const scalar, Vec2<Type> const& v) -> Vec2<Type> {
        return { scalar * v.x, scalar * v.y };
    }

    typedef Vec2<FLOAT> Vec2f;
    typedef Vec2<int> Vec2i;
}
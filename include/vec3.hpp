#pragma once
#include <gcem.hpp>

#include <type_traits>
#include <cassert>

#define REQUIRES(...) typename std::enable_if<(__VA_ARGS__), int>::type = 0

namespace gm {

    template<typename Type>
    class Normal3<Type>;

    template<typename Type, REQUIRES(std::is_arithmetic<Type>())>
    class Vec3 {
    public:
        Type x, y, z;

        constexpr Vec3() { x = y = z = 0; }
        constexpr Vec3(Type x, Type y, Type z) : x(x), y(y), z(z) { }

        auto constexpr length_squared() const -> Type {
            return x * x + y * y + z * z;
        }

        auto constexpr length() const -> Type {
            return static_cast<Type>(gcem::sqrt(length_squared()));
        }

        auto constexpr operator+(Vec3 const& other) const -> Vec3 {
            return { x + other.x, y + other.y, z + other.z };
        }

        auto constexpr operator-(Vec3 const& other) const -> Vec3 {
            return { x - other.x, y - other.y, z - other.z };
        }

        // unary minus
        auto constexpr operator-() const -> Vec3 { 
            return { -x, -y, -z };
        }

        auto constexpr operator[](std::size_t const index) const -> Type {
            assert(index >= 0 && index <= 2);
            if (index == 0) return x; 
            if (index == 1) return y; 
            return z;
        }

        auto constexpr operator==(Vec3 const& other) const -> bool {
            return x == other.x && y == other.y && z == other.z;
        }

        auto constexpr operator!=(Vec3 const& other) const -> bool {
            return x != other.x || y != other.y || z != other.z;
        } 

        auto constexpr dot(Vec3 const& other) const -> Type {
            return gm::dot(*this, other); 
        }

        auto constexpr cross(Vec3 const& other) const -> Vec3 {
            return gm::cross(*this, other); 
        }

        auto constexpr operator/(Type const scalar) const -> Vec3 {
            return { x / scalar, y / scalar, z / scalar };
        }

        auto constexpr to_normal() const -> Normal3 {
            auto const len = length();
            assert(len > 0);
            return { x / len, y / len, z / len };
        }

    };

    template<typename Type>
    auto constexpr dot(Vec3<Type> const& v, Vec3<Type> const& u) -> Type {
        return v.x * u.x + v.y * u.y + v.z * u.z;
    }

    template< typename T > 
    auto cross(Vec3<T> const& u, Vec3<T> const& v) -> Vec3<T> {
        return { u.y * v.z - u.z * v.y,
                 u.z * v.x - u.x * v.z,
                 u.x * v.y - u.y * v.x };
    }

    template<typename Type>
    auto constexpr operator*(Type const scalar, Vec3<Type> const& v) -> Vec3<Type> {
        return { scalar * v.x, scalar * v.y, scalar * v.z };
    }

}
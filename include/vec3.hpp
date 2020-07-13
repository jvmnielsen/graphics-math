#pragma once
#include "util.hpp"
#include "normal3.hpp"

#include <gcem.hpp>

#include <type_traits>
#include <cassert>


namespace gm {

    template<typename Type, std::enable_if_t<std::is_arithmetic<Type>::value, int> = 0>
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

        auto constexpr operator+(Vec3<Type> const& other) const -> Vec3<Type> {
            return { x + other.x, y + other.y, z + other.z };
        }

        auto constexpr operator-(Vec3<Type> const& other) const -> Vec3<Type> {
            return { x - other.x, y - other.y, z - other.z };
        }

        // unary minus
        auto constexpr operator-() const -> Vec3<Type> { 
            return { -x, -y, -z };
        }

        auto constexpr operator[](std::size_t const index) const -> Type {
            assert(index >= 0 && index <= 2);
            if (index == 0) return x; 
            if (index == 1) return y; 
            return z;
        }

        auto constexpr operator==(Vec3<Type> const& other) const -> bool {
            return x == other.x && y == other.y && z == other.z;
        }

        auto constexpr operator!=(Vec3<Type> const& other) const -> bool {
            return x != other.x || y != other.y || z != other.z;
        } 

        auto constexpr dot(Vec3 const& other) const -> Type {
            return gm::dot(*this, other); 
        }

        auto constexpr cross(Vec3<Type> const& other) const -> Vec3<Type> {
            return gm::cross(*this, other); 
        }

        auto constexpr operator/(Type const scalar) const -> Vec3<Type> {
            return { x / scalar, y / scalar, z / scalar };
        }

        auto constexpr to_normal() const -> Normal3<Type> {
            static_assert(std::is_floating_point_v<Type>);
            auto const len = length();
            assert(len > 0);
            return { 
                x / len, 
                y / len, 
                z / len 
            }; // TODO: consider pre-calculating inverse and multiplying
        }

    };

    template<typename Type>
    auto constexpr dot(Vec3<Type> const& v, Vec3<Type> const& u) -> Type {
        return v.x * u.x + v.y * u.y + v.z * u.z;
    }

    template<typename Type> 
    auto cross(Vec3<Type> const& u, Vec3<Type> const& v) -> Vec3<Type> {
        return { u.y * v.z - u.z * v.y,
                 u.z * v.x - u.x * v.z,
                 u.x * v.y - u.y * v.x };
    }

    template<typename Type>
    auto constexpr operator*(Type const scalar, Vec3<Type> const& v) -> Vec3<Type> {
        return { scalar * v.x, scalar * v.y, scalar * v.z };
    }

    typedef Vec3<FLOAT> Vec3f;
    typedef Vec3<int> Vec3i;

}
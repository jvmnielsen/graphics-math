#pragma once
#include "util.hpp"
//#include "normal3.hpp"

#include <gcem.hpp>

#include <type_traits>
#include <cassert>
#include <ostream>


namespace gm {

    template<typename>
    class Normal3;

    template<typename Type>
    class Vec3 {
    public:
        Type x, y, z;

        constexpr Vec3() : x(0), y(0), z(0) { }
        constexpr explicit Vec3(Type val) : x(val), y(val), z(val) { }
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

        auto constexpr operator*(Type scalar) const -> Vec3<Type> {
            return { x * scalar, y * scalar, z * scalar };
        }

        auto constexpr operator/(Type scalar) const -> Vec3<Type> {
            return { x / scalar, y / scalar, z / scalar };
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
            if constexpr (std::is_floating_point_v<Type>) {
                return gcem::abs(x - other.x) < constants::epsilon
                    && gcem::abs(y - other.y) < constants::epsilon
                    && gcem::abs(z - other.z) < constants::epsilon;
            } else {
                return x == other.x && y == other.y && z == other.z;
            }
        }

        auto constexpr operator!=(Vec3<Type> const& other) const -> bool {
            if constexpr (std::is_floating_point_v<Type>) {
                return gcem::abs(x - other.x) > constants::epsilon
                    || gcem::abs(y - other.y) > constants::epsilon
                    || gcem::abs(z - other.z) > constants::epsilon;
            } else {
                return x != other.x || y != other.y || z != other.z;
            }
        } 

        auto constexpr dot(Vec3 const& other) const -> Type {
            return x * other.x + y * other.y + z * other.z;
        }

        auto constexpr cross(Vec3<Type> const& v) const -> Vec3<Type> {
            return { y * v.z - z * v.y,
                     z * v.x - x * v.z,
                     x * v.y - y * v.x };
        }



        auto constexpr normalise() const -> Normal3<Type> {
            static_assert(std::is_floating_point_v<Type>);
            auto const len = length();
            assert(len > 0);
            return { 
                x / len, 
                y / len, 
                z / len 
            }; // TODO: consider pre-calculating inverse and multiplying
        }

        auto friend operator<<(std::ostream &os, Vec3<Type> const& v) -> std::ostream & {
            os << '[' << v.x << ',' << v.y << ',' << v.z <<']' << '\n';
            return os;
        }

    };

    template<typename Type>
    auto constexpr dot(Vec3<Type> const& v, Vec3<Type> const& u) -> Type {
        return v.dot(u);
    }

    template<typename Type>
    auto cross(Vec3<Type> const& u, Vec3<Type> const& v) -> Vec3<Type> {
        return u.cross(v);
    }

    template<typename Type>
    auto constexpr operator*(Type const scalar, Vec3<Type> const& v) -> Vec3<Type> {
        return { scalar * v.x, scalar * v.y, scalar * v.z };
    }

    template<typename Type>
    auto constexpr operator/(Type const scalar, Vec3<Type> const& v) -> Vec3<Type> {
        return { v.x / scalar, v.y / scalar, v.z / scalar };
    }

    typedef Vec3<FLOAT> Vec3f;
    typedef Vec3<int> Vec3i;

}
#pragma once

#include "util.hpp"

#include <cstdint>
#include <ostream>

namespace gm { 

    template<typename Type>
    class Color3
    {
    public:
        Type r, g, b;

        constexpr Color3() : r(0), g(0), b(0) { }
        constexpr explicit Color3(Type val) : r(val), g(val), b(val) { }
        constexpr Color3(Type r_, Type g_, Type b_) : r(r_), g(g_), b(b_) { }

        auto static constexpr black() -> Color3 { return Color3{0}; }

        auto constexpr operator==(Color3<Type> const& other) const -> bool {
            if constexpr (std::is_floating_point_v<Type>) {
                return gcem::abs(r - other.r) < constants::epsilon
                    && gcem::abs(g - other.g) < constants::epsilon
                    && gcem::abs(b - other.b) < constants::epsilon;
            } else {
                return r == other.x && g == other.y && b == other.z;
            }
        }

        auto constexpr operator!=(Color3<Type> const& other) const -> bool {
            if constexpr (std::is_floating_point_v<Type>) {
                return gcem::abs(r - other.r) > constants::epsilon
                    || gcem::abs(g - other.g) > constants::epsilon
                    || gcem::abs(b - other.b) > constants::epsilon;
            } else {
                return r != other.x || g != other.y || b != other.z;
            }
        } 

        auto constexpr operator*(Type factor) const -> Color3<Type>         {
            return Color3{r * factor, g * factor, b * factor};
        }

        auto constexpr operator*=(Type factor) ->  Color3<Type>& {
            r *= factor;
            g *= factor;
            b *= factor;
            return *this;
        }

        auto constexpr operator/(Type factor) const -> Color3<Type> {
            return Color3{r / factor, g / factor, b / factor};
        }

        auto constexpr operator/=(Type factor) -> Color3<Type>& {
            r /= factor;
            g /= factor;
            b /= factor;
            return *this;
        }

        auto constexpr operator+(Color3<Type> const& other) const -> Color3<Type> {
            return Color3{r + other.r, g + other.g, b + other.b};
        }

        auto constexpr operator+=(Color3<Type> const& other) -> Color3<Type>& {
            r += other.r;
            g += other.g;
            b += other.b;
            return *this;
        }

        auto constexpr operator-(Color3<Type> const& other) const -> Color3<Type> {
            return Color3<Type>{r - other.r, g - other.g, b - other.b};
        }

        auto constexpr operator-=(Color3<Type> const& other) -> Color3<Type>& {
            r -= other.r;
            g -= other.g;
            b -= other.b;
            return *this;
        }

        auto constexpr operator*(Color3<Type> const& other) const -> Color3<Type> {
            return {r * other.r, g * other.g, b * other.b};
        }

        auto constexpr is_black() const -> bool {
            return *this == black();
        }

        auto constexpr clamp() -> void {
            r = std::clamp(r, 0, 1);
            g = std::clamp(g, 0, 1);
            b = std::clamp(b, 0, 1);
        }

        auto friend operator<<(std::ostream &os, Color3<Type> const& c) -> std::ostream & {
            os << '(' << c.r << ',' << c.g << ',' << c.b <<')' << '\n';
            return os;
        }
    };

    template<typename Type>
    auto constexpr operator*(Type factor, Color3<Type> const& color) -> Color3<Type> {
        return Color3<Type>{ color.r * factor, color.g * factor, color.b * factor };
    }

    template<typename Type>
    auto constexpr operator/(Type factor, Color3<Type> const& color) -> Color3<Type>{
        return Color3<Type>{ color.r / factor, color.g / factor, color.b / factor };
    }

    template<typename Type>
    auto constexpr lerp(Type t, Color3<Type> const& s1, Color3<Type> const& s2) -> Color3<Type> {
        return (1 - t) * s1 + t * s2;
    }

    typedef Color3<FLOAT> Color3f;
    typedef Color3<std::uint8_t> Color3ui8;
    typedef Color3<unsigned short> Color3ui16;

}
#pragma once
#include <gcem.hpp>

namespace gm {

    template<typename Type>
    class Vec3 {
    public:
        Type x, y, z;

        constexpr Vec3() { x = y = z = 0; }
        constexpr Vec3(Type x, Type y, Type z) : x(x), y(y), z(z) { }

        auto constexpr lengthSquared() const -> Type {
            return x * x + y * y + z * z;
        }

        auto constexpr length() const -> Type {
            return static_cast<Type>(gcem::sqrt(lengthSquared()));
        }

    };

}
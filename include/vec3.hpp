#pragma once
#include <gcem.hpp>

namespace gm {

    template<typename Type>
    class Vec3 {
    public:
        Type x, y, z;

        auto constexpr lengthSquared() const -> Type {
            return x * x + y * y + z * z;
        }

        auto constexpr length() const -> Type {
            return gcem::sqrt(lengthSquared());
        }

    };

}
#pragma once
#include <gcem.hpp>

namespace gm {

    template<typename Type>
    class Vec2 {
    public:
        Type x, y;

        auto constexpr lengthSquared() const -> Type {
            return x * x + y * y;
        }

        auto constexpr length() const -> Type {
            return gcem::sqrt(lengthSquared());
        }

    };

}
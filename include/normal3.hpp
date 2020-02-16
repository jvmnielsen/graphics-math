#pragma once

#include "vec3.hpp"

namespace gm {

template<typename Type> 
class Normal3 {
    Type x, y, z;

    constexpr Normal3() { x = y = z = 0; }
    constexpr Normal3(Type x, Type y, Type z) : x(x), y(y), z(z) { }  
};

template<typename Type>
auto constexpr dot(Normal3<Type> const& v, Normal3<Type> const& u) -> Type {
    return v.x * u.x + v.y * u.y + v.z * u.z;
}

template<typename Type>
auto constexpr dot(Normal3<Type> const& v, Vec3<Type> const& u) -> Type {
    return v.x * u.x + v.y * u.y + v.z * u.z;
}


}
#pragma once

namespace gm {

    // adapted from https://baptiste-wicht.com/posts/2014/07/compile-integer-square-roots-at-compile-time-in-cpp.html
    template<typename Type> 
    auto constexpr sqrt(Type res, Type l, Type r) -> Type {
        if(l == r){
            return r;
        } else {
            const auto mid = (r + l) / 2;

            if(mid * mid >= res){
                return sqrt(res, l, mid);
            } else {
                return sqrt(res, mid + 1, r);
            }
        }
    }

    template<typename Type> 
    auto constexpr sqrt(Type res) -> Type {
        return sqrt(res, static_cast<Type>(1), res);
    }
}
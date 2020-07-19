#pragma once

#include <gcem.hpp>

#include <optional>
#include <tuple>

#define REQUIRES(...) typename std::enable_if<(__VA_ARGS__), int>::type = 0
#ifndef FLOAT
    #define FLOAT float
#endif 

namespace gm {

    namespace constants {
        inline constexpr FLOAT max_float = std::numeric_limits<FLOAT>::max();
        inline constexpr FLOAT min_float = std::numeric_limits<FLOAT>::lowest();
        inline constexpr FLOAT pi = static_cast<FLOAT>(3.14159265358979323846);
        inline constexpr FLOAT inv_pi = static_cast<FLOAT>(0.31830988618379067154);
        inline constexpr FLOAT epsilon = static_cast<FLOAT>(1e-5);
    };

    inline auto power_heuristic(int nf, FLOAT fPdf, int ng, FLOAT gPdf) -> float {
        const auto f = nf * fPdf, g = ng * gPdf;
        return (f * f) / (f * f + g * g);
    }

    template<typename T>
    auto constexpr degree_to_radian(T degree) -> FLOAT {
        return static_cast<FLOAT>(degree * constants::pi / 180.0);
    }

    // Returns in order smallest to largest solution
    template<typename T, REQUIRES(std::is_arithmetic<T>())>
    auto constexpr solve_quadratic(T a, T b, T c) -> std::optional<std::tuple<FLOAT, FLOAT>> {
       
        auto const discr = b * b - 4 * a * c;

        if (discr < 0) return std::nullopt;

        if (discr == 0) {
            auto const simple_solu = -0.5 * b / a;
            return std::make_tuple(simple_solu, simple_solu);
        }
          
        auto const q = (b > 0) ? -0.5 * (b + gcem::sqrt(discr)) : -0.5 * (b - gcem::sqrt(discr));

        auto solution_one = q / a;
        auto solution_two = c / q;

        if (solution_one > solution_two)
            std::swap(solution_one, solution_two);

        return std::make_tuple(solution_one, solution_two);
    }

    template<typename T>
    auto constexpr lerp(T t, T v1, T v2) -> T {
        return (1 - t) * v1 + t * v2;
    }
}
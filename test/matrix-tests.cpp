#include <graphics-math.hpp>

#include <catch2/catch.hpp>

#include <type_traits>

TEMPLATE_TEST_CASE(
    "Identity matrix", "[Matrix4x4]",
    std::int32_t, std::int64_t,
    float, double) {

    auto constexpr const matrix = gm::Matrix4x4<TestType>::identity();
    auto constexpr const identity = gm::Matrix4x4<TestType>{
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    REQUIRE(matrix == identity);

}
   

TEMPLATE_TEST_CASE(
    "Transpose", "[Matrix4x4]",
    std::int32_t, std::int64_t,
    float, double) {


    auto constexpr const base = gm::Matrix4x4<TestType>{
         1,  2,  3,  4,
         5,  6,  7,  8,
         9, 10, 11, 12,
        13, 14, 15, 16
    };
    auto constexpr const transposed = gm::Matrix4x4<TestType>{
        1, 5, 9, 13,
        2, 6, 10, 14,
        3, 7, 11, 15,
        4, 8, 12, 16
    };

    REQUIRE(base.transpose() == transposed);

}
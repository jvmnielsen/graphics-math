#include <graphics-math.hpp>

#include <catch2/catch.hpp>

#include <type_traits>

TEMPLATE_TEST_CASE(
    "Identity matrix", "[Matrix4x4]",
    std::int32_t, std::int64_t,
    float, double) {

    auto constexpr matrix = gm::Matrix4x4<TestType>::identity();
    auto constexpr identity = gm::Matrix4x4<TestType>{
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    REQUIRE(matrix == identity);

}
   

TEMPLATE_TEST_CASE(
    "Matrix transpose", "[Matrix4x4]",
    std::int32_t, std::int64_t,
    float, double) {


    auto constexpr base = gm::Matrix4x4<TestType>{
         1,  2,  3,  4,
         5,  6,  7,  8,
         9, 10, 11, 12,
        13, 14, 15, 16
    };
    auto constexpr transposed = gm::Matrix4x4<TestType>{
        1, 5, 9, 13,
        2, 6, 10, 14,
        3, 7, 11, 15,
        4, 8, 12, 16
    };

    REQUIRE(base.transpose() == transposed);

}

TEMPLATE_TEST_CASE(
    "Matrix-matrix multiplication", "[Matrix4x4]",
    std::int32_t, std::int64_t,
    float, double) {

    auto constexpr m1 = gm::Matrix4x4<TestType>{
         1,  2,  3,  4,
         5,  6,  7,  8,
         9, 10, 11, 12,
        13, 14, 15, 16
    };

    auto constexpr m2 = gm::Matrix4x4<TestType>{ 
        2, 4, 6, 8,
        10, 12, 14, 16,
        -2, -4, -6, -8,
        1, 3, 5, 9
    };
   
    auto constexpr result = gm::Matrix4x4<TestType>{ 
        20, 28, 36, 52,
        64, 88, 112, 152,
        108, 148, 188, 252,
        152, 208, 264, 352 
    }; 

    REQUIRE(m1 * m2 == result);

}
#include <graphics-math.hpp>

#include <catch2/catch.hpp>

using namespace gm; 

TEMPLATE_TEST_CASE(
    "Degree to radian", "[degree_to_radian]",
    std::int32_t, std::int64_t,
    float, double) {

    auto constexpr deg1 = 0;
    auto constexpr deg2 = 90;
    auto constexpr deg3 = 720;
    auto constexpr deg4 = 999999;
    auto constexpr deg5 = -20;

    REQUIRE(gm::degree_to_radian(deg1) == Approx(0));
    REQUIRE(gm::degree_to_radian(deg2) == Approx(1.5708));
    REQUIRE(gm::degree_to_radian(deg3) == Approx(12.5664));
    REQUIRE(gm::degree_to_radian(deg4) == Approx(17453.2751));
    REQUIRE(gm::degree_to_radian(deg5) == Approx(-0.349066));
}
   
TEMPLATE_TEST_CASE(
    "Solve quadratic", "[solve_quadratic]",
    std::int32_t, std::int64_t,
    float, double) {

    auto constexpr sol1 = gm::solve_quadratic(2, 5, -3);
    REQUIRE(sol1.has_value());
    auto const [val1, val2] = sol1.value(); 
    REQUIRE(val1 == Approx(-3.0f));
    REQUIRE(val2 == Approx(0.5f));
}


TEMPLATE_TEST_CASE("Color tests", "[Color3]", float, double) {

    auto constexpr black = Color3f::black(); 
    REQUIRE(black.is_black());
    auto constexpr green = Color3f{ 0.1, 0.8, 0.1 };
    auto constexpr red = Color3f{ 0.8, 0.1, 0.1 };
    auto constexpr blue = Color3f{ 0.1, 0.1, 0.8 };
    REQUIRE(green + red == Color3f{ 0.9, 0.9, 0.2 }); 
    REQUIRE(2.0f * blue == Color3f{ 0.2, 0.2, 1.6 }); 
    REQUIRE(blue - red == Color3f{ -0.7, 0, 0.7}); 
}
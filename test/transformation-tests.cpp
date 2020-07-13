#include <graphics-math.hpp>

#include <catch2/catch.hpp>

#include <type_traits>

using namespace gm;

TEST_CASE(
    "Transformations", "[Transform]") {

    auto transform = gm::Transform();
    auto const scale = Vec3f{ 1, 4, 1 };
    auto const translate = Vec3f{ 0, 0, 7 };
    auto const axis = Vec3f{ 1, 0, 0 };
    auto const degrees = 90.0f; 

    auto point = Point3f{ 1, 1, 1 }; 
    auto vec = Vec3f{ 0, 1, 0 };
    auto normal = Vec3f{ 0, 1, 0 }.to_normal(); 

    SECTION("scale") {
        transform.scale(scale); 
        auto const scaled_point = transform.apply(point);
        REQUIRE(scaled_point == Point3f{ 1, 4, 1 });
        auto const scaled_vec = transform.apply(vec);
        REQUIRE(scaled_vec == Vec3f{ 0, 4, 0 });
        auto const scaled_normal = transform.apply(normal);
        REQUIRE(scaled_normal == Vec3f{ 0, 1, 0 }.to_normal());
    }

    REQUIRE(true);
}
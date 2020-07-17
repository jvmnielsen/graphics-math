#include <graphics-math.hpp>

#include <catch2/catch.hpp>

#include <type_traits>

using namespace gm;

TEST_CASE("Transformations", "[Transform]") {

    auto transform = gm::Transform();
    auto const scale = Vec3f{ 1, 4, 1 };
    auto const translate = Vec3f{ 0, 0, 7 };
    auto const axis = Vec3f{ 1, 0, 0 };
    auto const degrees = 90.0f; 

    auto point = Point3f{ 1, 1, 1 }; 
    auto vec = Vec3f{ 0, 1, 0 };
    auto normal = Vec3f{ 0, 1, 0 }.normalise(); 

    SECTION("scale") {
        auto transform = gm::Transform();
        transform.scale(scale); 
        auto const scaled_point = transform.apply(point);
        REQUIRE(scaled_point == Point3f{ 1, 4, 1 });
        auto const scaled_vec = transform.apply(vec);
        REQUIRE(scaled_vec == Vec3f{ 0, 4, 0 });
        auto const scaled_normal = transform.apply(normal);
        REQUIRE(scaled_normal == Vec3f{ 0, 1, 0 }.normalise());
    }

    SECTION("translate") { // only affects points
        auto transform = gm::Transform();
        transform.translate(translate); 
        auto const translated_point = transform.apply(point);
        REQUIRE(translated_point == Point3f{ 1, 1, 8 });
        auto const translated_vec = transform.apply(vec);
        REQUIRE(translated_vec == vec);
        auto const translated_normal = transform.apply(normal);
        REQUIRE(translated_normal == normal);
    }

    SECTION("rotate") {
        auto transform = gm::Transform();
        transform.rotate(axis, degrees); 
        auto const rotated_point = transform.apply(point);
        REQUIRE(rotated_point == Point3f{ 1, -1, 1 });
        auto const rotated_vec = transform.apply(vec);
        REQUIRE(rotated_vec == Vec3f{ 0, 0, 1 });
        auto const rotated_normal = transform.apply(normal);
        REQUIRE(rotated_normal == Vec3f{ 0, 0, 1 }.normalise());
    }
}

TEST_CASE("Orthonormal basis", "[ONB]") {
    auto constexpr onb = ONB(Vec3f{1, 1, 0}.normalise()); 
    auto constexpr x = Vec3f{1, 0, 0}; 
    auto constexpr y = Vec3f{0, 1, 0}; 
    auto constexpr z = Vec3f{0, 0, 1}; 
    REQUIRE(onb.convert_to_local(x) == static_cast<Vec3f>(onb.u()));
    REQUIRE(onb.convert_to_local(y) == static_cast<Vec3f>(onb.v()));
    REQUIRE(onb.convert_to_local(z) == static_cast<Vec3f>(onb.w()));
}
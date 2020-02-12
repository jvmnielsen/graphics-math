#include <catch2/catch.hpp>
#include <graphics-math.hpp>
#include <gcem.hpp>

TEMPLATE_TEST_CASE( 
    "Vec3s with integers have length", "[Vec3]", 
    std::int32_t, std::int64_t) 
{
    auto v = gm::Vec3<TestType>{ 1, 2, 6 };
    REQUIRE( v.x == 1 );
    REQUIRE( v.y == 2 );
    REQUIRE( v.z == 6 );

    REQUIRE( v.length() == 6 );

    SECTION( "length is available at compile time" ) {
        auto constexpr u = gm::Vec3<TestType>{ 1, 2, 6 };
        if constexpr (u.length() == 6) {
            REQUIRE( true );
        } else {
            REQUIRE( false );
        }
    }

    SECTION( "length changes with resize" ) {
        v.x = 63;
        REQUIRE( v.length() == 63 );
    }
}

TEMPLATE_TEST_CASE( 
    "Vec3s with floats have length", "[Vec3]", 
    float, double) 
{
    auto constexpr v = gm::Vec3<TestType>{ 1, 2, 6 };
    REQUIRE( v.x == 1 );
    REQUIRE( v.y == 2 );
    REQUIRE( v.z == 6 );

    REQUIRE( std::abs(v.length() - 6.403) <= 0.001 );

    SECTION( "length is available at compile time" ) {
        if constexpr (gcem::abs(v.length() - 6.403) <= 0.001) {
            REQUIRE( true );
        } else {
            REQUIRE( false );
        }
    }


}
#include <catch2/catch.hpp>
#include <graphics-math.hpp>

TEMPLATE_TEST_CASE( 
    "Vec3s (integers) have length", "[Vec3]", 
    std::int32_t, std::int64_t) 
{
    auto v = gm::Vec3<TestType>{ 1, 2, 6 };
    REQUIRE( v.x == 1 );
    REQUIRE( v.y == 2 );
    REQUIRE( v.z == 6 );

    REQUIRE( v.length() == 6 );

    SECTION( "length changes with resize" ) {
        v.x = 63;
        REQUIRE( v.length() == 63 );
    }

    SECTION( "default length is zero" ) {
        auto const w = gm::Vec3<TestType>{ };
        REQUIRE( w.length() == 0 );
    }
}

TEMPLATE_TEST_CASE( 
    "Vec3s (floating point) have length", "[Vec3]", 
    float, double) 
{
    auto v = gm::Vec3<TestType>{ 1, 2, 6 };
    REQUIRE( v.x == 1 );
    REQUIRE( v.y == 2 );
    REQUIRE( v.z == 6 );

    REQUIRE( v.length() == Approx(6.403).epsilon(0.01) );

    SECTION( "length changes with resize" ) {
        v.x = 63;
        REQUIRE( v.length() == Approx(63.317).epsilon(0.01) );
    }

    SECTION( "negative length is the same" ) {
        v.x = -63;
        REQUIRE( v.length() == Approx(63.317).epsilon(0.01) );
    }

    SECTION( "default length is zero" ) {
        auto const w = gm::Vec3<TestType>{ };
        REQUIRE( w.length() == Approx(0).epsilon(0.001) );
    }
}
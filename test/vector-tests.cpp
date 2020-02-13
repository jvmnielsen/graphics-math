#include <graphics-math.hpp>

#include <catch2/catch.hpp>

#include <type_traits>

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

TEMPLATE_TEST_CASE( "Basic operators", "[Vec3]", std::int32_t, std::int64_t, float, double ) {
    auto const v = gm::Vec3<TestType>{ 1, 8, 9 };
    auto const u = gm::Vec3<TestType>{ 7, 2, 2 };
    SECTION( "addition" ) {
        REQUIRE( u + v == gm::Vec3<TestType>{ 8, 10, 11 });
    }
    SECTION( "subtraction" ) {
        REQUIRE( u - v == gm::Vec3<TestType>{ 6, -6, -7 });
    }
}

TEMPLATE_TEST_CASE( "Dot product", "[Vec3]", std::int32_t, std::int64_t, float, double ) {
    auto const v = gm::Vec3<TestType>{ 1, 8, 9 };
    auto const u = gm::Vec3<TestType>{ 7, 2, -2 };
    auto const expected = 7*1 + 8*2 + 9*(-2);
    SECTION( "basic case" ) {
        REQUIRE( gm::dot(v, u) == expected);
    }
    SECTION( "order doesn't matter" ) {
        REQUIRE( gm::dot(u, v) == expected);
    }
    SECTION( "as member function" ) {
        REQUIRE( u.dot(v) == expected);
    }
}

TEMPLATE_TEST_CASE( "scaling by constant", "[Vec3]", std::int32_t, std::int64_t, float, double ) {
    auto const v = gm::Vec3<TestType>{ 9, 828, 18 };
    auto const factor = 4;

    SECTION( "multiplication" ) {
        REQUIRE( factor * v == gm::Vec3<TestType>{ 36, 3312, 72 } );
    }
    SECTION( "multiplication by 0" ) {
        REQUIRE( 0 * v == gm::Vec3<TestType>{ 0, 0, 0 } );
    }
}

TEMPLATE_TEST_CASE( "unary minus", "[Vec3]", std::int32_t, std::int64_t, float, double ) {
    auto const v = gm::Vec3<TestType>{ 1222, 91, 2 };
    REQUIRE( -v == gm::Vec3<TestType>{ -1222, -91, -2 } );
}

TEMPLATE_TEST_CASE( "accessors", "[Vec3]", std::int32_t, std::int64_t, float, double ) {
    auto const v = gm::Vec3<TestType>{ 28, 19, -12 };
    REQUIRE( v[0] == 28 );
    REQUIRE( v[1] == 19 );
    REQUIRE( v[2] == -12 );
}

/*
TEMPLATE_TEST_CASE( "normalise", "[Vec3]", std::int32_t, std::int64_t, float, double ) {
    auto const v = gm::Vec3<TestType>{ 1, 1, 2 };
    if constexpr (std::is_floating_point<TestType>::value) {
        REQUIRE( v.normalise() == gm::Normal3<TestType>{ } );
    } else {
        REQUIRE( )
    }
} */

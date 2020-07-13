#include <graphics-math.hpp>

#include <catch2/catch.hpp>

#include <type_traits>

TEMPLATE_TEST_CASE(
    "Vec3s have length", "[Vec3]",
    std::int32_t, std::int64_t,
    float, double)
{
    auto v = gm::Vec3<TestType>{ 1, 2, 6 };
    REQUIRE( v.x == 1 );
    REQUIRE( v.y == 2 );
    REQUIRE( v.z == 6 );
    
    REQUIRE( v.length_squared() == static_cast<TestType>(41) );

    if constexpr (std::is_floating_point<TestType>::value) {
        REQUIRE( v.length() == Approx(6.403).epsilon(0.01) );
    } else {
        REQUIRE( v.length() == 6 );
    }

    SECTION( "length changes with resize" ) {
        v.x = 63;
        if constexpr (std::is_floating_point<TestType>::value) {
            REQUIRE( v.length() == Approx(63.317).epsilon(0.01) );
            REQUIRE( v.length_squared() == Approx(4009).epsilon(0.01) );
        } else {
            REQUIRE( v.length() == 63 );
            REQUIRE( v.length_squared() == 4009 );
        }
    }

    SECTION( "default length is zero" ) {
        auto const w = gm::Vec3<TestType>{ };
        REQUIRE( w.length() == 0 );
        REQUIRE( w.length_squared() == 0 );
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

TEMPLATE_TEST_CASE( "Comparison operators", "[Vec3]", std::int32_t, std::int64_t, float, double ) {
    auto const u = gm::Vec3<TestType>{ 1, 8, 9 };
    auto const v = gm::Vec3<TestType>{ 1, 8, 9 };
    auto const w = gm::Vec3<TestType>{ 7, 2, 2 };
    REQUIRE( u == v );
    REQUIRE( u != w );
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

TEMPLATE_TEST_CASE( "cross product", "[Vec3]", std::int32_t, std::int64_t, float, double ) {
    auto const v = gm::Vec3<TestType>{ 2, 3, 4 };
    auto const u = gm::Vec3<TestType>{ 5, 6, 7 };
    
    REQUIRE( v.cross(u) == gm::Vec3<TestType>{ -3, 6, -3 } );
    REQUIRE( cross(v, u) == gm::Vec3<TestType>{ -3, 6, -3 } );
}

TEMPLATE_TEST_CASE( "scaling by constant", "[Vec3]", std::int32_t, std::int64_t, float, double ) {
    auto const v = gm::Vec3<TestType>{ 9, 828, 18 };
    auto const factor = static_cast<TestType>(4);
    auto const divisor = static_cast<TestType>(5);

    SECTION( "multiplication" ) {
        REQUIRE( factor * v == gm::Vec3<TestType>{ 36, 3312, 72 } );
    }
    SECTION( "multiplication by 0" ) {
        REQUIRE( static_cast<TestType>(0) * v == gm::Vec3<TestType>{ 0, 0, 0 } );
    }
    SECTION( "division" ) {
        if constexpr (std::is_floating_point<TestType>::value) {
            auto const w = v / divisor; 
            REQUIRE( w.x == Approx(1.8).epsilon(0.01) );
            REQUIRE( w.y == Approx(165.6).epsilon(0.01) );
            REQUIRE( w.z == Approx(3.6).epsilon(0.01) );
        } else {
            auto const w = v / divisor; 
            REQUIRE( w.x == 1);
            REQUIRE( w.y == 165);
            REQUIRE( w.z == 3);
        }
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


TEMPLATE_TEST_CASE( "To normal", "[Vec3]", float, double ) {
    auto constexpr v = gm::Vec3<TestType>{ 1, 1, 2 };
    auto constexpr n = v.to_normal<TestType>();

    REQUIRE(n.x() == Approx(0.40824829046));
    REQUIRE(n.y() == Approx(0.40824829046));
    REQUIRE(n.z() == Approx(0.81649658092));

} 

TEMPLATE_TEST_CASE( "Normal operations", "[Normal3]", float, double ) {
    auto constexpr v = gm::Vec3<TestType>{ -3, 10, 9 };
    auto constexpr u = gm::Vec3<TestType>{ 3, -2, 20 };
    auto constexpr n = v.to_normal<TestType>();
    auto constexpr m = u.to_normal<TestType>();
    SECTION("dot product: normal/vec") {
        REQUIRE(dot(n, v) == Approx(13.78404875));
    }
    SECTION("cross product: normal/vec") {
        
        auto constexpr cross = gm::cross(n, u); 
        REQUIRE(cross.x == Approx(15.81538225));
        REQUIRE(cross.y == Approx(6.311643373));
        REQUIRE(cross.z == Approx(-1.741143000));
    }
    SECTION("dot product: normal/normal") {
        REQUIRE(dot(m, n) == Approx(0.539045122642215824));
    }
    SECTION("cross product: normal/normal") {
        auto constexpr cross = gm::cross(m, n); 
        REQUIRE(cross.x == Approx(-0.7782240843));
        REQUIRE(cross.y == Approx(-0.3105756667));
        REQUIRE(cross.z == Approx(0.08567604601));
    }
} 

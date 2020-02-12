#include <catch2/catch.hpp>
#include <graphics-math.hpp>

TEST_CASE( "is constexpr", "[sqrt]" ) {

    SECTION( "with float" ) {
        auto constexpr const num = 9.0f;
        if constexpr ( gm::sqrt(num) == 3.0f ) {
            REQUIRE( true );
        } else {
            REQUIRE( false );
        }
    }    

    SECTION( "with int" ) {
        auto constexpr const num = 349;
        if constexpr ( gm::sqrt(num) == 19 ) {
            REQUIRE( true );
        } else {
            REQUIRE( false );
        }
    }   
}

TEST_CASE( "works with different types", "[sqrt]" ) {

    SECTION( "with float" ) {
        auto const num = 99021.2;
        REQUIRE( gm::sqrt(num) == Approx(314.676) );
    }    

    SECTION( "with int" ) {
        auto const num = 2828271;
        REQUIRE( gm::sqrt(num) == 1682 );
    }   

}
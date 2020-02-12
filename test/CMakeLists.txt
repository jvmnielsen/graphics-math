
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/Catch2/)

add_executable(tests)
target_sources(tests
    PRIVATE
    catch.cpp
    vector-tests.cpp
)

target_link_libraries(tests Catch2::Catch2 graphics-math gcem)
target_compile_features(tests PRIVATE cxx_std_17)

include(CTest)
include(Catch)
catch_discover_tests(tests)
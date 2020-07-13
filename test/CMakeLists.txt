add_executable(tests
    catch.cpp
    vector-tests.cpp
    matrix-tests.cpp
    utility-tests.cpp
    transformation-tests.cpp
)

find_package(Catch2 CONFIG REQUIRED)
target_link_libraries(tests PRIVATE graphics-math Catch2::Catch2)
target_compile_features(tests PRIVATE cxx_std_17)

include(CTest)
include(Catch)
catch_discover_tests(tests)
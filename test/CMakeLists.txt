
# include_directories(${CMAKE_SOURCE_DIR}/thirdparty/Catch2/)

add_executable(tests)
target_sources(tests
    PRIVATE
    catch.cpp
    vector-tests.cpp
)

find_package(Catch2 CONFIG REQUIRED)
# target_link_libraries(main  Catch2::Catch2)

target_link_libraries(tests PRIVATE Catch2::Catch2 graphics-math)
target_compile_features(tests PRIVATE cxx_std_17)

include(CTest)
include(Catch)
catch_discover_tests(tests)
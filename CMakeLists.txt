cmake_minimum_required(VERSION 3.12)
project(graphics-math VERSION 0.1.0)

add_library(graphics-math INTERFACE)
#  ${CMAKE_CURRENT_SOURCE_DIR}/src/transform.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/onb.cpp)
# include_directories(include)
target_include_directories(
  ${PROJECT_NAME}
  INTERFACE include)

find_package(gcem CONFIG REQUIRED)
target_link_libraries(graphics-math INTERFACE gcem)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
# install(FILES test.h DESTINATION include)

# install(TARGETS 
#         EXPORT ${PROJECT_NAME}_Targets
#         ARCHIVE DESTINATION 
#         LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#         RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

enable_testing()
add_subdirectory(test)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

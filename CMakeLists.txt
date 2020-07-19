cmake_minimum_required(VERSION 3.12)
project(graphics-math VERSION 0.1.0)

add_library(graphics-math INTERFACE)
target_include_directories(
  ${PROJECT_NAME}
  INTERFACE include)

find_package(gcem CONFIG REQUIRED)
target_link_libraries(graphics-math INTERFACE gcem)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(TARGETS 
        EXPORT ${PROJECT_NAME}_Targets
        ARCHIVE DESTINATION 
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

enable_testing()
add_subdirectory(test)


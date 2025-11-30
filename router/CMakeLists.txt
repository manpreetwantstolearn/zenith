cmake_minimum_required(VERSION 3.25)
project(router)

add_library(zenith_router src/Router.cpp)
target_include_directories(zenith_router PUBLIC include)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

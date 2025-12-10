add_library(zenith_router src/Router.cpp)
target_include_directories(zenith_router PUBLIC include)
target_link_libraries(zenith_router PRIVATE zenith_sanitizers)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

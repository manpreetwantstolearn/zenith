cmake_minimum_required(VERSION 3.25)

project(zenith_concurrency)

find_package(Threads REQUIRED)

add_library(zenith_concurrency
    src/WorkerPool.cpp
    src/IoWorkerPool.cpp
)

target_include_directories(zenith_concurrency
    PUBLIC
        include
)

target_link_libraries(zenith_concurrency
    PUBLIC
        Threads::Threads
)

# Add tests if testing is enabled
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

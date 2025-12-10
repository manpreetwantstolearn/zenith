find_package(Threads REQUIRED)

add_library(zenith_execution
    src/ThreadPool.cpp
    src/StripedMessagePool.cpp
    src/ObservableMessagePool.cpp
)

target_include_directories(zenith_execution
    PUBLIC
        include
)

target_link_libraries(zenith_execution
    PRIVATE
        zenith_sanitizers
        Threads::Threads
    PUBLIC
        observability
)

# Add tests if testing is enabled
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
